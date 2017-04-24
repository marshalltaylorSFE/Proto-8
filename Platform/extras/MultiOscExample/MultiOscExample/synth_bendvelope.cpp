#include "synth_bendvelope.h"
#include "stdint.h"
#include "timeKeeper32.h"

//States
#define SM_IDLE 0
#define SM_ATTACK 1
#define SM_POST_DECAY 2
#define SM_PRE_DECAY 3
#define SM_DECAY 4
#define SM_PRE_RELEASE 5
#define SM_RELEASE 6
#define SM_POST_RELEASE 7
#define SM_ATTACK_HOLD 8

//Note states
#define NOTE_OFF 0
#define NOTE_ON 1
#define NOTE_NEW 2

extern const uint8_t fastMath[9][257];
AudioSynthBendvelope::AudioSynthBendvelope() : AudioStream(1, inputQueueArray)
{
	//Init variables
	state = SM_IDLE;
	noteState = NOTE_OFF;
	amp = 0;
	//Knob range scaling
	attackTable.maxTime = 1000000;
	decayTable.maxTime = 2500000;
	releaseTable.maxTime = 5000000;
	maxAHold = 1000000;

}

BendTable::BendTable( void )
{
    powerScale = 0;
    maxTime = 10000;
    calculate( 255, 0, 1, 1 );
    usMaxStageLength = 1; //bad default


}

void BendTable::calculate( int32_t upperVar, int32_t lowerVar, int8_t polarity, int8_t directionVar )
{
    direction = directionVar * polarity * -1;
    uint32_t timeVar = 0;
    uint32_t tempTimeVar = 0;
    uint32_t maxAmp;
    int16_t ampTemp;
    maxAmp = upperVar - lowerVar;
    if( polarity == -1 )
    {
        lowerVar += maxAmp;
    }
    for( timeVar = 0; timeVar < 256; timeVar++ )
    {
        if( directionVar == 1 )
        {
            tempTimeVar = timeVar;
        }
        else
        {
            tempTimeVar = 255 - timeVar;
        }

        //ampTemp = (uint16_t)(maxAmp*(float)pow(((float)tempTimeVar/(float)255), (exp((double)2*(float)powerScale/127))));
		ampTemp = (uint16_t)maxAmp*fastMath[(powerScale/32)+4][tempTimeVar] >> 8;
		
        if(ampTemp > 255)
        {
            ampTemp = 255;
        }

        if(ampTemp <= 0)
        {
            ampTemp = 0;
        }
        data[timeVar] = (lowerVar + ( polarity * ampTemp ));
    }
	
//    //Now generate other table
//    //Scan the table for the next sample number that is less than the input data
//    // put that number at that data location
//    for( int dataValue = 0; dataValue < 256; dataValue++ ) //Sample number of output graph (data value sought)
//    {
//        timeVar = 0;
//        while((dataValue != data[timeVar])||(timeVar != 255))
//        {
//            timeVar++;
//        }
//        positionLookup[dataValue] = dataValue;
//
//    }

}

int32_t BendTable::getSample( int32_t sampleVar )
{
    if(sampleVar > 255)
    {
        sampleVar = 255;
    }
    int32_t * pointer;
    pointer = &data[sampleVar];
    return * pointer;
}

int32_t BendTable::getSampleByTime( uint32_t usIntoVar )
{
    //get the total time in us
    uint32_t temp = (usIntoVar * 256 ) / knobFactor;
    temp = temp / ( maxTime >> 16 );
    //Replace this with next
    //temp = temp * 255;
    //temp = temp >> 16;
    temp = temp >> 8;


    if(temp > 255)
    {
        temp = 255;
    }
    int32_t * pointer;
    pointer = &data[temp];
    return * pointer;
}

uint32_t BendTable::getPositionBySample( int32_t sampleVar )
{
    uint8_t rotateBit = 0x80;
    uint8_t accumulator = 0x00;
    sampleVar = sampleVar * direction;
    while( rotateBit )
    {
        if( (direction * (data[accumulator | rotateBit])) > sampleVar )
        {
            //Point is to the right
            accumulator |= rotateBit;
        }
        rotateBit = rotateBit >> 1;
    }
    return accumulator;
}

