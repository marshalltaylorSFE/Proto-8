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
#include "P8Panel.h"
#include "Arduino.h"

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
	flasherState = 0;
	fastFlasherState = 0;
}

void P8Panel::init( void )
{
	button1.init(B1POS);
	button2.init(B2POS);
	button3.init(B3POS);
	button4.init(B4POS);
	button5.init(B5POS);
	button6.init(B6POS);
	button7.init(B7POS);
	button8.init(B8POS);
	button9.init(B9POS);
	button10.init(B10POS);
	button11.init(B11POS);
	button12.init(B12POS);
	button13.init(B13POS);
	button14.init(B14POS);
	button15.init(B15POS);
	button16.init(B16POS);
	
	led1.init(LED1POS, &flasherState, &fastFlasherState );
	led2.init(LED2POS, &flasherState, &fastFlasherState );
	led3.init(LED3POS, &flasherState, &fastFlasherState );
	led4.init(LED4POS, &flasherState, &fastFlasherState );
	led5.init(LED5POS, &flasherState, &fastFlasherState );
	led6.init(LED6POS, &flasherState, &fastFlasherState );
	led7.init(LED7POS, &flasherState, &fastFlasherState );
	led8.init(LED8POS, &flasherState, &fastFlasherState );
	led9.init(LED9POS, &flasherState, &fastFlasherState );
	led10.init(LED10POS, &flasherState, &fastFlasherState );
	led11.init(LED11POS, &flasherState, &fastFlasherState );
	led12.init(LED12POS, &flasherState, &fastFlasherState );
	led13.init(LED13POS, &flasherState, &fastFlasherState );
	led14.init(LED14POS, &flasherState, &fastFlasherState );
	led15.init(LED15POS, &flasherState, &fastFlasherState );
	led16.init(LED16POS, &flasherState, &fastFlasherState );

	fixtureKnob.init(FIXTUREKNOBPOS);
	
	attackKnob.init(AKPOS);
	attackBendKnob.init(ABKPOS);
	holdKnob.init(HKPOS);
	decayKnob.init(DKPOS);
	decayBendKnob.init(DBKPOS);
	sustainKnob.init(SKPOS);
	releaseKnob.init(RKPOS);
	releaseBendKnob.init(RBKPOS);

	refKnob.init(REFPOS);
	rail18Knob.init(RAIL18POS);
	rail33Knob.init(RAIL33POS);
	
 	flasherState = 0;
	fastFlasherState = 0;
}

void P8Panel::update( void )
{
	button1.update();
	button2.update();
	button3.update();
	button4.update();
	button5.update();
	button6.update();
	button7.update();
	button8.update();
	button9.update();
	button10.update();
	button11.update();
	button12.update();
	button13.update();
	button14.update();
	button15.update();
	button16.update();
	
	led1.update();
	led2.update();
	led3.update();
	led4.update();
	led5.update();
	led6.update();
	led7.update();
	led8.update();
	led9.update();
	led10.update();
	led11.update();
	led12.update();
	led13.update();
	led14.update();
	led15.update();
	led16.update();
	
	fixtureKnob.update();
	
	attackKnob.update();
	attackBendKnob.update();
	holdKnob.update();
	decayKnob.update();
	decayBendKnob.update();
	sustainKnob.update();
	releaseKnob.update();
	releaseBendKnob.update();

	refKnob.update();
	rail18Knob.update();
	rail33Knob.update();
}

void P8Panel::toggleFlasherState( void )
{
	flasherState ^= 0x01;
}

void P8Panel::toggleFastFlasherState( void )
{
	fastFlasherState ^= 0x01;
}