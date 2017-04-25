//**********************************************************************//
//
//  Patch cord changer interface.
//
//  Hardware:
//    16 buttons (5 used)
//    16 LEDs (4 used)
//    Knob on 64
//    scanned matrix 7 segment display.
//  
//  This file defines the human interaction of the panel parts
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//    2016/2/29: Merged with demo for segment driver
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
extern AudioControlSGTL5000 sgtl5000_2;     //xy=1430.0,93.0
extern AudioControlSGTL5000 sgtl5000_1;     //xy=1434.0,49.0


P8Interface::P8Interface( void )
{
	state = PInit;

	//Set all LED off
	LEDs.clear();

}

void P8Interface::reset( void )
{
	state = PInit;

	//Set all LED off
	LEDs.clear();
	
}

//---------------------------------------------------------------------------//
//
//  Interface Logic
//
//---------------------------------------------------------------------------//
void P8Interface::processMachine( uint16_t msInput )
{
	freshenComponents(msInput);

	//Do small machines
	if( button1.serviceRisingEdge() )
	{
		led1.setState(LEDON);
		led2.setState(LEDOFF);
		led3.setState(LEDOFF);
		led4.setState(LEDOFF);
		led5.setState(LEDOFF);
		
		//reconnect(...) doesn't check if there are any
		//cords currently attached, new cords will be ignored.
		
		//Disconnect all cords.
		patchCord1.disconnect();
		patchCord2.disconnect();
		patchCord3.disconnect();
		patchCord4.disconnect();
		
		//Connect new configuration
		patchCord1.reconnect(&waveform1, 0, &i2s_quad2, 0);
		patchCord2.reconnect(&waveform2, 0, &i2s_quad2, 1);
	}
	if( button2.serviceRisingEdge() )
	{
		led1.setState(LEDOFF);
		led2.setState(LEDON);
		led3.setState(LEDOFF);
		led4.setState(LEDOFF);
		led5.setState(LEDOFF);

		//Disconnect all cords.
		patchCord1.disconnect();
		patchCord2.disconnect();
		patchCord3.disconnect();
		patchCord4.disconnect();
		
		//Connect new configuration
		patchCord1.reconnect(&waveform3, 0, &i2s_quad2, 0);
		patchCord2.reconnect(&waveform4, 0, &i2s_quad2, 1);
	}
	if( button3.serviceRisingEdge() )
	{
		led1.setState(LEDOFF);
		led2.setState(LEDOFF);
		led3.setState(LEDON);
		led4.setState(LEDOFF);
		led5.setState(LEDOFF);

		//Disconnect all cords.
		patchCord1.disconnect();
		patchCord2.disconnect();
		patchCord3.disconnect();
		patchCord4.disconnect();
		
		//Connect new configuration
		patchCord1.reconnect(&waveform1, 0, &i2s_quad2, 0);
		patchCord2.reconnect(&waveform4, 0, &i2s_quad2, 1);
	}
	if( button4.serviceRisingEdge() )
	{
		led1.setState(LEDOFF);
		led2.setState(LEDOFF);
		led3.setState(LEDOFF);
		led4.setState(LEDON);
		led5.setState(LEDOFF);

		//Disconnect all cords.
		patchCord1.disconnect();
		patchCord2.disconnect();
		patchCord3.disconnect();
		patchCord4.disconnect();
		
		patchCord1.reconnect(&waveform2, 0, &i2s_quad2, 0);
		patchCord2.reconnect(&waveform3, 0, &i2s_quad2, 1);
	}
	if( button5.serviceRisingEdge() )
	{
		led1.setState(LEDFLASHING);
		led2.setState(LEDFLASHING);
		led3.setState(LEDFLASHING);
		led4.setState(LEDFLASHING);
		led5.setState(LEDOFF);

		//Disconnect all cords.
		patchCord1.disconnect();
		patchCord2.disconnect();
		patchCord3.disconnect();
		patchCord4.disconnect();
		
	}

	//Knobs
	if( fixtureKnob.serviceChanged() )
	{
		debugTemp = fixtureKnob.getState();
		sgtl5000_1.volume(float(fixtureKnob.getState())/255);
		sgtl5000_2.volume(float(fixtureKnob.getState())/255);
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

}

void P8Interface::tickStateMachine()
{
	//***** PROCESS THE LOGIC *****//
    //Now do the states.
    PStates nextState = state;
    switch( state )
    {
    case PInit:
		led1.setState(LEDFLASHING);
		led2.setState(LEDFLASHING);
		led3.setState(LEDFLASHING);
		led4.setState(LEDFLASHING);
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