uint32_t BendTable::getTimeBySample( int32_t sampleVar )
{
    uint32_t tempTime = getPositionBySample( sampleVar );
    tempTime = tempTime * maxTime;
    tempTime = tempTime >> 8;
    tempTime = tempTime * knobFactor;
    tempTime = tempTime >> 8;
    return tempTime;
}


void AudioSynthBendvelope::update(void)
{
	audio_block_t *block;
	uint32_t *p, *end;
	uint32_t sample12, sample34, sample56, sample78, tmp1;
	
	block = allocate();
	if (!block) return;
	//if (state == STATE_IDLE) {
	//	release(block);
	//	return;
	//}
	p = (uint32_t *)(block->data);
	end = p + AUDIO_BLOCK_SAMPLES/2;

	while (p < end)
	{
		// process 8 samples, using only mult
		sample12 = *p++;
		sample34 = *p++;
		sample56 = *p++;
		sample78 = *p++;
		p -= 4;

		tmp1 = ( (int32_t) amp << 7 );
	
		sample12 = pack_16b_16b(tmp1, tmp1);
		sample34 = pack_16b_16b(tmp1, tmp1);
		sample56 = pack_16b_16b(tmp1, tmp1);
		sample78 = pack_16b_16b(tmp1, tmp1);
		
		
		*p++ = sample12;
		*p++ = sample34;
		*p++ = sample56;
		*p++ = sample78;
		
		//calculate next amp
		tick(167);
		
	}

	transmit(block);
	release(block);
}


void AudioSynthBendvelope::tick( uint32_t uTicks )
{
	// Let the timers know how may useconds have passed
	mainTimeKeeper.uIncrement(uTicks);

	//State machine
	uint8_t next_state = state;
	switch( state )
	{
	case SM_IDLE:
		//do nothing
		if( noteState != NOTE_OFF )
		{
			next_state = SM_ATTACK;
			mainTimeKeeper.uClear();
			noteState = NOTE_ON;
		}
		break;
	case SM_ATTACK:
		//Increment amp or leave
		if( amp > 253 )
		{
			next_state = SM_ATTACK_HOLD;
			mainTimeKeeper.uClear();
		}
		else if( noteState == NOTE_OFF )
		{
			if( amp < decayTable.getSample(255) )
			{
				//We haven't reached sustain yet, do release
				uint32_t uTempTicks = releaseTable.getTimeBySample(amp);
				//Force the clock
				mainTimeKeeper.uClear();
				mainTimeKeeper.uIncrement(uTempTicks);
				next_state = SM_RELEASE;

			}
			else
			{
				//We're above sustain, do decay seek
				uint32_t uTempTicks = decayTable.getTimeBySample(amp);
				//Force the clock
				mainTimeKeeper.uClear();
				mainTimeKeeper.uIncrement(uTempTicks);
				next_state = SM_DECAY;
			}
		}
		else
		{
			//ignore new note states, convert to note on
			if( noteState == NOTE_NEW )//inChar
			{
				noteState = NOTE_ON;
			}
			//change amp
            amp = attackTable.getSampleByTime(mainTimeKeeper.uGet());
		}
		break;
	case SM_PRE_DECAY:
		break;
	case SM_ATTACK_HOLD:
		//Increment amp or leave
		if( mainTimeKeeper.uGet() > envAttackHold.timeScale )
		{
			next_state = SM_DECAY;
			mainTimeKeeper.uClear();
		}
		break;
	case SM_DECAY:
		if( amp > envSustain.level )  //Always get to sustain level before advancing
		{
            amp = decayTable.getSampleByTime(mainTimeKeeper.uGet());
		}
		//If there is a new note, start attacking
		if( noteState == NOTE_NEW )
		{
			noteState = NOTE_ON;
			//Note went back on!
			uint32_t uTempTicks = attackTable.getTimeBySample(amp);
			//Force the clock
			mainTimeKeeper.uClear();
			mainTimeKeeper.uIncrement(uTempTicks);
			next_state = SM_ATTACK;

		}
		else if( (noteState == NOTE_OFF)&&( amp <= envSustain.level ))
		{
			mainTimeKeeper.uClear();
			next_state = SM_RELEASE;
		}
		break;
	case SM_POST_DECAY:
		break;
	case SM_PRE_RELEASE:
		break;
	case SM_RELEASE:
		if( noteState != NOTE_OFF )
		{
			//Note went back on!
			uint32_t uTempTicks = attackTable.getTimeBySample(amp);
			//Force the clock
			mainTimeKeeper.uClear();
			mainTimeKeeper.uIncrement(uTempTicks);
			next_state = SM_ATTACK;

		}
		else  //it does equal note off
		{
			//Serial.println(releaseTable.usMaxStageLength);
			if( mainTimeKeeper.uGet() < releaseTable.usMaxStageLength )
			{
				if( amp > 0 )
				{
					amp = releaseTable.getSampleByTime(mainTimeKeeper.uGet());
				}
			}
			else
			{
				amp = 0;
				next_state = SM_IDLE;
			}
		}
		break;
	case SM_POST_RELEASE:
/* 		if( noteState == NOTE_OFF )
		{
			//go back to the release
			next_state = SM_RELEASE;

		}
		else
		{
			if( amp > 0 )
			{
				//changeAmp( envRelease, mainTimeKeeper.uGet(), state, amp );
			}
		} */
		break;
	default:
		break;
	}
	//Apply the next state after the logic has completed
	state = next_state;
	//Serial.println(amp);
}

