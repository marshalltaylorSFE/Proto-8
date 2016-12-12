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

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"

extern LEDShiftRegister LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

extern AudioControlSGTL5000     sgtl5000_2;     //xy=1564,476
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1568,432
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioFilterStateVariable filter3;        //xy=1217.4999694824219,650.3333415985107
extern AudioOutputI2SQuad       i2s_quad2;      //xy=1459.6666259765625,698.5

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	
	filterOutputState = 0;
	audioChanState = 3;
	
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
	uint8_t triggerChange = 0;
	if( bus1SrcPick.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		filterOutputState++;
		if(filterOutputState > 2) filterOutputState = 0;
		modSrcLed0.setState(LEDOFF);
		modSrcLed1.setState(LEDOFF);
		modSrcLed2.setState(LEDOFF);
		
		triggerChange = 1;
	}

	if( bus1DestPick.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		audioChanState++;
		if(audioChanState > 3) audioChanState = 0;
		modDestLed0.setState(LEDOFF);
		modDestLed1.setState(LEDOFF);
		
		triggerChange = 1;
	}
	
	if(triggerChange)
	{
		patchCord2.disconnect();
		patchCord3.disconnect();
		switch(audioChanState)
		{
			case 0:
			break;
			case 1:
			modDestLed0.setState(LEDON);
			break;
			case 2:
			modDestLed1.setState(LEDON);
			break;
			case 3:
			modDestLed0.setState(LEDON);
			modDestLed1.setState(LEDON);
			break;
			default:
			break;
		}		
		switch(filterOutputState)
		{
			case 0:
			modSrcLed0.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(filter3, 0, i2s_quad2, 0);;
			if(audioChanState & 0x02) patchCord3.reconnect(filter3, 0, i2s_quad2, 1);;
			break;
			case 1:
			modSrcLed1.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(filter3, 1, i2s_quad2, 0);;
			if(audioChanState & 0x02) patchCord3.reconnect(filter3, 1, i2s_quad2, 1);;
			break;
			case 2:
			modSrcLed2.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(filter3, 2, i2s_quad2, 0);;
			if(audioChanState & 0x02) patchCord3.reconnect(filter3, 2, i2s_quad2, 1);;
			break;
			default:
			break;
			
		}
	}
	//Misc knobs
	if( masterVolume.serviceChanged() )
	{
		sgtl5000_1.volume(((float)masterVolume.getState() / 256) * 1);
		sgtl5000_2.volume(((float)masterVolume.getState() / 256) * 1);
	}
	if( Select.serviceChanged() )
	{
		Serial.println("Detect: ");
		Serial.println(Select.getState());
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
		modSrcLed0.setState(LEDOFF);
		modSrcLed1.setState(LEDOFF);
		modSrcLed2.setState(LEDOFF);

		modDestLed0.setState(LEDON);
		modDestLed1.setState(LEDON);

		switch(filterOutputState)
		{
			case 0:
			modSrcLed0.setState(LEDON);
			break;
			case 1:
			modSrcLed1.setState(LEDON);
			break;
			case 2:
			modSrcLed2.setState(LEDON);
			break;
			default:
			break;
			
		}		
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

}

void P8Interface::setPointer( uint8_t oscNumber, int16_t * pointerVar ) //Pass number 0 = OSC A, 1 = OSC B
{
	switch( oscNumber )
	{
		case 0:
		break;
		case 1:
		break;
		default:
		break;
	}
}