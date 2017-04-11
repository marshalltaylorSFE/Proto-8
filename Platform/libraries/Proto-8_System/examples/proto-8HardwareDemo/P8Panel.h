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
#ifndef P8PANEL_H
#define P8PANEL_H

#include "Panel.h"
#include "PanelComponents.h"
#include "proto-8HardwareInterfaces.h"
#include <Arduino.h>

enum PStates
{
	PInit,
	PRun
};

class P8Panel : public Panel
{
public:
	P8Panel( void );
	void reset( void );
	void tickStateMachine( int msTicksDelta );
	uint8_t getState( void ){
		return (uint8_t)state;
	}
	
private:
	Button button1;
	Button button2;
	Button button3;
	Button button4;
	Button button5;
	Button button6;
	Button button7;
	Button button8;
	Button button9;
	Button button10;
	Button button11;
	Button button12;
	Button button13;
	Button button14;
	Button button15;
	Button button16;
	
	Led led1;
	Led led2;
	Led led3;
	Led led4;
	Led led5;
	Led led6;
	Led led7;
	Led led8;
	Led led9;
	Led led10;
	Led led11;
	Led led12;
	Led led13;
	Led led14;
	Led led15;
	Led led16;
	
	Windowed10BitKnob fixtureKnob;

	Simple10BitKnob refKnob;
	Simple10BitKnob rail18Knob;
	Simple10BitKnob rail33Knob;

	//State machine stuff  
	PStates state;
	
};

#endif // P8PANEL_H