void AudioSynthBendvelope::noteOn(void)
{
	noteState = NOTE_NEW;
}

void AudioSynthBendvelope::noteOff(void)
{
    noteState = NOTE_OFF;
}

void AudioSynthBendvelope::attack( uint8_t var_attack, int8_t var_power )
{
    //Scale 0-255 input parameters to the appropriate phase range in ms
	if( var_attack == 0 ) var_attack++;
    attackTable.knobFactor = var_attack;
	if( var_power == 0 ) var_power++;
    attackTable.powerScale = var_power;
    attackTable.calculate( 255, 0, 1, 1 );
    attackTable.usMaxStageLength = ( var_attack *  attackTable.maxTime ) >> 8;

}

void AudioSynthBendvelope::decay( uint8_t var_decay, int8_t var_power )
{
	if( var_decay == 0 ) var_decay++;
    decayTable.knobFactor = var_decay;
	if( var_power == 0 ) var_power++;
    decayTable.powerScale = var_power;
    decayTable.calculate( 255, envSustain.level, 1, -1 );
    decayTable.usMaxStageLength = ( var_decay *  decayTable.maxTime ) >> 8;
}

uint32_t AudioSynthBendvelope::getDecay( void )
{
  return envDecay.timeScale;
}

void AudioSynthBendvelope::sustain( uint8_t var_sustain )
{
	if( var_sustain == 0 ) var_sustain++;
    envSustain.level = var_sustain;
    decayTable.calculate( 255, envSustain.level, 1, -1 );
    releaseTable.calculate( envSustain.level, 0, -1, 1 );

}

void AudioSynthBendvelope::release( uint8_t var_release, int8_t var_power )
{
	if( var_release == 0 ) var_release++;
    releaseTable.knobFactor = var_release;
	if( var_power == 0 ) var_power++;
    releaseTable.powerScale = var_power;
    releaseTable.calculate( envSustain.level, 0, -1, 1 );
    releaseTable.usMaxStageLength = ( var_release *  releaseTable.maxTime ) >> 8;
	//Serial.println(releaseTable.usMaxStageLength);
}

void AudioSynthBendvelope::setAttackHold( uint8_t var_attackHold )
{
	if( var_attackHold == 0 ) var_attackHold++;
    envAttackHold.timeScale = (((uint32_t)var_attackHold * maxAHold) >> 8);

}
RateParameter::RateParameter( void )
{
    //Constructor
	timeScale = 1;
	powerScale = 0;
}

LevelParameter::LevelParameter( void )
{
    //Constructor
	level = 1;
}

uint8_t LevelParameter::getLevel( void )
{
    return level;

}
