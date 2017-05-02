//**********************************************************************//
//
//  A synth that consists of 3 oscillators, 2 envelopes, and a selection
//  of modulation paths
//
//  MIT License: http://opensource.org/licenses/MIT
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2017/05/01: Created
//
//**********************************************************************//
#include "P8Interface.h"
#include "PanelComponents.h"
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
#include "synth_monoosc.h"
#include "synth_dc_binary.h"
#include "synth_dc_binary_glide.h"

extern LEDShiftRegister LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

extern AudioSynthWaveformDcBinary dc_one;     //xy=190.75,700.75
extern AudioSynthWaveformDcBinary dc_zero;        //xy=199.75,414
extern AudioEffectEnvelope      envelope1;      //xy=346.75,708
extern AudioSynthWaveformSine   lfo1;           //xy=354.75,657
extern AudioSynthWaveformDcBinary dc1PitchB;     //xy=374.75,461.75
extern AudioSynthWaveformDcBinary dc1CentB;       //xy=377.75,508
extern AudioSynthWaveformDcBinary dc1PitchA;     //xy=384.75,369.75
extern AudioSynthWaveformDcBinary dc1PitchC;     //xy=403.75,556.75
extern AudioSynthBendvelope     bendvelope1;    //xy=427.75,319
extern AudioSynthWaveformDcBinary dc1CentC;       //xy=429.75,607
extern AudioSynthMonoOsc        monoosc3;       //xy=629.75,561
extern AudioSynthMonoOsc        monoosc2;       //xy=633.75,487
extern AudioSynthMonoOsc        monoosc1;       //xy=635.75,412
extern AudioSynthWaveformDcBinary dc_filter;      //xy=789.75,599
extern AudioMixer4              mixer5;         //xy=827.75,475
extern AudioFilterStateVariable filter1;        //xy=973.75,485
extern AudioOutputI2SQuad       is_quad23;      //xy=1200.75,495
extern AudioSynthWaveformDcBinary modGain;        //xy=1343.75,589
extern AudioEffectMultiply      modAmp;         //xy=1484.75,583
extern AudioSynthWaveformDcBinary modOffset;      //xy=1491.75,628
extern AudioMixer4              effectMixer;    //xy=1657.75,561
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1163.75,390
extern AudioControlSGTL5000     sgtl5000_2;     //xy=1167.75,346
// GUItool: end automatically generated code

extern AudioAnalyzePeak         peak1;
extern AudioConnection          patchCord9000;

#define CordDCCB patchCord4
#define CordDCCC patchCord10
#define CordFilter patchCord14


extern ModulatorBlock modulator[4];

P8Interface::P8Interface( void )
{
}

