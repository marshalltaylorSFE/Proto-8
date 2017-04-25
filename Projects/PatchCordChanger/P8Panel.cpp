//**********************************************************************//
//
//  Patch cord changer panel description.
//
//  Hardware:
//    16 buttons
//    16 LEDs
//    Knob on 64
//    scanned matrix 7 segment display.
//  
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
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
#include "Arduino.h"
#include "P8Panel.h"
#include "panelComponents.h"
#include "proto-8PanelComponents.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"

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

#define LED16POS 1
#define LED15POS 2
#define LED14POS 3
#define LED13POS 4
#define LED12POS 5
#define LED11POS 6
#define LED10POS 7
#define LED9POS 8
#define LED8POS 9
#define LED7POS 10
#define LED6POS 11
#define LED5POS 12
#define LED4POS 13
#define LED3POS 14
#define LED2POS 15
#define LED1POS 16

#define FIXTUREKNOBPOS 64

#define	AKPOS 56
#define	ABKPOS 51
#define	HKPOS 55
#define	DKPOS 54
#define	DBKPOS 50
#define	SKPOS 53
#define	RKPOS 52
#define	RBKPOS 49

#define	REFPOS 8
#define	RAIL18POS 6
#define	RAIL33POS 7


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
	led8.setHardware(new Proto8DigitalOut( LED8POS  ), 0);
	led9.setHardware(new Proto8DigitalOut( LED9POS  ), 0);
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
	add( &fixtureKnob );
	
	refKnob.setHardware(new Proto8AnalogIn( REFPOS ));
	rail18Knob.setHardware(new Proto8AnalogIn( RAIL18POS ));
	rail33Knob.setHardware(new Proto8AnalogIn( RAIL33POS ));
	add( &refKnob );
	add( &rail18Knob );
	add( &rail33Knob );
	
}
