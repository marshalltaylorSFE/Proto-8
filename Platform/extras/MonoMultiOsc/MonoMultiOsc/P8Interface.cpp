//**********************************************************************//
//
//  Interface example for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//  This file defines the human interaction of the panel parts
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//    2016/2/29: Merged with demo for segment driver
//
//**********************************************************************//
#include "P8Interface.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "Arduino.h"
#include "flagMessaging.h"
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

#include "wavegen.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"
#include "synth_bendvelope.h"
#include "synth_multiosc.h"
#include "synth_dc_binary.h"

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;
extern AudioSynthBendvelope    bendvelope1;    //xy=584,58
extern AudioSynthBendvelope    bendvelope2;    //xy=592,208
extern AudioSynthBendvelope    bendvelope3;    //xy=600,358
extern AudioSynthBendvelope    bendvelope4;    //xy=608,508
extern AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
extern AudioSynthWaveformDcBinary     dc1;
extern AudioSynthWaveformDcBinary     dc1CentA;
extern AudioSynthWaveformDcBinary     dc1CentB;
extern AudioSynthWaveformDcBinary     dc1CentC;
extern AudioSynthWaveformDcBinary     dc1CentD;
extern AudioSynthMultiOsc       multiosc1;
extern AudioMixer4              effectMixer;

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	lastAttack = 10;
	lastAttackBend = 127;
	lastAttackHold = 10;
	lastDecay = 100;
	lastDecayBend = 127;
	lastSustain = 100;
	lastRelease = 100;
	lastReleaseBend = 127;
	waveShapeParams[0][0] = 255;
	waveShapeParams[0][1] = 0;
	waveShapeParams[0][2] = 0;
	waveShapeParams[0][3] = 45;
	waveShapeParams[1][0] = 0;
	waveShapeParams[1][1] = 0;
	waveShapeParams[1][2] = 0;
	waveShapeParams[1][3] = 0;	
}

void P8Interface::reset( void )
{
	//Set explicit states
	//Set all LED off
	LEDs.clear();
	
}

