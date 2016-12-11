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
#include <Audio.h>

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;
extern AudioConnection patchCord1;
extern AudioConnection patchCord2;
extern AudioConnection patchCord3;
extern AudioConnection patchCord4;
extern AudioSynthWaveform waveform1;
extern AudioSynthWaveform waveform2;
extern AudioSynthWaveform waveform3;
extern AudioSynthWaveform waveform4;
extern AudioOutputI2SQuad i2s_quad2;

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
		select1 = 1;
		patchCord1.reconnect(waveform1, 0, i2s_quad2, 0);
	}
	if( button2.serviceRisingEdge() )
	{
		select1 = 2;
		patchCord1.reconnect(waveform2, 0, i2s_quad2, 0);
	}
	if( button3.serviceRisingEdge() )
	{
		select1 = 3;
		patchCord1.reconnect(waveform3, 0, i2s_quad2, 0);
	}
	if( button4.serviceRisingEdge() )
	{
		select1 = 4;
		patchCord1.reconnect(waveform4, 0, i2s_quad2, 0);
	}
	if( button5.serviceRisingEdge() )
	{
		patchCord1.disconnect(waveform1, 0, i2s_quad2, 0);
		//patchCord2.disconnect(waveform2, 0, i2s_quad2, 0);
		//patchCord3.disconnect(waveform3, 0, i2s_quad2, 0);
		//patchCord4.disconnect(waveform4, 0, i2s_quad2, 0);
	}
	if( button6.serviceRisingEdge() )
	{
	}
	if( button7.serviceRisingEdge() )
	{
	}
	if( button8.serviceRisingEdge() )
	{
	}
	if( button9.serviceRisingEdge() )
	{
	}
	if( button10.serviceRisingEdge() )
	{
	}
	if( button11.serviceRisingEdge() )
	{
	}
	if( button12.serviceRisingEdge() )
	{
	}
	if( button13.serviceRisingEdge() )
	{
	}
	if( button14.serviceRisingEdge() )
	{
	}
	if( button15.serviceRisingEdge() )
	{
	}
	if( button16.serviceRisingEdge() )
	{
	}

	if( button1.serviceHoldRisingEdge() )
	{
	}
	if( button2.serviceHoldRisingEdge() )
	{
	}
	if( button3.serviceHoldRisingEdge() )
	{
	}
	if( button4.serviceHoldRisingEdge() )
	{
	}
	if( button5.serviceHoldRisingEdge() )
	{
	}

	//Knobs
	if( fixtureKnob.serviceChanged() )
	{
		debugTemp = fixtureKnob.getState();
	}
	LEDs.setNumber1( debugTemp );
	float tempVoltage = 0;
	float tempFactor = 0; // n * factor = 2.5
	tempFactor = 2.5 / refKnob.getState();
	tempVoltage = (float)rail18Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 0 );
	tempVoltage = (float)rail33Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 3 );
	
	//Do main machine
	tickStateMachine();

	led1.setState(LEDOFF);
	led2.setState(LEDOFF);
	led3.setState(LEDOFF);
	led4.setState(LEDOFF);
	led5.setState(LEDOFF);
	led6.setState(LEDOFF);
	led7.setState(LEDOFF);
	led8.setState(LEDOFF);
	led9.setState(LEDOFF);
	led10.setState(LEDOFF);
	led11.setState(LEDOFF);
	led12.setState(LEDOFF);
	led13.setState(LEDOFF);
	led14.setState(LEDOFF);
	led15.setState(LEDOFF);
	led16.setState(LEDOFF);
	
	switch( select1 )
	{
		case 1:
		led1.setState(LEDON);
		break;
		case 2:
		led2.setState(LEDON);
		break;
		case 3:
		led3.setState(LEDON);
		break;
		case 4:
		led4.setState(LEDON);
		break;
		default:
		break;
	}
	switch( select2 )
	{
		case 1:
		led5.setState(LEDON);
		break;
		case 2:
		led6.setState(LEDON);
		break;
		case 3:
		led7.setState(LEDON);
		break;
		case 4:
		led8.setState(LEDON);
		break;
		default:
		break;
	}
	switch( select3 )
	{
		case 1:
		led9.setState(LEDON);
		break;
		case 2:
		led10.setState(LEDON);
		break;
		case 3:
		led11.setState(LEDON);
		break;
		case 4:
		led12.setState(LEDON);
		break;
		default:
		break;
	}
	switch( select4 )
	{
		case 1:
		led13.setState(LEDON);
		break;
		case 2:
		led14.setState(LEDON);
		break;
		case 3:
		led15.setState(LEDON);
		break;
		case 4:
		led16.setState(LEDON);
		break;
		default:
		break;
	}

	update();
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