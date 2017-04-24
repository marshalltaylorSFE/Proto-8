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

//// GUItool: begin automatically generated code
//extern AudioSynthBendvelope     bendvelope1;    //xy=71,800
//extern AudioSynthBendvelope     bendvelope2;    //xy=103,1183
//extern AudioSynthWaveformDcBinary dc1A;           //xy=260,883
//extern AudioSynthWaveformDcBinary dc1CentA;       //xy=264,1013
//extern AudioSynthWaveformDcBinary dc1B;           //xy=321,920
//extern AudioSynthWaveformDcBinary dc1CentB;       //xy=331,1049
//extern AudioSynthWaveformDcBinary dc1C;           //xy=384,958
//extern AudioSynthWaveformDcBinary dc1CentC;       //xy=396,1084
//extern AudioSynthWaveformDcBinary dc1D;           //xy=449,994
//extern AudioSynthWaveformDcBinary dc1CentD;       //xy=457,1123
//extern AudioSynthMultiOsc       multiosc1;      //xy=696,1014
//extern AudioMixer4              mixer5;         //xy=872,1024
//extern AudioFilterStateVariable filter1;        //xy=1018,1034
//extern AudioFilterStateVariable filter2;        //xy=1164,1033
//extern AudioOutputI2SQuad       is_quad23;      //xy=1354,1042
//extern AudioConnection          patchCord1;
//extern AudioConnection          patchCord2;
//extern AudioConnection          patchCord3;
//extern AudioConnection          patchCord4;
//extern AudioConnection          patchCord5;
//extern AudioConnection          patchCord6;
//extern AudioConnection          patchCord7;
//extern AudioConnection          patchCord8;
//extern AudioConnection          patchCord9;
//extern AudioConnection          patchCord10;
//extern AudioConnection          patchCord11;
//extern AudioConnection          patchCord12;
//extern AudioConnection          patchCord13;
//extern AudioConnection          patchCord14;
//extern AudioConnection          patchCord15;
//extern AudioConnection          patchCord16;
//extern AudioControlSGTL5000     sgtl5000_1;     //xy=1308,897
//extern AudioControlSGTL5000     sgtl5000_2;     //xy=1312,853
//// GUItool: end automatically generated code

extern AudioSynthBendvelope     bendvelope1;    //xy=144.88888549804688,248
extern AudioSynthBendvelope     bendvelope2;    //xy=176.88888549804688,631
extern AudioSynthWaveformDcBinary dc1A;           //xy=320.8888854980469,331
extern AudioSynthWaveformDcBinary dc1CentA;       //xy=328.8888854980469,367
extern AudioSynthWaveformDcBinary dc1B;           //xy=347.8888854980469,402
extern AudioSynthWaveformDcBinary dc1CentB;       //xy=355.8888854980469,435
extern AudioSynthWaveformDcBinary dc1C;           //xy=378.8888854980469,469
extern AudioSynthWaveformDcBinary dc1CentC;       //xy=388.8888854980469,504
extern AudioSynthWaveformDcBinary dc1D;           //xy=412.8888854980469,541.0001525878906
extern AudioSynthWaveformDcBinary dc1CentD;       //xy=417.8888854980469,576.0000305175781
extern AudioSynthMultiOsc       multiosc1;      //xy=769.8888854980469,462
extern AudioMixer4              mixer5;         //xy=945.8888854980469,472
extern AudioFilterStateVariable filter1;        //xy=1091.8888854980469,482
extern AudioFilterStateVariable filter2;        //xy=1237.8888854980469,481
extern AudioOutputI2SQuad       is_quad23;      //xy=1427.8888854980469,490
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
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1381.8888854980469,345
extern AudioControlSGTL5000     sgtl5000_2;     //xy=1385.8888854980469,301

#define CordDCPA patchCord2
#define CordDCCA patchCord3
#define CordDCPB patchCord4
#define CordDCCB patchCord5
#define CordDCPC patchCord6
#define CordDCCC patchCord7
#define CordDCPD patchCord8
#define CordDCCD patchCord9

extern ModulatorBlock modulator[4];

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	busState = BInit;
	
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
	
	srcMapping[1] = 1;
	srcMapping[2] = 2;
	srcMapping[3] = 3;
	srcMapping[4] = 4;

	destMapping[1] = 5;
	destMapping[2] = 6;
	destMapping[3] = 7;
	destMapping[4] = 8;

}

