//**********************************************************************//
//
//  Panel example for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//
//**********************************************************************//
#include "Arduino.h"
#include "P8Panel.h"
#include "panelComponents.h"
#include "proto-8PanelComponents.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"
#include <typeinfo>   // operator typeid


//This is where PanelComponents are joined to form the custom panel


P8Panel::P8Panel( void )
{
	//Bendvelope1
	bv1Attack.setHardware(new Proto8AnalogIn( 25 ));
	add( &bv1Attack );
	bv1AttackBend.setHardware(new Proto8AnalogIn( 24 ));
	add( &bv1AttackBend );
	bv1Hold.setHardware(new Proto8AnalogIn( 26 ));
	add( &bv1Hold );
	bv1Decay.setHardware(new Proto8AnalogIn( 28 ));
	add( &bv1Decay );
	bv1DecayBend.setHardware(new Proto8AnalogIn( 27 ));
	add( &bv1DecayBend );
	bv1Sustain.setHardware(new Proto8AnalogIn( 29 ));
	add( &bv1Sustain );
	bv1Release.setHardware(new Proto8AnalogIn( 30 ));
	add( &bv1Release );
	bv1ReleaseBend.setHardware(new Proto8AnalogIn( 31 ));
	add( &bv1ReleaseBend );
	//bv1Select
	//bv1Select.init(32, 255, 0 ); //With max and min ranges
	//add( &bv1Select );
	bv1Trigger.setHardware(new Proto8DigitalOut( 41 ), 0);
	add( &bv1Trigger );
	
	//Bendvelope2
	bv2Attack.setHardware(new Proto8AnalogIn( 16 ));
	add( &bv2Attack );
	bv2AttackBend.setHardware(new Proto8AnalogIn( 15 ));
	add( &bv2AttackBend );
	bv2Hold.setHardware(new Proto8AnalogIn( 17 ));
	add( &bv2Hold );
	bv2Decay.setHardware(new Proto8AnalogIn( 19 ));
	add( &bv2Decay );
	bv2DecayBend.setHardware(new Proto8AnalogIn( 18 ));
	add( &bv2DecayBend );
	bv2Sustain.setHardware(new Proto8AnalogIn( 20 ));
	add( &bv2Sustain );
	bv2Release.setHardware(new Proto8AnalogIn( 21 ));
	add( &bv2Release );
	bv2ReleaseBend.setHardware(new Proto8AnalogIn( 22 ));
	add( &bv2ReleaseBend );
	//bv2Select
	//bv2Select.init(23, 255, 0 ); //With max and min ranges
//	add( &bv2Select );
	bv2Trigger.setHardware(new Proto8DigitalOut( 42 ), 0);
	add( &bv2Trigger );
	
	//Bus
	bus1Amp.setHardware(new Proto8AnalogIn( 13 ));
	bus1Amp.setWindow( 10 );
	add( &bus1Amp );
	bus1Offset.setHardware(new Proto8AnalogIn( 14 ));
	bus1Offset.setWindow( 10 );
	add( &bus1Offset );
	bus1SrcPick.setHardware(new Proto8DigitalIn( 5,1 ), 0);
	add( &bus1SrcPick );
	bus1DestPick.setHardware(new Proto8DigitalIn( 4,1 ), 0);
	add( &bus1DestPick );
	bus1SrcLed.setHardware(new Proto8DigitalOut( 15 ), 0);
	add( &bus1SrcLed );
	bus1DestLed.setHardware(new Proto8DigitalOut( 25 ), 0);
	add( &bus1DestLed );
	
	bus2Amp.setHardware(new Proto8AnalogIn( 11 ));
	add( &bus2Amp );
	bus2Offset.setHardware(new Proto8AnalogIn( 12 ));
	add( &bus2Offset );
	bus2SrcPick.setHardware(new Proto8DigitalIn( 5,2 ), 0);
	add( &bus2SrcPick );
	bus2DestPick.setHardware(new Proto8DigitalIn( 4,2 ), 0);
	add( &bus2DestPick );
	bus2SrcLed.setHardware(new Proto8DigitalOut( 14 ), 0);
	add( &bus2SrcLed );
	bus2DestLed.setHardware(new Proto8DigitalOut( 24 ), 0);
	add( &bus2DestLed );

	bus3Amp.setHardware(new Proto8AnalogIn( 9 ));
	add( &bus3Amp );
	bus3Offset.setHardware(new Proto8AnalogIn( 10 ));
	add( &bus3Offset );
	bus3SrcPick.setHardware(new Proto8DigitalIn( 5,3 ), 0);
	add( &bus3SrcPick );
	bus3DestPick.setHardware(new Proto8DigitalIn( 4,3 ), 0);
	add( &bus3DestPick );
	bus3SrcLed.setHardware(new Proto8DigitalOut( 13 ), 0);
	add( &bus3SrcLed );
	bus3DestLed.setHardware(new Proto8DigitalOut( 23 ), 0);
	add( &bus3DestLed );

	bus4Amp.setHardware(new Proto8AnalogIn( 7 ));
	add( &bus4Amp );
	bus4Offset.setHardware(new Proto8AnalogIn( 8 ));
	add( &bus4Offset );
	bus4SrcPick.setHardware(new Proto8DigitalIn( 5,4 ), 0);
	add( &bus4SrcPick );
	bus4DestPick.setHardware(new Proto8DigitalIn( 4,4 ), 0);
	add( &bus4DestPick );
	bus4SrcLed.setHardware(new Proto8DigitalOut( 12 ), 0);
	add( &bus4SrcLed );
	bus4DestLed.setHardware(new Proto8DigitalOut( 22 ), 0);
	add( &bus4DestLed );

	bus5Amp.setHardware(new Proto8AnalogIn( 5 ));
	add( &bus5Amp );
	bus5Offset.setHardware(new Proto8AnalogIn( 6 ));
	add( &bus5Offset );
	bus5SrcPick.setHardware(new Proto8DigitalIn( 6,1 ), 0);//Both want 6,1 ... Need to be rewired!  But bus 5 is last to be implemented...
	add( &bus5SrcPick );
	bus5DestPick.setHardware(new Proto8DigitalIn( 6,1 ), 0);//Both want 6,1 ... Need to be rewired!  But bus 5 is last to be implemented...
	add( &bus5DestPick );
	bus5SrcLed.setHardware(new Proto8DigitalOut( 11 ), 0);
	add( &bus5SrcLed );
	bus5DestLed.setHardware(new Proto8DigitalOut( 21 ), 0);
	add( &bus5DestLed );
	
	modSrcLed0.setHardware(new Proto8DigitalOut( 16 ), 0);
	modSrcLed1.setHardware(new Proto8DigitalOut( 17 ), 0);
	modSrcLed2.setHardware(new Proto8DigitalOut( 18 ), 0);
	modSrcLed3.setHardware(new Proto8DigitalOut( 19 ), 0);
	modSrcLed4.setHardware(new Proto8DigitalOut( 20 ), 0);
	modSrcLed5.setHardware(new Proto8DigitalOut( 1 ), 0);
	modSrcLed6.setHardware(new Proto8DigitalOut( 2 ), 0);
	modSrcLed7.setHardware(new Proto8DigitalOut( 3 ), 0);
	modSrcLed8.setHardware(new Proto8DigitalOut( 4 ), 0);
	modSrcLed9.setHardware(new Proto8DigitalOut( 5 ), 0);
	modSrcLed10.setHardware(new Proto8DigitalOut( 6 ), 0);
	modSrcLed11.setHardware(new Proto8DigitalOut( 7 ), 0);
	modSrcLed12.setHardware(new Proto8DigitalOut( 8 ), 0);
	modSrcLed13.setHardware(new Proto8DigitalOut( 9 ), 0);
	modSrcLed14.setHardware(new Proto8DigitalOut( 10 ), 0);
	add( &modSrcLed0 );
	add( &modSrcLed1 );
	add( &modSrcLed2 );
	add( &modSrcLed3 );
	add( &modSrcLed4 );
	add( &modSrcLed5 );
	add( &modSrcLed6 );
	add( &modSrcLed7 );
	add( &modSrcLed8 );
	add( &modSrcLed9 );
	add( &modSrcLed10 );
	add( &modSrcLed11 );
	add( &modSrcLed12 );
	add( &modSrcLed13 );
	add( &modSrcLed14 );
	
	modDestLed0.setHardware(new Proto8DigitalOut( 26 ), 0);
	modDestLed1.setHardware(new Proto8DigitalOut( 27 ), 0);
	modDestLed2.setHardware(new Proto8DigitalOut( 28 ), 0);
	modDestLed3.setHardware(new Proto8DigitalOut( 29 ), 0);
	modDestLed4.setHardware(new Proto8DigitalOut( 30 ), 0);
	modDestLed5.setHardware(new Proto8DigitalOut( 31 ), 0);
	modDestLed6.setHardware(new Proto8DigitalOut( 32 ), 0);
	modDestLed7.setHardware(new Proto8DigitalOut( 33 ), 0);
	modDestLed8.setHardware(new Proto8DigitalOut( 34 ), 0);
	modDestLed9.setHardware(new Proto8DigitalOut( 35 ), 0);
	modDestLed10.setHardware(new Proto8DigitalOut( 36 ), 0);
	modDestLed11.setHardware(new Proto8DigitalOut( 37 ), 0);
	modDestLed12.setHardware(new Proto8DigitalOut( 38 ), 0);
	modDestLed13.setHardware(new Proto8DigitalOut( 39 ), 0);
	modDestLed14.setHardware(new Proto8DigitalOut( 40 ), 0);
	add( &modDestLed0 );
	add( &modDestLed1 );
	add( &modDestLed2 );
	add( &modDestLed3 );
	add( &modDestLed4 );
	add( &modDestLed5 );
	add( &modDestLed6 );
	add( &modDestLed7 );
	add( &modDestLed8 );
	add( &modDestLed9 );
	add( &modDestLed10 );
	add( &modDestLed11 );
	add( &modDestLed12 );
	add( &modDestLed13 );
	add( &modDestLed14 );
	
	//Master
	masterCoarseTune.setHardware(new Proto8AnalogIn( 62 ));
	add( &masterCoarseTune );
	masterFineTune.setHardware(new Proto8AnalogIn( 63 ));
	add( &masterFineTune );
	masterVolume.setHardware(new Proto8AnalogIn( 64 ));
	add( &masterVolume );
	
	//LFO1
	lfo1Freq.setHardware(new Proto8AnalogIn( 61 ));
	add( &lfo1Freq );
	lfo1Shape.setHardware(new Proto8DigitalIn( 1,3 ), 0);
	add( &lfo1Shape );
	lfo1Led1.setHardware(new Proto8DigitalOut( 62 ), 0);
	add( &lfo1Led1 );
	lfo1Led2.setHardware(new Proto8DigitalOut( 63 ), 0);
	add( &lfo1Led2 );
	lfo1Led3.setHardware(new Proto8DigitalOut( 64 ), 0);
	add( &lfo1Led3 );
	
	//LFO2
	lfo2Freq.setHardware(new Proto8AnalogIn( 60 ));
	add( &lfo2Freq );
	lfo2Shape.setHardware(new Proto8DigitalIn( 1,4 ), 0);
	add( &lfo2Shape );
	lfo2Led1.setHardware(new Proto8DigitalOut( 59 ), 0);
	add( &lfo2Led1 );
	lfo2Led2.setHardware(new Proto8DigitalOut( 60 ), 0);
	add( &lfo2Led2 );
	lfo2Led3.setHardware(new Proto8DigitalOut( 61 ), 0);	
	add( &lfo2Led3 );
	
	//OSCA
	oscAPitch.setHardware(new Proto8AnalogIn( 56 ));
	oscAPitch.setWindow( 10 );
	add( &oscAPitch );
	oscAOctave.setHardware(new Proto8AnalogIn( 57 ));
	oscAOctave.init(673, 373, 4); //With max, min, points
	add( &oscAOctave );
	//oscASyncLed.setHardware(new Proto8DigitalOut( xxx ), 0);
//	add( &oscASyncLed );
	oscASync.setHardware(new Proto8DigitalIn( 3,1 ), 0);
	add( &oscASync );
	oscACent.setHardware(new Proto8AnalogIn( 58 ));
	oscACent.setWindow( 10 );
	add( &oscACent );
	oscAShape.setHardware(new Proto8DigitalIn( 2,1 ), 0);
	add( &oscAShape );
	oscALed1.setHardware(new Proto8DigitalOut( 56 ), 0);
	add( &oscALed1 );
	oscALed2.setHardware(new Proto8DigitalOut( 57 ), 0);
	add( &oscALed2 );
	oscALed3.setHardware(new Proto8DigitalOut( 58 ), 0);
	add( &oscALed3 );
	oscAPreAmp.setHardware(new Proto8AnalogIn( 59 ));
	add( &oscAPreAmp );
	
	//OSCB
	oscBPitch.setHardware(new Proto8AnalogIn( 52 ));
	oscBPitch.setWindow( 10 );
	add( &oscBPitch );
	oscBOctave.setHardware(new Proto8AnalogIn( 53 ));
	oscBOctave.init(750, 380, 4); //With max, min, points
	add( &oscBOctave );
	oscBSyncLed.setHardware(new Proto8DigitalOut( 46 ), 0);
	add( &oscBSyncLed );
	oscBSync.setHardware(new Proto8DigitalIn( 3,2 ), 0);
	add( &oscBSync );
	oscBCent.setHardware(new Proto8AnalogIn( 54 ));
	oscBPitch.setWindow( 10 );
	add( &oscBCent );
	oscBShape.setHardware(new Proto8DigitalIn( 2,2 ), 0);
	add( &oscBShape );
	oscBLed1.setHardware(new Proto8DigitalOut( 53 ), 0);
	add( &oscBLed1 );
	oscBLed2.setHardware(new Proto8DigitalOut( 54 ), 0);
	add( &oscBLed2 );
	oscBLed3.setHardware(new Proto8DigitalOut( 55 ), 0);
	add( &oscBLed3 );
	oscBPreAmp.setHardware(new Proto8AnalogIn( 55 ));
	add( &oscBPreAmp );

	//OSCC
	oscCPitch.setHardware(new Proto8AnalogIn( 48 ));
	add( &oscCPitch );
	oscCOctave.setHardware(new Proto8AnalogIn( 49 ));
	oscCOctave.init(185, 71, 4); //With max, min, points
	add( &oscCOctave );
	oscCSyncLed.setHardware(new Proto8DigitalOut( 45 ), 0);
	add( &oscCSyncLed );
	oscCSync.setHardware(new Proto8DigitalIn( 3,3 ), 0);
	add( &oscCSync );
	oscCCent.setHardware(new Proto8AnalogIn( 50 ));
	add( &oscCCent );
	oscCShape.setHardware(new Proto8DigitalIn( 2,3 ), 0);
	add( &oscCShape );
	oscCLed1.setHardware(new Proto8DigitalOut( 50 ), 0);
	add( &oscCLed1 );
	oscCLed2.setHardware(new Proto8DigitalOut( 51 ), 0);
	add( &oscCLed2 );
	oscCLed3.setHardware(new Proto8DigitalOut( 52 ), 0);
	add( &oscCLed3 );
	oscCPreAmp.setHardware(new Proto8AnalogIn( 51 ));
	add( &oscCPreAmp );

	//OSCD
	oscDPitch.setHardware(new Proto8AnalogIn( 44 ));
	add( &oscDPitch );
	oscDOctave.setHardware(new Proto8AnalogIn( 45 ));
	oscDOctave.init(185, 71, 4); //With max, min, points
	add( &oscDOctave );
	oscDSyncLed.setHardware(new Proto8DigitalOut( 44 ), 0);
	add( &oscDSyncLed );
	oscDSync.setHardware(new Proto8DigitalIn( 3,4 ), 0);
	add( &oscDSync );
	oscDCent.setHardware(new Proto8AnalogIn( 46 ));
	add( &oscDCent );
	oscDShape.setHardware(new Proto8DigitalIn( 2,4 ), 0);
	add( &oscDShape );
	oscDLed1.setHardware(new Proto8DigitalOut( 47 ), 0);
	add( &oscDLed1 );
	oscDLed2.setHardware(new Proto8DigitalOut( 48 ), 0);
	add( &oscDLed2 );
	oscDLed3.setHardware(new Proto8DigitalOut( 49 ), 0);
	add( &oscDLed3 );
	oscDPreAmp.setHardware(new Proto8AnalogIn( 47 ));
	add( &oscDPreAmp );
	
	//Wave Shape
	wave1Ramp.setHardware(new Proto8AnalogIn( 39 ));
	add( &wave1Ramp );
	wave1Sine.setHardware(new Proto8AnalogIn( 36 ));
	add( &wave1Sine );
	wave1Pulse.setHardware(new Proto8AnalogIn( 33 ));
	add( &wave1Pulse );
	wave2Ramp.setHardware(new Proto8AnalogIn( 40 ));
	add( &wave2Ramp );
	wave2Sine.setHardware(new Proto8AnalogIn( 37 ));
	add( &wave2Sine );
	wave2Pulse.setHardware(new Proto8AnalogIn( 34 ));
	add( &wave2Pulse );
	wave3Width.setHardware(new Proto8AnalogIn( 38 ));
	add( &wave3Width );
	wave3Pulse.setHardware(new Proto8AnalogIn( 35 ));
	add( &wave3Pulse );
	
	//General
	Select.setHardware(new Proto8AnalogIn( 43 ));
	Select.init(1023, 0, 16); //With max, min, points
	add( &Select );
}

