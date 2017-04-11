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
//#include "Arduino.h"
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"
#include "P8Panel.h"
#include "panelComponents.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

//This is where PanelComponents are joined to form the custom panel
//col,row
#define B1POS 1,1
#define B2POS 1,2
#define B3POS 2,1
#define B4POS 2,2
#define B5POS 3,1
#define B6POS 3,2
#define B7POS 4,1
#define B8POS 4,2
#define B9POS 5,1
#define B10POS 5,2
#define B11POS 6,1
#define B12POS 6,2
#define B13POS 7,1
#define B14POS 7,2
#define B15POS 8,1
#define B16POS 8,2

#define LED16POS 25
#define LED15POS 26
#define LED14POS 27
#define LED13POS 28
#define LED12POS 29
#define LED11POS 30
#define LED10POS 31
#define LED9POS 32
#define LED8POS 33
#define LED7POS 34
#define LED6POS 35
#define LED5POS 36
#define LED4POS 37
#define LED3POS 38
#define LED2POS 39
#define LED1POS 40

#define FIXTUREKNOBPOS 64

//#define	AKPOS 56
//#define	ABKPOS 51
//#define	HKPOS 55
//#define	DKPOS 54
//#define	DBKPOS 50
//#define	SKPOS 53
//#define	RKPOS 52
//#define	RBKPOS 49

#define	REFPOS 8
#define	RAIL18POS 6
#define	RAIL33POS 7

//segments at:
//hpA.init(60);
//hpB.init(52);
//hpC.init(64);
//hpD.init(56);
//hpE.init(58);
//hpF.init(50);
//hpG.init(54);
//hpDP.init(62);
//hpD1.init(48);
//hpD2.init(63);
//hpD3.init(61);
//hpD4.init(59);
//hpD5.init(57);
//hpD6.init(55);
//hpD7.init(53);
//hpD8.init(51);
//hpD9.init(49);

P8Panel::P8Panel( void )
{
	button1.setHardware(new Proto8DigitalIn( B1POS ), 0);
	button2.setHardware(new Proto8DigitalIn( B2POS ), 0);
	button3.setHardware(new Proto8DigitalIn( B3POS ), 0);
	button4.setHardware(new Proto8DigitalIn( B4POS ), 0);
	button5.setHardware(new Proto8DigitalIn( B5POS ), 0);
	button6.setHardware(new Proto8DigitalIn( B6POS ), 0);
	button7.setHardware(new Proto8DigitalIn( B7POS ), 0);
	button8.setHardware(new Proto8DigitalIn( B8POS ), 0);
	button9.setHardware(new Proto8DigitalIn( B9POS ), 0);
	button10.setHardware(new Proto8DigitalIn( B10POS ), 0);
	button11.setHardware(new Proto8DigitalIn( B11POS ), 0);
	button12.setHardware(new Proto8DigitalIn( B12POS ), 0);
	button13.setHardware(new Proto8DigitalIn( B13POS ), 0);
	button14.setHardware(new Proto8DigitalIn( B14POS ), 0);
	button15.setHardware(new Proto8DigitalIn( B15POS ), 0);
	button16.setHardware(new Proto8DigitalIn( B16POS ), 0);
	add( &button1 );
	add( &button2 );
	add( &button3 );
	add( &button4 );
	add( &button5 );
	add( &button6 );
	add( &button7 );
	add( &button8 );
	add( &button9 );
	add( &button10 );
	add( &button11 );
	add( &button12 );
	add( &button13 );
	add( &button14 );
	add( &button15 );
	add( &button16 );
    
	led1.setHardware(new Proto8DigitalOut( LED1POS ), 0);
	led2.setHardware(new Proto8DigitalOut( LED2POS ), 0);
	led3.setHardware(new Proto8DigitalOut( LED3POS ), 0);
	led4.setHardware(new Proto8DigitalOut( LED4POS ), 0);
	led5.setHardware(new Proto8DigitalOut( LED5POS ), 0);
	led6.setHardware(new Proto8DigitalOut( LED6POS ), 0);
	led7.setHardware(new Proto8DigitalOut( LED7POS ), 0);
	led8.setHardware(new Proto8DigitalOut( LED8POS ), 0);
	led9.setHardware(new Proto8DigitalOut( LED9POS ), 0);
	led10.setHardware(new Proto8DigitalOut( LED10POS ), 0);
	led11.setHardware(new Proto8DigitalOut( LED11POS ), 0);
	led12.setHardware(new Proto8DigitalOut( LED12POS ), 0);
	led13.setHardware(new Proto8DigitalOut( LED13POS ), 0);
	led14.setHardware(new Proto8DigitalOut( LED14POS ), 0);
	led15.setHardware(new Proto8DigitalOut( LED15POS ), 0);
	led16.setHardware(new Proto8DigitalOut( LED16POS ), 0);
	add( &led1 );
	add( &led2 );
	add( &led3 );
	add( &led4 );
	add( &led5 );
	add( &led6 );
	add( &led7 );
	add( &led8 );
	add( &led9 );
	add( &led10 );
	add( &led11 );
	add( &led12 );
	add( &led13 );
	add( &led14 );
	add( &led15 );
	add( &led16 );
    
	fixtureKnob.setHardware(new Proto8AnalogIn( FIXTUREKNOBPOS ));
	refKnob.setHardware(new Proto8AnalogIn( REFPOS ));
	rail18Knob.setHardware(new Proto8AnalogIn( RAIL18POS ));
	rail33Knob.setHardware(new Proto8AnalogIn( RAIL33POS ));
	add( &fixtureKnob );
	add( &refKnob );
	add( &rail18Knob );
	add( &rail33Knob );
	
	state = PInit;
}

void P8Panel::reset( void )
{
	//Set explicit states
	//Set all LED off
	LEDs.clear();
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
	
}

void P8Panel::tickStateMachine( int msTicksDelta )
{
	float tempVoltage = 0;
	float tempFactor = 0;

	//switches.scan();
	//knobs.scan();
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
			Serial.println("14!!!");
		}
		if( button15.serviceRisingEdge() )
		{
			led15.toggle();
			Serial.println("15!!!");
		}
		if( button16.serviceRisingEdge() )
		{
			led16.toggle();
			Serial.println("16!!!");
		}
		if( fixtureKnob.serviceChanged() == 1 )
		{
			//LEDs.store( fixtureKnob.getState() + 1, 1 );
			//LEDs.store( attackBendKnob.getState() + 1, 0 );
			//LEDs.setNumber1( fixtureKnob.getState() );
			//Serial.println( fixtureKnob.getState() );
		}
		LEDs.setNumber1( knobs.fetch(64) );
		// n * factor = 2.5
		tempFactor = 2.5 / (refKnob.getState() >> 2);
		tempVoltage = (float)(rail18Knob.getState() >> 2) * tempFactor * 2;
		LEDs.setVoltage( tempVoltage, 0 );
		tempVoltage = (float)(rail33Knob.getState() >> 2) * tempFactor * 2;
		LEDs.setVoltage( tempVoltage, 3 );
		break;		
	default:
		nextState = PInit;
		break;
	}
	state = nextState;

}
