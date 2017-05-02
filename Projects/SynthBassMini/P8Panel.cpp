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
#include "Arduino.h"
#include "P8Panel.h"
#include "panelComponents.h"
#include "proto-8PanelComponents.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"
#include <typeinfo>   // operator typeid

P8Panel::P8Panel( void )
{
	//Bendvelope1
	bv1Attack.setHardware(new Proto8AnalogIn( 32 ));
	add( &bv1Attack );
	bv1AttackBend.setHardware(new Proto8AnalogIn( 27 ));
	add( &bv1AttackBend );
	bv1Hold.setHardware(new Proto8AnalogIn( 31 ));
	add( &bv1Hold );
	bv1Decay.setHardware(new Proto8AnalogIn( 30 ));
	add( &bv1Decay );
	bv1DecayBend.setHardware(new Proto8AnalogIn( 26 ));
	add( &bv1DecayBend );
	bv1Sustain.setHardware(new Proto8AnalogIn( 29 ));
	add( &bv1Sustain );
	bv1Release.setHardware(new Proto8AnalogIn( 28 ));
	add( &bv1Release );
	bv1ReleaseBend.setHardware(new Proto8AnalogIn( 25 ));
	add( &bv1ReleaseBend );

	bv1Trigger.setHardware(new Proto8DigitalOut( 37 ), 0);
	add( &bv1Trigger );
	
	//OSC
	oscPitch.setHardware(new Proto8AnalogIn( 17 ));
	oscPitch.setWindow( 10 );
	add( &oscPitch );
	oscOctave.setHardware(new Proto8AnalogIn( 18 ));
	oscOctave.init(673, 373, 4); //With max, min, points
	add( &oscOctave );
	oscOptionLed.setHardware(new Proto8DigitalOut( 36 ), 0);
	add( &oscOptionLed );
	oscOption.setHardware(new Proto8DigitalIn( 9,4 ), 0);
	add( &oscOption );
	oscShape.setHardware(new Proto8DigitalIn( 9,3 ), 0);
	add( &oscShape );
	oscLed1.setHardware(new Proto8DigitalOut( 33 ), 0);
	add( &oscLed1 );
	oscLed2.setHardware(new Proto8DigitalOut( 34 ), 0);
	add( &oscLed2 );
	oscLed3.setHardware(new Proto8DigitalOut( 35 ), 0);
	add( &oscLed3 );
	oscPreAmp.setHardware(new Proto8AnalogIn( 19 ));
	add( &oscPreAmp );
	
	//Bendvelope2
	env2Attack.setHardware(new Proto8AnalogIn( 16 ));
	add( &env2Attack );
	env2Decay.setHardware(new Proto8AnalogIn( 15 ));
	add( &env2Decay );
	param1Knob.setHardware(new Proto8AnalogIn( 14 ));
	add( &param1Knob );
	param2Knob.setHardware(new Proto8AnalogIn( 13 ));
	add( &param2Knob );
	
	tone.setHardware(new Proto8AnalogIn( 10 ));
	tone.init( 1023, 0, 10 ); //With max and min ranges
	add( &tone );
	effect.setHardware(new Proto8AnalogIn( 9 ));
	effect.init( 1023, 0, 10 ); //With max and min ranges
	add( &effect );

}