//This function walks through the linked list and prints information about it.
void P8Panel::PrintPanelState( void )
{
	ListObject * tempObject = componentList;
	if( tempObject == NULL )
	{
		Serial.println("No objects");
		 return;
	}
	//call all contained objects' freshen
	while( tempObject != NULL )
	{
		Serial.print("ListObject: ");
		Serial.println((uint32_t)&(*tempObject), HEX);
		Serial.print("ListObject->component: ");
		Serial.println((uint32_t)&(*tempObject->component), HEX);
		//Advance linked list:
		tempObject = tempObject->next;
	}
	//Print synth specific stuff
	Serial.println();
	
	//Bendvelope1
	Serial.print("AAHDDSRR Envelope 1: ");
	Serial.print(bv1Attack.getState());
	Serial.print(", ");
	Serial.print(bv1AttackBend.getState());
	Serial.print(", ");
	Serial.print(bv1Hold.getState());
	Serial.print(", ");
	Serial.print(bv1Decay.getState());
	Serial.print(", ");
	Serial.print(bv1DecayBend.getState());
	Serial.print(", ");
	Serial.print(bv1Sustain.getState());
	Serial.print(", ");
	Serial.print(bv1Release.getState());
	Serial.print(", ");
	Serial.print(bv1ReleaseBend.getState());
	Serial.print(", ");
	Serial.print(bv1Select.getState());
	Serial.println();

	Serial.print("Trig LED state: ");
	Serial.println(bv1Trigger.getState());

	//Bendvelope2
	Serial.print("AAHDDSRR Envelope 2: ");
	Serial.print(bv2Attack.getState());
	Serial.print(", ");
	Serial.print(bv2AttackBend.getState());
	Serial.print(", ");
	Serial.print(bv2Hold.getState());
	Serial.print(", ");
	Serial.print(bv2Decay.getState());
	Serial.print(", ");
	Serial.print(bv2DecayBend.getState());
	Serial.print(", ");
	Serial.print(bv2Sustain.getState());
	Serial.print(", ");
	Serial.print(bv2Release.getState());
	Serial.print(", ");
	Serial.print(bv2ReleaseBend.getState());
	Serial.print(", ");
	Serial.print(bv2Select.getState());
	Serial.println();

	Serial.print("Trig LED state: ");
	Serial.println(bv2Trigger.getState());
	Serial.println();

	//Bus
	Serial.print("Bus1Amp: ");
	Serial.print(bus1Amp.getState());
	Serial.print(", Bus1Offset: ");
	Serial.print(bus1Offset.getState());
	Serial.println();

	Serial.print("LEDs, Src: ");
	Serial.print(bus1SrcLed.getState());
	Serial.print(", Dst: ");
	Serial.print(bus1DestLed.getState());
	Serial.println();

	Serial.print("Bus2Amp: ");
	Serial.print(bus2Amp.getState());
	Serial.print(", Bus2Offset: ");
	Serial.print(bus2Offset.getState());
	Serial.println();

	Serial.print("LEDs, Src: ");
	Serial.print(bus2SrcLed.getState());
	Serial.print(", Dst: ");
	Serial.print(bus2DestLed.getState());
	Serial.println();

	Serial.print("Bus3Amp: ");
	Serial.print(bus3Amp.getState());
	Serial.print(", Bus3Offset: ");
	Serial.print(bus3Offset.getState());
	Serial.println();

	Serial.print("LEDs, Src: ");
	Serial.print(bus3SrcLed.getState());
	Serial.print(", Dst: ");
	Serial.print(bus3DestLed.getState());
	Serial.println();

	Serial.print("Bus4Amp: ");
	Serial.print(bus4Amp.getState());
	Serial.print(", Bus4Offset: ");
	Serial.print(bus4Offset.getState());
	Serial.println();

	Serial.print("LEDs, Src: ");
	Serial.print(bus4SrcLed.getState());
	Serial.print(", Dst: ");
	Serial.print(bus4DestLed.getState());
	Serial.println();

	Serial.print("Bus5Amp: ");
	Serial.print(bus5Amp.getState());
	Serial.print(", Bus5Offset: ");
	Serial.print(bus5Offset.getState());
	Serial.println();

	Serial.print("LEDs, Src: ");
	Serial.print(bus5SrcLed.getState());
	Serial.print(", Dst: ");
	Serial.print(bus5DestLed.getState());
	Serial.println();

	Serial.print("MOD LEDs, Src: ");
	Serial.print(modSrcLed0.getState());	Serial.print(", ");
	Serial.print(modSrcLed1.getState());	Serial.print(", ");
	Serial.print(modSrcLed2.getState());	Serial.print(", ");
	Serial.print(modSrcLed3.getState());	Serial.print(", ");
	Serial.print(modSrcLed4.getState());	Serial.print(", ");
	Serial.print(modSrcLed5.getState());	Serial.print(", ");
	Serial.print(modSrcLed6.getState());	Serial.print(", ");
	Serial.print(modSrcLed7.getState());	Serial.print(", ");
	Serial.print(modSrcLed8.getState());	Serial.print(", ");
	Serial.print(modSrcLed9.getState());	Serial.print(", ");
	Serial.print(modSrcLed10.getState());	Serial.print(", ");
	Serial.print(modSrcLed11.getState());	Serial.print(", ");
	Serial.print(modSrcLed12.getState());	Serial.print(", ");
	Serial.print(modSrcLed13.getState());	Serial.print(", ");
	Serial.print(modSrcLed14.getState());
	Serial.println();
	
	Serial.print("MOD LEDs, Dst: ");
	Serial.print(modDestLed0.getState());	Serial.print(", ");
	Serial.print(modDestLed1.getState());	Serial.print(", ");
	Serial.print(modDestLed2.getState());	Serial.print(", ");
	Serial.print(modDestLed3.getState());	Serial.print(", ");
	Serial.print(modDestLed4.getState());	Serial.print(", ");
	Serial.print(modDestLed5.getState());	Serial.print(", ");
	Serial.print(modDestLed6.getState());	Serial.print(", ");
	Serial.print(modDestLed7.getState());	Serial.print(", ");
	Serial.print(modDestLed8.getState());	Serial.print(", ");
	Serial.print(modDestLed9.getState());	Serial.print(", ");
	Serial.print(modDestLed10.getState());	Serial.print(", ");
	Serial.print(modDestLed11.getState());	Serial.print(", ");
	Serial.print(modDestLed12.getState());	Serial.print(", ");
	Serial.print(modDestLed13.getState());	Serial.print(", ");
	Serial.print(modDestLed14.getState());
	Serial.println();
	
	//Master
	Serial.print("Master: ");
	Serial.print(masterCoarseTune.getState());	Serial.print(", ");
	Serial.print(masterFineTune.getState());	Serial.print(", ");
	Serial.print(masterVolume.getState());
	Serial.println();
	
	//LFO1
	Serial.print("LFO1: ");
	Serial.print(lfo1Freq.getState());	Serial.print(", ");
	Serial.print(lfo1Led1.getState());	Serial.print(", ");
	Serial.print(lfo1Led2.getState());	Serial.print(", ");
	Serial.print(lfo1Led3.getState());
	Serial.println();
	
	//LFO2
	Serial.print("LFO2: ");
	Serial.print(lfo2Freq.getState());	Serial.print(", ");
	Serial.print(lfo2Led1.getState());	Serial.print(", ");
	Serial.print(lfo2Led2.getState());	Serial.print(", ");
	Serial.print(lfo2Led3.getState());
	Serial.println();
	
	//OSCA
	Serial.print("OSCA, Pitch: ");	Serial.print(oscAPitch.getState());
	Serial.print(", Octave: ");	Serial.print(oscAOctave.getState());
	Serial.print(", Cent: ");	Serial.print(oscACent.getState());
	Serial.print(", Shape: ");	Serial.print(oscALed1.getState());
	Serial.print(", ");	Serial.print(oscALed2.getState());
	Serial.print(", ");	Serial.print(oscALed3.getState());
	Serial.print(", Amp: ");	Serial.print(oscAPreAmp.getState());
	Serial.println();
	
	Serial.print("OSCB, Pitch: ");	Serial.print(oscBPitch.getState());
	Serial.print(", Octave: ");	Serial.print(oscBOctave.getState());
	Serial.print(", Cent: ");	Serial.print(oscBCent.getState());
	Serial.print(", Shape: ");	Serial.print(oscBLed1.getState());
	Serial.print(", ");	Serial.print(oscBLed2.getState());
	Serial.print(", ");	Serial.print(oscBLed3.getState());
	Serial.print(", Amp: ");	Serial.print(oscBPreAmp.getState());
	Serial.println();

	Serial.print("OSCC, Pitch: ");	Serial.print(oscCPitch.getState());
	Serial.print(", Octave: ");	Serial.print(oscCOctave.getState());
	Serial.print(", Cent: ");	Serial.print(oscCCent.getState());
	Serial.print(", Shape: ");	Serial.print(oscCLed1.getState());
	Serial.print(", ");	Serial.print(oscCLed2.getState());
	Serial.print(", ");	Serial.print(oscCLed3.getState());
	Serial.print(", Amp: ");	Serial.print(oscCPreAmp.getState());
	Serial.println();

	Serial.print("OSCD, Pitch: ");	Serial.print(oscDPitch.getState());
	Serial.print(", Octave: ");	Serial.print(oscDOctave.getState());
	Serial.print(", Cent: ");	Serial.print(oscDCent.getState());
	Serial.print(", Shape: ");	Serial.print(oscDLed1.getState());
	Serial.print(", ");	Serial.print(oscDLed2.getState());
	Serial.print(", ");	Serial.print(oscDLed3.getState());
	Serial.print(", Amp: ");	Serial.print(oscDPreAmp.getState());
	Serial.println();
	
	//Wave Shape
	Serial.println("Waveshapes: ");
	Serial.print(" R1: ");	Serial.print(wave1Ramp.getState());
	Serial.print(" S1: ");	Serial.print(wave1Sine.getState());
	Serial.print(" PA1: ");	Serial.print(wave1Pulse.getState());
	Serial.println();
	Serial.print(" R2: ");	Serial.print(wave2Ramp.getState());
	Serial.print(" S2: ");	Serial.print(wave2Sine.getState());
	Serial.print(" PA2: ");	Serial.print(wave2Pulse.getState());
	Serial.println();
	Serial.print(" PA3: ");	Serial.print(wave3Pulse.getState());
	Serial.print(" PW3: ");	Serial.print(wave3Width.getState());
	Serial.println();
	Serial.println();

	//General
	Serial.print("Selector: ");	Serial.print(Select.getState());
	Serial.println();

}