//---------------------------------------------------------------------------//
//
//  To process the machine,
//    take the inputs from the system
//    process human interaction hard-codes
//    process the state machine
//    clean up and post output data
//
//---------------------------------------------------------------------------//
void P8Interface::processMachine( void )
{
	//switches.scan();
	//knobs.scan();
	update();

	//Do small machines
//	if( trackDownButton.serviceRisingEdge() )
//	{
//		if( viewingTrack > 1 )
//		{
//			viewingTrack--;
//		}
//	}
//	if( quantizeSelector.serviceChanged() )
//	{
	int8_t group1Service = 0;
	if( button1.serviceRisingEdge() )
	{
		group1Service = 1;
		group1Store = 1;
	}
	if( button2.serviceRisingEdge() )
	{
		group1Service = 2;
		group1Store = 2;
	}
	if( button3.serviceRisingEdge() )
	{
		group1Service = 3;
		group1Store = 3;
	}
	if( button4.serviceRisingEdge() )
	{
		group1Service = 4;
		group1Store = 4;
	}
	if( button5.serviceRisingEdge() )
	{
		group1Service = 5;
		group1Store = 5;
	}
	if( oscAButton1.serviceRisingEdge() )
	{
		//oscASelect++;
		//if(oscASelect > 2)
		//{
		//	oscASelect = 0;
		
		
//		WaveGenerator testWave;
//		switch(oscASelect)
//		{
//			case 0:
//			testWave.setParameters( 255, 255, 0, 0, 45 );
//			break;
//			case 1:
//			testWave.setParameters( 255, 0, 255, 0, 45 );
//			break;
//			case 2:
//			default:
//			testWave.setParameters( 255, 0, 0, 255, 45 );
//			break;
//		}
//		testWave.writeWaveU16_257( waveFormPointerA );		
	}	
	if( oscBButton1.serviceRisingEdge() )
	{
		//oscBSelect++;
		//if(oscBSelect > 2)
		//{
		//	oscBSelect = 0;
		//}
	}
	if( oscAButton2.serviceRisingEdge() )
	{
		oscALed4.toggle();
	}	
	if( oscBButton2.serviceRisingEdge() )
	{
		oscBLed4.toggle();
	}	
	if( oscAButton3.serviceRisingEdge() )
	{
		oscALed5.toggle();
	}	
	if( oscBButton3.serviceRisingEdge() )
	{
		oscBLed5.toggle();
	}
	if( button6.serviceRisingEdge() )
	{
		pageNumber++;
		if(pageNumber > 1)
		{
			pageNumber = 0;
		}
		led6.toggle();
	}
	if( button7.serviceRisingEdge() )
	{
		fineTune++;
		if(fineTune > 1)
		{
			fineTune = 0;
		}
		led7.toggle();
	}
	if( button8.serviceRisingEdge() )
	{
		led8.toggle();
	}
	if( button9.serviceRisingEdge() )
	{
		led9.toggle();
	}
	if( button10.serviceRisingEdge() )
	{
		led10.toggle();
	}
	if( button11.serviceRisingEdge() )
	{
		led11.toggle();
	}
	if( button12.serviceRisingEdge() )
	{
		led12.toggle();
	}
	if( button13.serviceRisingEdge() )
	{
		led13.toggle();
	}
	int8_t group3Service = 0;
	if( button14.serviceRisingEdge() )
	{
		group3Service = 1;
	}
	if( button15.serviceRisingEdge() )
	{
		group3Service = 2;
	}
	if( button16.serviceRisingEdge() )
	{
		group3Service = 3;
	}
	if( group1Service )
	{
		led1.setState(LEDOFF);
		led2.setState(LEDOFF);
		led3.setState(LEDOFF);
		led4.setState(LEDOFF);
		led5.setState(LEDOFF);
		switch( group1Service )
		{
			case 1:
			led1.setState(LEDON);
			group3Service = -1;
			break;
			case 2:
			led2.setState(LEDON);
			group3Store = 1;
			group3Service = -1;
			break;
			case 3:
			led3.setState(LEDON);
			group3Store = 1;
			group3Service = -1;
			break;
			case 4:
			led4.setState(LEDON);
			group3Store = 0;
			group3Service = -1;
			break;
			case 5:
			led5.setState(LEDON);
			group3Store = 0;
			group3Service = -1;
			break;
			default:
			break;
		}
	}
	int8_t group2Service = 0;
	if( button1.serviceHoldRisingEdge() )
	{
		group2Service = 1;
	}
	if( button2.serviceHoldRisingEdge() )
	{
		group2Service = 2;
	}
	if( button3.serviceHoldRisingEdge() )
	{
		group2Service = 3;
	}
	if( button4.serviceHoldRisingEdge() )
	{
		group2Service = 4;
	}
	if( button5.serviceHoldRisingEdge() )
	{
		group2Service = 5;
	}
	if( group2Service )
	{
		switch( group2Service )
		{
			case 1:
			break;
			case 2:
			led2.setState(LEDFLASHING);
			break;
			case 3:
			led3.setState(LEDFLASHING);
			break;
			case 4:
			led4.setState(LEDFLASHING);
			break;
			case 5:
			led5.setState(LEDFLASHING);
			break;
			default:
			break;
		}
	}
	if( group3Service ) //happens on button change
	{
		if( group3Service != -1 )
		{
			group3Store = group3Service;
		}
		led14.setState(LEDOFF);
		led15.setState(LEDOFF);
		led16.setState(LEDOFF);
		if((group1Store == 2)||(group1Store == 3))
		{
			switch( group3Store )  //switching LED, switch waveform here
			//Note: group3Store is uesd to set fixture knob's function
			{
				case 1:
				led14.setState(LEDON);
				break;
				case 2:
				led15.setState(LEDON);
				break;
				case 3:
				led16.setState(LEDON);
				default:
				break;
			}
		}
	}	

	//Knobs
	uint8_t temp1;
	uint8_t temp2;
	
	temp1 = attackKnob.serviceChanged();
	if( temp1 ) debugTemp = attackKnob.getState();
	temp2 = attackBendKnob.serviceChanged();
	if( temp2 ) debugTemp = attackBendKnob.getState();
	if( temp1 || temp2 )
	{
		if( pageNumber == 0 )
		{
			bendvelope1.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		}
		else if( pageNumber == 1 )
		{
			bendvelope2.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		}
	}
	if( holdKnob.serviceChanged() )
	{
		debugTemp = holdKnob.getState();
		if( pageNumber == 0 )
		{
			bendvelope1.setAttackHold( holdKnob.getState() );
		}
		else if( pageNumber == 1 )
		{
			bendvelope2.setAttackHold( holdKnob.getState() );
		}
	}
	temp1 = decayKnob.serviceChanged();
	if( temp1 ) debugTemp = decayKnob.getState();
	temp2 = decayBendKnob.serviceChanged();
	if( temp2 ) debugTemp = decayBendKnob.getState();
	if( temp1 || temp2 )
	{
		if( pageNumber == 0 )
		{
			bendvelope1.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
		}
		else if( pageNumber == 1 )
		{
			bendvelope2.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
		}
	}
	if( sustainKnob.serviceChanged() )
	{
		debugTemp = sustainKnob.getState();
		if( pageNumber == 0 )
		{
			bendvelope1.sustain( sustainKnob.getState() );// 0 to 255 for level
		}
		else if( pageNumber == 1 )
		{
			bendvelope2.sustain( sustainKnob.getState() );// 0 to 255 for level
		}
	}
	temp1 = releaseKnob.serviceChanged();
	if( temp1 ) debugTemp = releaseKnob.getState();
	temp2 = releaseBendKnob.serviceChanged();
	if( temp2 ) debugTemp = releaseBendKnob.getState();
	if( temp1 || temp2 )
	{
		if( pageNumber == 0 )
		{
			bendvelope1.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		}
		else if( pageNumber == 1 )
		{
			bendvelope2.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		}
	}
	if( oscAFreqKnob.serviceChanged() )
	{
		debugTemp = oscAFreqKnob.getState();
		if( pageNumber == 0 )
		{
			if( fineTune == 0 )
			{
				dcTuneOffset[0] = ((float)debugTemp - 127) / 64; //Use +- 2 octave with no range control for now
			}
			else
			{
				dc1CentA.amplitude_int(((int16_t)debugTemp - 127) << 10);
			}
		}
		else if( pageNumber == 1 )
		{
			if( fineTune == 0 )
			{
				dcTuneOffset[2] = ((float)debugTemp - 127) / 64; //Use +- 2 octave with no range control for now
			}
			else
			{
				dc1CentC.amplitude_int(((int16_t)debugTemp - 127) << 10);
			}
		}
	}
	if( oscBFreqKnob.serviceChanged() )
	{
		debugTemp = oscBFreqKnob.getState();
		if( pageNumber == 0 )
		{
			if( fineTune == 0 )
			{
				dcTuneOffset[1] = ((float)debugTemp - 127) / 64; //Use +- 2 octave with no range control for now
			}
			else
			{
				dc1CentB.amplitude_int(((int16_t)debugTemp - 127) << 10);
			}
		}
		else if( pageNumber == 1 )
		{
			if( fineTune == 0 )
			{
				dcTuneOffset[3] = ((float)debugTemp - 127) / 64; //Use +- 2 octave with no range control for now
			}
			else
			{
				dc1CentD.amplitude_int(((int16_t)debugTemp - 127) << 8);
			}

		}


	}
	if( oscAAmpKnob.serviceChanged() )
	{
		//using amp as cent input
		debugTemp = oscAAmpKnob.getState();
		if( pageNumber == 0 )
		{
			multiosc1.staticAmp[0] = debugTemp;
		}
		else if( pageNumber == 1 )
		{
			multiosc1.staticAmp[2] = debugTemp;
		}

	}
	if( oscBAmpKnob.serviceChanged() )
	{
		//using amp as cent input
		debugTemp = oscBAmpKnob.getState();
		if( pageNumber == 0 )
		{
			multiosc1.staticAmp[1] = debugTemp;
		}
		else if( pageNumber == 1 )
		{
			multiosc1.staticAmp[3] = debugTemp;
		}

	}
	//example:  dc1.amplitude(0.01994666666640625);
	
	if( fixtureKnob.serviceChanged() )
	{
		debugTemp = fixtureKnob.getState();
		if( pageNumber == 0 )
		{
			if(group1Store == 1)
			{
				sgtl5000_1.volume(((float)debugTemp / 256) * 1);
				sgtl5000_2.volume(((float)debugTemp / 256) * 1);
			}
			Serial.println(debugTemp);
			if(group1Store == 2)
			{
				switch(group3Store)
				{
					case 1:
					waveShapeParams[0][0] = debugTemp;
					break;
					case 2:
					waveShapeParams[0][1] = debugTemp;
					break;
					case 3:
					waveShapeParams[0][2] = debugTemp;
					break;
					default:
					break;
				}
				WaveGenerator testWave;
				testWave.setParameters( 255, waveShapeParams[0][0], waveShapeParams[0][1], waveShapeParams[0][2], 45 );			
				Serial.println("before");
				delay(20);
				testWave.writeWaveU16_257( multiosc1.getPointer( 0 ) );
				Serial.println("after");
				delay(20);
			}
			if(group1Store == 5)
			{
			}
		}
		else if( pageNumber == 1 )
		{
			//set effect bend amp
			effectMixer.gain(0, ((float)debugTemp - 127)/256);
		}

	}
	LEDs.setNumber1( debugTemp );
	float tempVoltage = 0;
	float tempFactor = 0; // n * factor = 2.5
	tempFactor = 2.5 / refKnob.getState();
	tempVoltage = (float)rail18Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 0 );
	tempVoltage = (float)rail33Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 3 );
	//'set' all the values
	//display1.update();
	//update();
	
	//Do main machine
	tickStateMachine();
	
	//Do pure LED operations first
	
	//System level LEDs
	oscALed1.setState(LEDOFF);
	oscALed2.setState(LEDOFF);
	oscALed3.setState(LEDOFF);
	oscBLed1.setState(LEDOFF);
	oscBLed2.setState(LEDOFF);
	oscBLed3.setState(LEDOFF);
	switch(oscASelect)
	{
		case 0:
		oscALed1.setState(LEDON);
		break;
		case 1:
		oscALed2.setState(LEDON);
		break;
		case 2:
		oscALed3.setState(LEDON);
		break;
		default:
		break;
	}
	switch(oscBSelect)
	{
		case 0:
		oscBLed1.setState(LEDON);
		break;
		case 1:
		oscBLed2.setState(LEDON);
		break;
		case 2:
		oscBLed3.setState(LEDON);
		break;
		default:
		break;
	}
	update();
	//Panel level LEDs
	//LEDs.send();
}

