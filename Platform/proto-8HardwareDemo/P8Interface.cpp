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
//
//**********************************************************************//
#include "P8Interface.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "Arduino.h"
#include "flagMessaging.h"
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	
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
	if( button1.serviceRisingEdge() )
	{
		led1.toggle();
	}
	if( button2.serviceRisingEdge() )
	{
		led2.toggle();
	}
	if( button3.serviceRisingEdge() )
	{
		led3.toggle();
	}
	if( button4.serviceRisingEdge() )
	{
		led4.toggle();
	}
	if( button5.serviceRisingEdge() )
	{
		led5.toggle();
	}
	if( button6.serviceRisingEdge() )
	{
		led6.toggle();
	}
	if( button7.serviceRisingEdge() )
	{
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
	if( button14.serviceRisingEdge() )
	{
		led14.toggle();
	}
	if( button15.serviceRisingEdge() )
	{
		led15.toggle();
	}
	if( button16.serviceRisingEdge() )
	{
		led16.toggle();
	}
	if( fixtureKnob.serviceChanged() == 1 )
	{
		//LEDs.store( fixtureKnob.getState() + 1, 1 );
		//LEDs.store( attackBendKnob.getState() + 1, 0 );
		//LEDs.setNumber1( fixtureKnob.getState() );
		//Serial.println( fixtureKnob.getState() );
	}
	LEDs.setNumber1( knobs.fetch(64) );
	//'set' all the values
	//display1.update();
	//update();
	
	//Do main machine
	tickStateMachine();
	
	//Do pure LED operations first
	
	//System level LEDs
	//led10.setState(LEDON);
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
	

}
