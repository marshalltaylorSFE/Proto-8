//--------------------------------------------------------------------------------------
// Generates a single sample of a 256 sample long waveform
//
// char shape is SINESHAPE, PULSESHAPE, RAMPSHAPE, or DCSHAPE
// float duty, float amp
// char sample is 0x00 to 0xFF
//
// Shapes are ~ +-127, scaled by amp/100, then output ranged 0 to 255 (but type int)
#include "math.h"
#include "wavegen.h"


WaveGenerator::WaveGenerator( void )
{
    masterAmp = 0;
    rampAmp = 0;
    sineAmp = 0;
    pulseAmp = 0;
    pulseDuty = 0;
    sampleNumber = 0;

}

void WaveGenerator::resetOffset( void )
{
    sampleNumber = 0;

}


int16_t WaveGenerator::getSample( void )
{
    int16_t tempRamp = 0;
    int16_t tempSine = 0;
    int16_t tempPulse = 0;
    int32_t retVal;

    if(rampAmp)
    {
        tempRamp = (((int16_t)sampleNumber) - 127 ) * ( rampAmp );
    }

    if( sineAmp )
    {
        tempSine = sin(((float)sampleNumber * 3.141592)/128) * ((int32_t)sineAmp << 7 );
    }

    if( pulseAmp )
    {
		//Is sample beyond duty cycle?
		if ( sampleNumber < pulseDuty )
		{
			tempPulse = ( (int16_t)pulseAmp << 7 );
		}
		else
		{
			tempPulse = ( (int16_t)pulseAmp << 7 ) * -1;
		}
    }

    sampleNumber++;

//old way
if(0)
{
    //Sum all waves
	retVal = (int32_t)tempRamp + (int32_t)tempSine + (int32_t)tempPulse;
 	//get total amp factor
 	int32_t ampFactor = (sineAmp + pulseAmp + rampAmp); //max 767
 	//if they're all there, / 3.  If 1 is there, * 1. if 0.5 are there, * 2
 	retVal = retVal * masterAmp / ampFactor;
 	//brin
}

    //Sum all waves
	retVal = (int32_t)tempRamp + (int32_t)tempSine + (int32_t)tempPulse;
	
	//Carefull, overflow
    return retVal;

}

void WaveGenerator::setParameters( uint8_t masterAmpVar, uint8_t rampAmpVar, uint8_t sineAmpVar, uint8_t pulseAmpVar, uint8_t pulseDutyVar )
{
    masterAmp = masterAmpVar;
    rampAmp = rampAmpVar;
    sineAmp = sineAmpVar;
    pulseAmp = pulseAmpVar;
    pulseDuty = pulseDutyVar;
}

void WaveGenerator::writeWaveU16_257( int16_t * waveToWritePtr )
{
    resetOffset();
    for(int i = 0; i < 256; i++)
    {
		waveToWritePtr[i] = getSample();
	}
	waveToWritePtr[256] = waveToWritePtr[0];
}

int16_t * WaveGenerator::allocateU16_257( void )
{
	int16_t * tempWaveformPointer = new int16_t[257];  //Nothing deletes this
	
	//Fill with zero
    for(int i = 0; i < 257; i++)
    {
		tempWaveformPointer[i] = 0;
	}
	
	return tempWaveformPointer;
}