void P8Interface::tickStateMachine()
{
	//***** PROCESS THE LOGIC *****//
    //Now do the states.
    PStates nextState = state;
    switch( state )
    {
    case PInit:
		nextState = PIdle;
		
		break;
	case PIdle:
		nextState = PIdle;
        break;
    default:
        nextState = PInit;
		//Serial.println("!!!DEFAULT STATE HIT!!!");
        break;
    }
	
    state = nextState;

}

void P8Interface::timersMIncrement( uint8_t inputValue )
{
	button1.buttonDebounceTimeKeeper.mIncrement(inputValue);
	button2.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button3.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button4.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button5.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button6.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button7.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button8.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button9.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button10.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button11.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button12.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button13.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button14.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button15.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button16.buttonDebounceTimeKeeper.mIncrement(inputValue);	

	oscAButton1.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscAButton2.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscAButton3.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	
	oscBButton1.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscBButton2.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscBButton3.buttonDebounceTimeKeeper.mIncrement(inputValue);	

}

void P8Interface::setPointer( uint8_t oscNumber, int16_t * pointerVar ) //Pass number 0 = OSC A, 1 = OSC B
{
	switch( oscNumber )
	{
		case 0:
		waveFormPointerA = pointerVar;
		break;
		case 1:
		waveFormPointerB = pointerVar;
		break;
		default:
		break;
	}
}