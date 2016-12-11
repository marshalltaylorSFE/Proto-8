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

#include "wavegen.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"
#include "synth_bendvelope.h"
#include "synth_multiosc.h"
#include "synth_dc_binary.h"

extern LEDShiftRegister LEDs;
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
extern AudioSynthWaveformDcBinary dc_binary1;
extern AudioSynthWaveformDcBinary dc_binary2;

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	
	lfo1WaveSrc = 1;
	lfo2WaveSrc = 1;
	oscAWaveSrc = 1;
	oscBWaveSrc = 1;
	oscCWaveSrc = 1;
	oscDWaveSrc = 1;
	
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
	// Handle wave selection variable
	if( lfo1Shape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		lfo1WaveSrc++;
		if(lfo1WaveSrc > 3) lfo1WaveSrc = 1;
		lfo1Led1.setState(LEDOFF);
		lfo1Led2.setState(LEDOFF);
		lfo1Led3.setState(LEDOFF);
		switch(lfo1WaveSrc)
		{
			case 1:
			lfo1Led1.setState(LEDON);
			break;
			case 2:
			lfo1Led2.setState(LEDON);
			break;
			case 3:
			lfo1Led3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	if( lfo2Shape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		lfo2WaveSrc++;
		if(lfo2WaveSrc > 3) lfo2WaveSrc = 1;
		lfo2Led1.setState(LEDOFF);
		lfo2Led2.setState(LEDOFF);
		lfo2Led3.setState(LEDOFF);
		switch(lfo2WaveSrc)
		{
			case 1:
			lfo2Led1.setState(LEDON);
			break;
			case 2:
			lfo2Led2.setState(LEDON);
			break;
			case 3:
			lfo2Led3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	if( oscAShape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		oscAWaveSrc++;
		if(oscAWaveSrc > 3) oscAWaveSrc = 1;
		oscALed1.setState(LEDOFF);
		oscALed2.setState(LEDOFF);
		oscALed3.setState(LEDOFF);
		switch(oscAWaveSrc)
		{
			case 1:
			oscALed1.setState(LEDON);
			break;
			case 2:
			oscALed2.setState(LEDON);
			break;
			case 3:
			oscALed3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	if( oscBShape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		oscBWaveSrc++;
		if(oscBWaveSrc > 3) oscBWaveSrc = 1;
		oscBLed1.setState(LEDOFF);
		oscBLed2.setState(LEDOFF);
		oscBLed3.setState(LEDOFF);
		switch(oscBWaveSrc)
		{
			case 1:
			oscBLed1.setState(LEDON);
			break;
			case 2:
			oscBLed2.setState(LEDON);
			break;
			case 3:
			oscBLed3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	if( oscCShape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		oscCWaveSrc++;
		if(oscCWaveSrc > 3) oscCWaveSrc = 1;
		oscCLed1.setState(LEDOFF);
		oscCLed2.setState(LEDOFF);
		oscCLed3.setState(LEDOFF);
		switch(oscCWaveSrc)
		{
			case 1:
			oscCLed1.setState(LEDON);
			break;
			case 2:
			oscCLed2.setState(LEDON);
			break;
			case 3:
			oscCLed3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	if( oscDShape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		oscDWaveSrc++;
		if(oscDWaveSrc > 3) oscDWaveSrc = 1;
		oscDLed1.setState(LEDOFF);
		oscDLed2.setState(LEDOFF);
		oscDLed3.setState(LEDOFF);
		switch(oscDWaveSrc)
		{
			case 1:
			oscDLed1.setState(LEDON);
			break;
			case 2:
			oscDLed2.setState(LEDON);
			break;
			case 3:
			oscDLed3.setState(LEDON);
			break;
			default:
			break;
			
		}
	}
	//Handle sync toggles
	if( oscBSync.serviceRisingEdge() )
	{
		oscBSyncLed.toggle();
	}
	if( oscCSync.serviceRisingEdge() )
	{
		oscCSyncLed.toggle();
	}
	if( oscDSync.serviceRisingEdge() )
	{
		oscDSyncLed.toggle();
	}

	//OSC Knobs
	if( oscAPitch.serviceChanged() || oscAOctave.serviceChanged() )
	{
		oscAOctaveState = oscAOctave.getState();
		dcTuneOffset[0] = (int16_t)oscAOctaveState - 2 + ((float)oscAPitch.getState() - 127) / 200; //Use +- 2 octave with no range control for now
	}	
	if( oscACent.serviceChanged() )
	{
		dc1CentA.amplitude_int(((int16_t)oscACent.getState() - 128) << 8);
	}
	if( oscAPreAmp.serviceChanged() )
	{
		multiosc1.staticAmp[0] = oscAPreAmp.getState();
	}


	if( oscBPitch.serviceChanged() || oscBOctave.serviceChanged() )
	{
		oscBOctaveState = oscBOctave.getState();
		dcTuneOffset[1] = (int16_t)oscBOctaveState - 2 + ((float)oscBPitch.getState() - 127) / 200; //Use +- 2 octave with no range control for now
	}	
	if( oscBCent.serviceChanged() )
	{
		dc1CentB.amplitude_int(((int16_t)oscBCent.getState() - 128) << 8);
	}	
	if( oscBPreAmp.serviceChanged() )
	{
		multiosc1.staticAmp[1] = oscBPreAmp.getState();
	}
	
	
	if( oscCPitch.serviceChanged() || oscCOctave.serviceChanged() )
	{
		oscCOctaveState = oscCOctave.getState();
		dcTuneOffset[2] = (int16_t)oscCOctaveState - 2 + ((float)oscCPitch.getState() - 127) / 200; //Use +- 2 octave with no range control for now
	}	
	if( oscCCent.serviceChanged() )
	{
		dc1CentC.amplitude_int(((int16_t)oscCCent.getState() - 128) << 8);
	}	
	if( oscCPreAmp.serviceChanged() )
	{
		multiosc1.staticAmp[2] = oscCPreAmp.getState();
	}
	
	
	if( oscDPitch.serviceChanged() || oscDOctave.serviceChanged() )
	{
		oscDOctaveState = oscDOctave.getState();
		dcTuneOffset[3] = (int16_t)oscDOctaveState - 2 + ((float)oscDPitch.getState() - 127) / 200; //Use +- 2 octave with no range control for now
	}	
	if( oscDCent.serviceChanged() )
	{
		dc1CentD.amplitude_int(((int16_t)oscDCent.getState() - 128) << 8);
	}	
	if( oscDPreAmp.serviceChanged() )
	{
		multiosc1.staticAmp[3] = oscDPreAmp.getState();
	}
	
	
	//Bendvelope knobs
	if( bv1Attack.serviceChanged() || bv1AttackBend.serviceChanged() )
	{
		bendvelope1.attack( bv1Attack.getState(), (int16_t)bv1AttackBend.getState() - 128 );// 0 to 255 for length, -128 to 127
	}	
	if( bv1Hold.serviceChanged() )
	{
		bendvelope1.setAttackHold( bv1Hold.getState() );
	}
	if( bv1Decay.serviceChanged() || bv1DecayBend.serviceChanged() )
	{
		bendvelope1.decay( bv1Decay.getState(), ((int16_t)bv1DecayBend.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
	}	
	if( bv1Sustain.serviceChanged() )
	{
		bendvelope1.sustain( bv1Sustain.getState() );// 0 to 255 for level
	}
	if( bv1Release.serviceChanged() || bv1ReleaseBend.serviceChanged() )
	{
		bendvelope1.release( bv1Release.getState(), (int16_t)bv1ReleaseBend.getState() - 128 );// 0 to 255 for length, -128 to 127
	}
	
	if( bv2Attack.serviceChanged() || bv2AttackBend.serviceChanged() )
	{
		bendvelope2.attack( bv2Attack.getState(), (int16_t)bv2AttackBend.getState() - 128 );// 0 to 255 for length, -128 to 127
	}	
	if( bv2Hold.serviceChanged() )
	{
		bendvelope2.setAttackHold( bv2Hold.getState() );
	}
	if( bv2Decay.serviceChanged() || bv2DecayBend.serviceChanged() )
	{
		bendvelope2.decay( bv2Decay.getState(), ((int16_t)bv2DecayBend.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
	}	
	if( bv2Sustain.serviceChanged() )
	{
		bendvelope2.sustain( bv2Sustain.getState() );// 0 to 255 for level
	}
	if( bv2Release.serviceChanged() || bv2ReleaseBend.serviceChanged() )
	{
		bendvelope2.release( bv2Release.getState(), (int16_t)bv2ReleaseBend.getState() - 128 );// 0 to 255 for length, -128 to 127
	}
	//Wave shape knobs
	if( wave1Ramp.serviceChanged() || wave1Sine.serviceChanged() || wave1Pulse.serviceChanged() )
	{
		waveShapeParams[0][0] = wave1Ramp.getState();
		waveShapeParams[0][1] = wave1Sine.getState();
		waveShapeParams[0][2] = wave1Pulse.getState();	
		
		WaveGenerator testWave;
		testWave.setParameters( 255, waveShapeParams[0][0], waveShapeParams[0][1], waveShapeParams[0][2], 45 );			
		Serial.println("before");
		delay(20);
		testWave.writeWaveU16_257( multiosc1.getPointer( 0 ) );
		Serial.println("after");
		delay(20);
		
	}
	if( wave2Ramp.serviceChanged() || wave2Sine.serviceChanged() || wave2Pulse.serviceChanged() )
	{
		
	}
	if( wave3Width.serviceChanged() || wave3Pulse.serviceChanged() )
	{
		
	}
	
	//Bus knobs
	if( bus1Amp.serviceChanged() || bus1Offset.serviceChanged() )
	{
		int16_t ampCalc = ((int16_t)bus1Amp.getState() - 128) << 8;
		int16_t offsetCalc = ((int16_t)bus1Offset.getState() - 128) << 8;
		Serial.print("Amp1: ");
		Serial.print(ampCalc);
		Serial.print("  Offset1: ");
		Serial.println(offsetCalc);
		dc_binary2.amplitude_int( ampCalc );// 0 to 255 for length, -128 to 127
		dc_binary1.amplitude_int( offsetCalc );
	}	
	
	//Misc knobs
	if( masterVolume.serviceChanged() )
	{
		sgtl5000_1.volume(((float)masterVolume.getState() / 256) * 1);
		sgtl5000_2.volume(((float)masterVolume.getState() / 256) * 1);
	}
	if( Select.serviceChanged() )
	{
		effectMixer.gain(0, ((float)Select.getState() - 127)/256);
	}
	
	//Do main machine
	tickStateMachine();
	
	//Do something afterwards?
	
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
		lfo1Led1.setState(LEDON);
		lfo2Led1.setState(LEDON);
		oscALed1.setState(LEDON);
		oscBLed1.setState(LEDON);
		oscCLed1.setState(LEDON);
		oscDLed1.setState(LEDON);
		
		oscAOctaveState = oscAOctave.getState();
		oscBOctaveState = oscBOctave.getState();
		oscCOctaveState = oscCOctave.getState();
		oscDOctaveState = oscDOctave.getState();
		
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
	bus1SrcPick.buttonDebounceTimeKeeper.mIncrement(inputValue);
	bus1DestPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus2SrcPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus2DestPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus3SrcPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus3DestPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus4SrcPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus4DestPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus5SrcPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	bus5DestPick.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	lfo1Shape.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	lfo2Shape.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscASync.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscAShape.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscBSync.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscBShape.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscCSync.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscCShape.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscDSync.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	oscDShape.buttonDebounceTimeKeeper.mIncrement(inputValue);	

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