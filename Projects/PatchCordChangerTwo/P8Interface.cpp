//**********************************************************************//
//
//  Interface
//
//  Press button 1 to cycle through the filter outputs.
//  Press button 2 to cycle through the L/R output combinations
//  
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2017/4/24: Converted to uCModules 2.0 interface
//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//**********************************************************************//
#include "P8Interface.h"
#include "PanelComponents.h"
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

	//Set all LED off
	LEDs.clear();
	
}

void P8Interface::reset( void )
{
	state = PInit;
	
	filterOutputState = 0;
	audioChanState = 3;

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
void P8Interface::processMachine( uint16_t msInput )
{
	freshenComponents(msInput);

	// Handle wave selection variable
	uint8_t triggerChange = 0;
	if( filterSelectButton.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		filterOutputState++;
		if(filterOutputState > 2) filterOutputState = 0;
		lowPassLed.setState(LEDOFF);
		bandPassLed.setState(LEDOFF);
		highPassLed.setState(LEDOFF);
		
		triggerChange = 1;
	}

	if( channelSelectButton.serviceRisingEdge() )
	{
		Serial.println("Detect.");
		audioChanState++;
		if(audioChanState > 3) audioChanState = 0;
		leftActiveLed.setState(LEDOFF);
		rightActiveLed.setState(LEDOFF);
		
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
			leftActiveLed.setState(LEDON);
			break;
			case 2:
			rightActiveLed.setState(LEDON);
			break;
			case 3:
			leftActiveLed.setState(LEDON);
			rightActiveLed.setState(LEDON);
			break;
			default:
			break;
		}		
		switch(filterOutputState)
		{
			case 0:
			lowPassLed.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(&filter3, 0, &i2s_quad2, 0);
			if(audioChanState & 0x02) patchCord3.reconnect(&filter3, 0, &i2s_quad2, 1);
			break;
			case 1:
			bandPassLed.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(&filter3, 1, &i2s_quad2, 0);
			if(audioChanState & 0x02) patchCord3.reconnect(&filter3, 1, &i2s_quad2, 1);
			break;
			case 2:
			highPassLed.setState(LEDON);
			if(audioChanState & 0x01) patchCord2.reconnect(&filter3, 2, &i2s_quad2, 0);
			if(audioChanState & 0x02) patchCord3.reconnect(&filter3, 2, &i2s_quad2, 1);
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
		lowPassLed.setState(LEDOFF);
		bandPassLed.setState(LEDOFF);
		highPassLed.setState(LEDOFF);

		leftActiveLed.setState(LEDON);
		rightActiveLed.setState(LEDON);

		switch(filterOutputState)
		{
			case 0:
			lowPassLed.setState(LEDON);
			break;
			case 1:
			bandPassLed.setState(LEDON);
			break;
			case 2:
			highPassLed.setState(LEDON);
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
		break;
    }
	
    state = nextState;

}
