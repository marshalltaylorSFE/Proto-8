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

extern LEDShiftRegister LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

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
	
	//Do main machine
	tickStateMachine();
	
	//Do pure LED operations first
	
	//System level LEDs
//	oscALed1.setState(LEDOFF);
//	oscALed2.setState(LEDOFF);
//	oscALed3.setState(LEDOFF);
//	oscBLed1.setState(LEDOFF);
//	oscBLed2.setState(LEDOFF);
//	oscBLed3.setState(LEDOFF);

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
