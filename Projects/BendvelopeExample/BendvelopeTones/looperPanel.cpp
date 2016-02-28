//**LooperPanel*******************************//
#include "looperPanel.h"
//#include "PanelComponents.h"
#include "Panel.h"
#include "Arduino.h"
#include "flagMessaging.h"

LooperPanel::LooperPanel( void )
{
	//Controls
	rxLedFlag = 0;	

	state = PInit;
	
	
}

void LooperPanel::setRxLed( void )
{
	rxLedFlag = 1;
}

ledState_t LooperPanel::serviceRxLed( void )
{
	ledState_t returnVar = LEDOFF;
	if( rxLedFlag == 1 )
	{
		returnVar = LEDON;
		rxLedFlag = 0;
		
	}
	return returnVar;
	
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
void LooperPanel::processMachine( void )
{
	//Do small machines

	//Do main machine
	tickStateMachine();
	
	//Do pure LED operations first
	//System level LEDs
	rxLed.setState(serviceRxLed());
	
	update();

}

void LooperPanel::tickStateMachine()
{
	//***** PROCESS THE LOGIC *****//
    //Now do the states.
    PStates nextState = state;
    switch( state )
    {
    case PInit:
		Serial.println("Init state!!!!");
		nextState = PIdle;
		
		break;
	case PIdle:
		//Can't be running, if button pressed move on
        break;
	case PFirstRecord:
        break;
	case PPlay:
		break;
	case POverdub:
		break;
	case PUndoClearOverdub:
		break;
	case PUndoDecrement:
		break;
	case PUndoClearTrack:
		break;
    default:
        nextState = PInit;
		//Serial.println("!!!DEFAULT STATE HIT!!!");
        break;
    }
	
    state = nextState;

}


void LooperPanel::timersMIncrement( uint8_t inputValue )
{
}