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
#include "PCSelector.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"

#define FIXTUREKNOBPOS 64

P8Panel::P8Panel( void )
{
	fixtureKnob.setHardware(new Proto8AnalogIn( FIXTUREKNOBPOS ));
	fixtureKnob.init( 255, 0, 10 );
	add( &fixtureKnob );
	
	state = PInit;
}

void P8Panel::reset( void )
{
	state = PInit;
	
}

void P8Panel::tickStateMachine( int msTicksDelta )
{
	freshenComponents( msTicksDelta );
	
	//***** PROCESS THE LOGIC *****//
	//Now do the states.
	PStates nextState = state;
	switch( state )
	{
	case PInit:
		nextState = PRun;
		break;
	case PRun:
		if( fixtureKnob.serviceChanged() == 1 )
		{
			Serial.println( fixtureKnob.getState() );
		}
		break;		
	default:
		nextState = PInit;
		break;
	}
	state = nextState;

}