void P8Interface::reset( void )
{
	state = PInit;
	busState = BInit;
	
	oscAWaveSrc = 1;
	oscBWaveSrc = 1;
	oscCWaveSrc = 1;
	
	waveShapeParams[0][0] = 128;
	waveShapeParams[0][1] = 128;
	waveShapeParams[0][2] = 0;
	waveShapeParams[0][3] = 45;

	waveShapeParams[1][0] = 0;
	waveShapeParams[1][1] = 255;
	waveShapeParams[1][2] = 0;
	waveShapeParams[1][3] = 55;

	waveShapeParams[2][0] = 0;
	waveShapeParams[2][1] = 0;
	waveShapeParams[2][2] = 200;
	waveShapeParams[2][3] = 50;
	
	//Set explicit states
	state = PInit;
	//Set all LED off
	LEDs.clear();

	modulator[0].init();
	modulator[1].init();
	modulator[2].init();
	modulator[3].init();

	
	effectPaths[0].set(&CordDCCB);
	effectPaths[1].set(&CordDCCC);
	effectPaths[2].set(&CordFilter);

	modSources[0].set( &bendvelope1, 0 );
	modSources[1].set( &envelope1, 0 );
	modSources[2].set( &lfo1, 0 );
	
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
void P8Interface::processMachine( uint16_t msInput )
{
	freshenComponents(msInput);

	// Handle wave selection variable
	if( oscShape.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		oscAWaveSrc++;
		if(oscAWaveSrc > 3) oscAWaveSrc = 1;
		oscLed1.setState(LEDOFF);
		oscLed2.setState(LEDOFF);
		oscLed3.setState(LEDOFF);
		switch(oscAWaveSrc)
		{
			case 1:
			oscLed1.setState(LEDON);
			break;
			case 2:
			oscLed2.setState(LEDON);
			break;
			case 3:
			oscLed3.setState(LEDON);
			break;
			default:
			break;
			
		}
		WaveGenerator testWave;
		testWave.setParameters( 255, waveShapeParams[oscAWaveSrc - 1][0], waveShapeParams[oscAWaveSrc - 1][1], waveShapeParams[oscAWaveSrc - 1][2], waveShapeParams[oscAWaveSrc - 1][3] );			
		testWave.writeWaveU16_257( monoosc1.getPointer( 0 ) );

	}

	
	//OSC Knobs
	if( oscPitch.serviceChanged() || oscOctave.serviceChanged() )
	{
		oscAOctaveState = oscOctave.getState();
		Serial.println(oscAOctaveState);
		dcTuneOffset[0] = (int16_t)oscAOctaveState - 2 + ((float)oscPitch.getAsUInt8() - 127) / 200; //Use +- 2 octave with no range control for now
		dcTuneOffset[1] = (int16_t)oscAOctaveState - 1 + ((float)oscPitch.getAsUInt8() - 127) / 200; //Use +- 2 octave with no range control for now
		dcTuneOffset[2] = (int16_t)oscAOctaveState - 1 + ((float)oscPitch.getAsUInt8() - 127) / 200; //Use +- 2 octave with no range control for now
	}	

	if( oscPreAmp.serviceChanged() )
	{
		sgtl5000_1.volume(((float)oscPreAmp.getAsUInt8() / 256) * 1);
		sgtl5000_2.volume(((float)oscPreAmp.getAsUInt8() / 256) * 1);

	}
	
	//Bendvelope knobs
	if( bv1Attack.serviceChanged() || bv1AttackBend.serviceChanged() )
	{
		Serial.println("Attack changed");
		bendvelope1.attack( bv1Attack.getAsUInt8(), (int16_t)bv1AttackBend.getAsUInt8() - 128 );// 0 to 255 for length, -128 to 127
	}	
	if( bv1Hold.serviceChanged() )
	{
		Serial.println("Hold changed");
		bendvelope1.setAttackHold( bv1Hold.getAsUInt8() );
	}
	if( bv1Decay.serviceChanged() || bv1DecayBend.serviceChanged() )
	{
		Serial.println("Decay changed");
		bendvelope1.decay( bv1Decay.getAsUInt8(), ((int16_t)bv1DecayBend.getAsUInt8() - 127 ) * -1);// 0 to 255 for length, -128 to 127
	}	
	if( bv1Sustain.serviceChanged() )
	{
		Serial.println("Sustain changed");
		bendvelope1.sustain( bv1Sustain.getAsUInt8() );// 0 to 255 for level
	}
	if( bv1Release.serviceChanged() || bv1ReleaseBend.serviceChanged() )
	{
		Serial.println("Release changed");
		bendvelope1.release( bv1Release.getAsUInt8(), (int16_t)bv1ReleaseBend.getAsUInt8() - 128 );// 0 to 255 for length, -128 to 127
	}

	//General knobs
	if( env2Attack.serviceChanged() )
	{
		envelope1.attack( env2Attack.getAsUInt8() );// 0 to 255 for length, -128 to 127
		Serial.print("Attack 2: ");
		Serial.println( env2Attack.getAsUInt8() );
	}	
	if( env2Decay.serviceChanged() )
	{
		envelope1.decay( env2Decay.getAsUInt8() * 3 );// 0 to 255 for length, -128 to 127
		Serial.print("Decay 2: ");
		Serial.println( env2Decay.getAsUInt8() );
	}	

	if( param1Knob.serviceChanged() )
	{
		Serial.print("Parameter 1: ");
		Serial.println( param1Knob.getAsInt16() );
		//control modulator 1 directly
		modulator[0].modGain.amplitude_int( param1Knob.getAsInt16() );// -32768 to 32768
		//control modulator 2 inversly
		modulator[1].modGain.amplitude_int( -1 * param1Knob.getAsInt16() );// -32768 to 32768
		//Double control for modulator 3
		uint64_t knobValue = param1Knob.getAsInt16() * 2;
		if( knobValue > 32767 ) knobValue = 32767;
		modulator[2].modGain.amplitude_int( knobValue );// -32768 to 32768
	}
	if( param2Knob.serviceChanged() )
	{
		Serial.print("Parameter 2: ");
		Serial.println( param2Knob.getAsInt16() );
		//lfo1Pitch.amplitude_int(((int16_t)lfo1Freq.getAsUInt8() - 128) << 8);
		lfo1.frequency(0.05 + ((float)param2Knob.getAsUInt8() / 50));
	}


	//Tone knob
	if( tone.serviceChanged() )
	{
		Serial.print("New Tone Setting: ");
		Serial.print(tone.getState());
		switch( tone.getState() )
		{
			case 0:
			waveShapeParams[0][0] = 0;
			waveShapeParams[0][1] = 255;
			waveShapeParams[0][2] = 0;
			break;
			case 1:
			waveShapeParams[0][0] = 80;
			waveShapeParams[0][1] = 255;
			waveShapeParams[0][2] = 0;
			break;
			case 2:
			waveShapeParams[0][0] = 150;
			waveShapeParams[0][1] = 255;
			waveShapeParams[0][2] = 0;
			break;
			case 3:
			waveShapeParams[0][0] = 0;
			waveShapeParams[0][1] = 100;
			waveShapeParams[0][2] = 150;
			break;
			case 4:
			waveShapeParams[0][0] = 0;
			waveShapeParams[0][1] = 0;
			waveShapeParams[0][2] = 200;
			break;
			case 5:
			waveShapeParams[0][0] = 0;
			waveShapeParams[0][1] = 0;
			waveShapeParams[0][2] = 0;
			break;
			default:
			break;
		}
		
		WaveGenerator testWave;
		testWave.setParameters( 255, waveShapeParams[0][0], waveShapeParams[0][1], waveShapeParams[0][2], waveShapeParams[0][3] );			
		if( oscAWaveSrc == 1 )
		{
			testWave.writeWaveU16_257( monoosc1.getPointer( 0 ) );
		}
		if( oscBWaveSrc == 1 )
		{
			testWave.writeWaveU16_257( monoosc2.getPointer( 0 ) );
		}
		if( oscCWaveSrc == 1 )
		{
			testWave.writeWaveU16_257( monoosc3.getPointer( 0 ) );
		}
		
	}
	
	if( effect.serviceChanged() )
	{
		Serial.print("New Effect Setting: ");
		Serial.println(effect.getState());
		//Find and turn off the effects
		for( int i = 0; i < 4; i++ )
		{
			if( modulator[i].connected == 1 )
			{
				//Print panel variables
				Serial.print("&modulator[i].effectMixer = ");
				uint32_t address = (uint32_t)&modulator[i].effectMixer;
				Serial.println(address, HEX);
				//Remove cords
				//search for connected cords for each modulator
				for( int j = 0; j < 3; j++ )
				{
					if( &modulator[i].effectMixer == effectPaths[j].associatedPatchCord->getSrc())
					{
						Serial.print("effectPaths[j].associatedPatchCord->getSrc() = ");
						address = (uint32_t)effectPaths[j].associatedPatchCord->getSrc();
						Serial.println(address, HEX);
						//passed modulator's input is attached to the effect path we're looking for
						modulator[i].remove(&effectPaths[j]);
					}
				}
			}
		}
		switch( effect.getState() )
		{
			case 0:
			dc1CentB.amplitude_int(0);
			dc1CentC.amplitude_int(-0);
			break;
			case 1:
			//Reconnect as detune
			dc1CentB.amplitude_int(1000);
			dc1CentC.amplitude_int(-1000);
			modulator[0].modOffset.amplitude_int( 0 );
			modulator[1].modOffset.amplitude_int( -0 );
			modulator[0].insert(&effectPaths[0], modSources[1].src, modSources[1].src_index);
			modulator[1].insert(&effectPaths[1], modSources[1].src, modSources[1].src_index);
			Serial.println("Inserted detune");

			break;
			case 2:
			//Reconnect as filter osc
			dc1CentB.amplitude_int(1);
			dc1CentC.amplitude_int(-1);
			modulator[0].modOffset.amplitude_int( 0 );
			modulator[0].insert(&effectPaths[2], modSources[2].src, modSources[2].src_index);
			Serial.println("Inserted filter");
			break;
			case 3:
			//Reconnect as env
			dc1CentB.amplitude_int(1);
			dc1CentC.amplitude_int(-1);
			modulator[2].modOffset.amplitude_int( 0 );
			modulator[2].insert(&effectPaths[2], modSources[1].src, modSources[1].src_index);
			Serial.println("Inserted env");
			break;
			case 4:
			//Reconnect as env and detune
			dc1CentB.amplitude_int(1);
			dc1CentC.amplitude_int(-1);
			modulator[0].modOffset.amplitude_int( 0 );
			modulator[1].modOffset.amplitude_int( -0 );
			modulator[2].modOffset.amplitude_int( 0 );
			modulator[0].insert(&effectPaths[0], modSources[1].src, modSources[1].src_index);
			modulator[1].insert(&effectPaths[1], modSources[1].src, modSources[1].src_index);
			modulator[2].insert(&effectPaths[2], modSources[1].src, modSources[1].src_index);
			Serial.println("Inserted env + detune");
			break;
			default:
			break;
		}
	}

	//Do main machine
	tickStateMachine();
	
	//Do something afterwards?
}

void P8Interface::tickStateMachine()
{
	//***** PROCESS THE LOGIC *****//
    //Now do the states.
    PStates nextState = state;
    switch( state )
    {
    case PInit:
		//Set glide rate

		oscLed1.setState(LEDON);
		
		oscAOctaveState = oscOctave.getState();
		oscBOctaveState = oscAOctaveState;
		oscCOctaveState = oscAOctaveState;
		
		dc1CentB.amplitude_int(500);
		dc1CentC.amplitude_int(-500);

		envelope1.sustain(0);
		
		nextState = PIdle;
		break;
	case PIdle:
		nextState = PIdle;
        break;
    default:
        nextState = PInit;
        break;
    }
	
    state = nextState;

}