void P8Interface::reset( void )
{
	//Set explicit states
	//Set all LED off
	LEDs.clear();
	modSources[0].set( &bendvelope2, 0 );

	effectPaths[0].set(&CordDCPA);
	effectPaths[1].set(&CordDCCA);
	effectPaths[2].set(&CordDCPB);
	effectPaths[3].set(&CordDCCB);
	effectPaths[4].set(&CordDCPC);
	effectPaths[5].set(&CordDCCC);
	effectPaths[6].set(&CordDCPD);
	effectPaths[7].set(&CordDCCD);	
	
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
		modulator[0].modGain.amplitude_int( ampCalc );// 0 to 255 for length, -128 to 127
		modulator[0].modOffset.amplitude_int( offsetCalc );
	}	
	
	//Misc knobs
	if( masterVolume.serviceChanged() )
	{
		sgtl5000_1.volume(((float)masterVolume.getState() / 256) * 1);
		sgtl5000_2.volume(((float)masterVolume.getState() / 256) * 1);
	}
	//if( Select.serviceChanged() )
	//{
	//	effectMixer.gain(0, ((float)Select.getState() - 127)/256);
	//}
	
	//Do main machine
	tickStateMachine();
	tickBusStateMachine();
	tickBusDestStateMachine();
	
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
uint8_t tempOscAState = 0;
void P8Interface::tickBusStateMachine( void )
{
	//if( oscASync.serviceRisingEdge() )
	//{
	//	if(tempOscAState == 0)
	//	{
	//		tempOscAState = 1;
	//		modulator.insert(&effectPaths[6], &bendvelope2, 0);
	//	}
	//	else
	//	{
	//		tempOscAState = 0;
	//		modulator.remove(&effectPaths[6]);
	//	}
    //
	//}

	uint8_t srcPick[6];
	srcPick[0] = 0;
	srcPick[1] = bus1SrcPick.serviceRisingEdge();
	srcPick[2] = bus2SrcPick.serviceRisingEdge();
	srcPick[3] = bus3SrcPick.serviceRisingEdge();
	srcPick[4] = bus4SrcPick.serviceRisingEdge();
	srcPick[5] = 0;

	int srcBtn = 0;
	for( int i = 1; i < 5; i++)
	{
		if( srcPick[i] )
		{
			srcBtn = i; // low priority
			i = 10;//break;
		}
		//else srcBtn remains 0
	}

	uint8_t destPick[6];
	destPick[0] = 0;
	destPick[1] = bus1DestPick.serviceRisingEdge();
	destPick[2] = bus2DestPick.serviceRisingEdge();
	destPick[3] = bus3DestPick.serviceRisingEdge();
	destPick[4] = bus4DestPick.serviceRisingEdge();
	destPick[5] = 0;

    //Detect held conditions
	int destBtn = 0;
	for( int i = 1; i < 5; i++)
	{
		if( destPick[i] )
		{
			destBtn = i; // low priority
			i = 10;//break;
		}
		//else destBtn remains 0
	}
	if(srcBtn||destBtn)printDebugInfo();
	BusStates nextState = busState;
	
    switch( busState )
    {
    case BInit:
		modulator[0].init();
		modulator[1].init();
		modulator[2].init();
		modulator[3].init();

		srcBusSelected = 0;
		srcCursorOn = 0;
		destBusSelected = 0;
		destCursorOn = 0;

		displayBusMapping();
		
		nextState = BShowAll;
		break;
	case BShowAll:
		if( srcBtn )
		{
			//new button
			srcBusSelected = srcBtn;
			srcCursorOn = 1;
			destBusSelected = srcBtn;
			displayBusMapping();
			nextState = BPickSrc;
		}
		if( destBtn )
		{
			//new button
			destCursorOn = 1;
			destBusSelected = destBtn;
			srcBusSelected = destBtn;
			displayBusMapping();
			nextState = BPickDest;
		}
		break;
	case BPickSrc:
		if( srcBtn )
		{
			if( srcBusSelected != srcBtn )
			{
				//new button
				srcBusSelected = srcBtn;
				destBusSelected = srcBtn;
				srcCursorOn = 1;
				displayBusMapping();
			}
			else
			{
				if( srcCursor ) //if cursor not zero
				{
					if( srcCursor == srcMapping[ srcBusSelected ]) //if same
					{
						srcMapping[ srcBusSelected ] = 0;
					}
					else
					{
						//if valid.. (TODO: WRITE)
						srcMapping[ srcBusSelected ] = srcCursor;
					}
				}
				//display
				srcBusSelected = 0;
				srcCursorOn = 0;
				destBusSelected = 0;
				destCursorOn = 0;
				displayBusMapping();
				nextState = BShowAll;
			}
		}
		if( destBtn )
		{
			//new button
			destCursorOn = 1;
			destBusSelected = destBtn;
			srcBusSelected = destBtn;
			srcCursorOn = 0;
			displayBusMapping();
			nextState = BPickDest;
		}
		break;
	case BPickDest:
		if( destBtn )
		{
			if( destBusSelected != destBtn )
			{
				Serial.println("destBusSelected != destBtn");
				//new button
				destBusSelected = destBtn;
				srcBusSelected = destBtn;
				destCursorOn = 1;
				displayBusMapping();
			}
			else
			{
				Serial.println("destBusSelected == destBtn");
				if( destCursor )
				{
					//Print panel variables
					Serial.println("destCursor detected");
					Serial.print("destMapping[destBusSelected]: ");
					Serial.println(destMapping[destBusSelected]);
					//Check if cursor is selecting the current mapping
					if( destCursor == destMapping[destBusSelected])
					{
						Serial.println("destCursor == destMapping[destBusSelected]");
						//Find and turn off the effect
						for( int i = 0; i < 4; i++ )
						{
							if( modulator[i].connected == 1 )
							{
								//Print panel variables
								Serial.print("destMapping[destBusSelected]: ");
								Serial.println(destMapping[destBusSelected]);
								Serial.print("&modulator[i].effectMixer = ");
								uint32_t address = (uint32_t)&modulator[i].effectMixer;
								Serial.println(address, HEX);
								Serial.print("effectPaths[destMapping[destBusSelected]-1].associatedPatchCord->getSrc() = ");
								address = (uint32_t)effectPaths[destMapping[destBusSelected]-1].associatedPatchCord->getSrc();
								Serial.println(address, HEX);
                
								//connected to something...
								if( &modulator[i].effectMixer == effectPaths[destMapping[destBusSelected]-1].associatedPatchCord->getSrc())
								{
									//passed modulator's input is attached to the effect path we're looking for
									modulator[i].remove(&effectPaths[destMapping[destBusSelected]-1]);
								}
							}
						}
						destMapping[destBusSelected] = 0;
						
					}
					else
					{
						Serial.println("destCursor != destMapping[destBusSelected]");
						//if valid..
						//Print panel variables
						//Serial.print("destMapping[destBusSelected]: ");
						//Serial.println(destMapping[destBusSelected]);
						//if( effectPaths[destMapping[destBusSelected]-1].associatedPatchCord != NULL )
						Serial.print("destCursor - 1 = ");
						Serial.println(destCursor - 1);
						if( effectPaths[destCursor - 1].associatedPatchCord != NULL )
						{
							uint8_t recorded = 0;
							//Find a vacent slot and turn on the effect
							for( int i = 0; (i < 4)&&(recorded == 0); i++ )
							{
								if( modulator[i].connected == 0 )
								{
									//Free space found
									//Record change
									destMapping[ destBusSelected ] = destCursor;
									recorded = 1;
									//apply change
									Serial.print("Inserting, destMapping[destBusSelected]: ");
									Serial.println(destMapping[destBusSelected]);
									modulator[i].insert(&effectPaths[destMapping[destBusSelected]-1], modSources[srcMapping[srcBusSelected]-1].src, modSources[srcMapping[srcBusSelected]-1].src_index);
									
								}
							}
						}
					}
				}
				//display
				srcBusSelected = 0;
				srcCursorOn = 0;
				destBusSelected = 0;
				destCursorOn = 0;
				displayBusMapping();
				nextState = BShowAll;
			}
		}
		if( srcBtn )
		{
			//new button
			srcBusSelected = srcBtn;
			srcCursorOn = 1;
			destBusSelected = srcBtn;
			destCursorOn = 0;
			displayBusMapping();
			nextState = BPickSrc;
		}
		break;
    default:
        nextState = BInit;
        break;
    }
    busState = nextState;

	//Check cursor movement
	if( Select.serviceChanged() )
	{
		uint8_t variable = Select.getState();
		if(variable)
		{
			//If variable = 1 (almost full CCW), output = 15
			srcCursor = 16 - variable; // 16 points
			destCursor = 16 - variable; // 16 points
		}
		displayBusMapping();
		Serial.println(Select.getState());
		Serial.println(srcBusSelected);
		Serial.println(srcCursorOn);
	}
	
}

