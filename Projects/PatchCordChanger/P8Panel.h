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
#ifndef P8PANEL_H
#define P8PANEL_H


#include "Panel.h"
#include "PanelComponents.h"
#include "proto-8PanelComponents.h"
#include "proto-8HardwareInterfaces.h"

class P8Panel : public Panel
{
public:
	P8Panel( void );

protected:
//Buttons
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

//LEDs
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

//Knobs
	Simple8BitKnob fixtureKnob;

	Simple8BitKnob refKnob;
	Simple8BitKnob rail18Knob;
	Simple8BitKnob rail33Knob;

};

#endif // P8PANEL_H