void P8Interface::printDebugInfo( void )
{
	uint32_t address;
	Serial.println("*****BUTTONPRESS*****");
	//Print panel variables
	Serial.print("srcBusSelected: ");
	Serial.println(srcBusSelected);
	Serial.print("destBusSelected: ");
	Serial.println(destBusSelected);
	Serial.print("srcCursor: ");
	Serial.println(srcCursor);
	Serial.print("destCursor: ");
	Serial.println(destCursor);
	//print srcmapping
	for( int i = 0; i < 6; i++ )
	{
		Serial.print("srcMapping[");
		Serial.print(i);
		Serial.print("] = ");
		Serial.println(srcMapping[i]);
	}
	//Print modSources
	for( int i = 0; i < 15; i++ )
	{
		Serial.print("modSources[");
		Serial.print(i);
		Serial.print("].src = ");
		address = (uint32_t)modSources[i].src;
		Serial.println(address, HEX);
	}
	//Print destBusSelected
	for( int i = 0; i < 6; i++ )
	{
		Serial.print("destMapping[");
		Serial.print(i);
		Serial.print("] = ");
		Serial.println(destMapping[i]);
	}
//	//Print effectPaths
//	for( int i = 0; i < 15; i++ )
//	{
//		Serial.print("effectPaths[");
//		Serial.print(i);
//		Serial.print("].associatedPatchCord->getDst() = ");
//		address = (uint32_t)effectPaths[i].associatedPatchCord->getDst();
//		Serial.println(address, HEX);
//	}
	//Print effectPaths
	for( int i = 0; i < 15; i++ )
	{
		Serial.print("effectPaths[");
		Serial.print(i);
		Serial.print("]:   .src = ");
		address = (uint32_t)effectPaths[i].src;
		Serial.print(address, HEX);
		Serial.print("   .src_index = ");
		Serial.print(effectPaths[i].src_index, HEX);
		Serial.print("   .associatedPatchCord->getDst() = ");
		address = (uint32_t)effectPaths[i].associatedPatchCord->getDst();
		Serial.println(address, HEX);
	}
	//Print destBusSelected
	for( int i = 0; i < 4; i++ )
	{
		Serial.print("&modulator[");
		Serial.print(i);
		Serial.print("].effectMixer = ");
		address = (uint32_t)&modulator[i].effectMixer;
		Serial.println(address, HEX);
	}
	for( int i = 0; i < 4; i++ )
	{
		Serial.print("&modulator[");
		Serial.print(i);
		Serial.print("].connected = ");
		Serial.println(modulator[i].connected, HEX);
	}
}
void P8Interface::tickBusDestStateMachine( void )
{
}

void P8Interface::displayBusMapping( void )
{
	//Turn everything off
	bus1SrcLed.setState(LEDOFF);
	bus1DestLed.setState(LEDOFF);
	bus2SrcLed.setState(LEDOFF);
	bus2DestLed.setState(LEDOFF);
	bus3SrcLed.setState(LEDOFF);
	bus3DestLed.setState(LEDOFF);
	bus4SrcLed.setState(LEDOFF);
	bus4DestLed.setState(LEDOFF);
	bus5SrcLed.setState(LEDOFF);
	bus5DestLed.setState(LEDOFF);

	
	ledState_t srcLEDTable[15];
	for( int i = 0; i < 15; i++ ) srcLEDTable[i] = LEDOFF;

	//Show Source Column by state machine variables
	ledState_t ledType = LEDON;//LEDFLASHING
	if( srcCursorOn ) ledType = LEDFLASHING;
	switch( srcBusSelected )
	{
		case 0: //None selected, OR
		if(srcMapping[1])srcLEDTable[srcMapping[1]-1] = LEDON;
		if(srcMapping[2])srcLEDTable[srcMapping[2]-1] = LEDON;
		if(srcMapping[3])srcLEDTable[srcMapping[3]-1] = LEDON;
		if(srcMapping[4])srcLEDTable[srcMapping[4]-1] = LEDON;
		
		break;
		case 1:
		if(srcMapping[1])srcLEDTable[srcMapping[1]-1] = LEDON;
		bus1SrcLed.setState(ledType);
		break;
		case 2:
		if(srcMapping[2])srcLEDTable[srcMapping[2]-1] = LEDON;
		bus2SrcLed.setState(ledType);
		break;
		case 3:
		if(srcMapping[3])srcLEDTable[srcMapping[3]-1] = LEDON;
		bus3SrcLed.setState(ledType);
		break;
		case 4:
		if(srcMapping[4])srcLEDTable[srcMapping[4]-1] = LEDON;
		bus4SrcLed.setState(ledType);
		break;
		case 5:
		bus5SrcLed.setState(ledType);
		break;
		default:
		break;
	}
	
	ledState_t destLEDTable[15];
	for( int i = 0; i < 15; i++ ) destLEDTable[i] = LEDOFF;

	//Show Source Column by state machine variables
	ledType = LEDON;//LEDFLASHING
	if( destCursorOn ) ledType = LEDFLASHING;
	switch( destBusSelected )
	{
		case 0: //None selected, OR
		if(destMapping[1])destLEDTable[destMapping[1]-1] = LEDON;
		if(destMapping[2])destLEDTable[destMapping[2]-1] = LEDON;
		if(destMapping[3])destLEDTable[destMapping[3]-1] = LEDON;
		if(destMapping[4])destLEDTable[destMapping[4]-1] = LEDON;
		
		break;
		case 1:
		if(destMapping[1])destLEDTable[destMapping[1]-1] = LEDON;
		bus1DestLed.setState(ledType);
		break;
		case 2:
		if(destMapping[2])destLEDTable[destMapping[2]-1] = LEDON;
		bus2DestLed.setState(ledType);
		break;
		case 3:
		if(destMapping[3])destLEDTable[destMapping[3]-1] = LEDON;
		bus3DestLed.setState(ledType);
		break;
		case 4:
		if(destMapping[4])destLEDTable[destMapping[4]-1] = LEDON;
		bus4DestLed.setState(ledType);
		break;
		case 5:
		bus5DestLed.setState(ledType);
		break;
		default:
		break;
	}

	//Draw cursor
	if( ( srcCursor > 0 ) && srcCursorOn )
	{
		srcLEDTable[srcCursor-1] = LEDFLASHING;
	}
	//Draw cursor
	if( ( destCursor > 0 ) && destCursorOn )
	{
		destLEDTable[destCursor-1] = LEDFLASHING;
	}
	
	modSrcLed0.setState(srcLEDTable[0]);
	modSrcLed1.setState(srcLEDTable[1]);
	modSrcLed2.setState(srcLEDTable[2]);
	modSrcLed3.setState(srcLEDTable[3]);
	modSrcLed4.setState(srcLEDTable[4]);
	modSrcLed5.setState(srcLEDTable[5]);
	modSrcLed6.setState(srcLEDTable[6]);
	modSrcLed7.setState(srcLEDTable[7]);
	modSrcLed8.setState(srcLEDTable[8]);
	modSrcLed9.setState(srcLEDTable[9]);
	modSrcLed10.setState(srcLEDTable[10]);
	modSrcLed11.setState(srcLEDTable[11]);
	modSrcLed12.setState(srcLEDTable[12]);
	modSrcLed13.setState(srcLEDTable[13]);
	modSrcLed14.setState(srcLEDTable[14]);
	
	modDestLed0.setState(destLEDTable[0]);
	modDestLed1.setState(destLEDTable[1]);
	modDestLed2.setState(destLEDTable[2]);
	modDestLed3.setState(destLEDTable[3]);
	modDestLed4.setState(destLEDTable[4]);
	modDestLed5.setState(destLEDTable[5]);
	modDestLed6.setState(destLEDTable[6]);
	modDestLed7.setState(destLEDTable[7]);
	modDestLed8.setState(destLEDTable[8]);
	modDestLed9.setState(destLEDTable[9]);
	modDestLed10.setState(destLEDTable[10]);
	modDestLed11.setState(destLEDTable[11]);
	modDestLed12.setState(destLEDTable[12]);
	modDestLed13.setState(destLEDTable[13]);
	modDestLed14.setState(destLEDTable[14]);

	
	
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