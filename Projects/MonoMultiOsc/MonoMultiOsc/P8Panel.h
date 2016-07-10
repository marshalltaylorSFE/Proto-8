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

#include "P8PanelComponents.h"

class P8Panel
{
public:
	P8Panel( void );
	void update( void );
	void init( void );
	void toggleFlasherState( void );
	void toggleFastFlasherState( void );

	P8PanelButton button1;
	P8PanelButton button2;
	P8PanelButton button3;
	P8PanelButton button4;
	P8PanelButton button5;
	P8PanelButton button6;
	P8PanelButton button7;
	P8PanelButton button8;
	P8PanelButton button9;
	P8PanelButton button10;
	P8PanelButton button11;
	P8PanelButton button12;
	P8PanelButton button13;
	P8PanelButton button14;
	P8PanelButton button15;
	P8PanelButton button16;
	
	P8PanelLed led1;
	P8PanelLed led2;
	P8PanelLed led3;
	P8PanelLed led4;
	P8PanelLed led5;
	P8PanelLed led6;
	P8PanelLed led7;
	P8PanelLed led8;
	P8PanelLed led9;
	P8PanelLed led10;
	P8PanelLed led11;
	P8PanelLed led12;
	P8PanelLed led13;
	P8PanelLed led14;
	P8PanelLed led15;
	P8PanelLed led16;

	P8PanelButton oscAButton1;
	P8PanelButton oscAButton2;
	P8PanelButton oscAButton3;
	P8PanelButton oscBButton1;
	P8PanelButton oscBButton2;
	P8PanelButton oscBButton3;

	P8PanelLed oscALed1;
	P8PanelLed oscALed2;
	P8PanelLed oscALed3;
	P8PanelLed oscALed4;
	P8PanelLed oscALed5;
	P8PanelLed oscBLed1;
	P8PanelLed oscBLed2;
	P8PanelLed oscBLed3;
	P8PanelLed oscBLed4;
	P8PanelLed oscBLed5;
	
	P8PanelKnob8Bit fixtureKnob;

	P8PanelKnob8Bit attackKnob;
	P8PanelKnob8Bit attackBendKnob;
	P8PanelKnob8Bit holdKnob;
	P8PanelKnob8Bit decayKnob;
	P8PanelKnob8Bit decayBendKnob;
	P8PanelKnob8Bit sustainKnob;
	P8PanelKnob8Bit releaseKnob;
	P8PanelKnob8Bit releaseBendKnob;

	P8PanelKnob8Bit refKnob;
	P8PanelKnob8Bit rail18Knob;
	P8PanelKnob8Bit rail33Knob;

	P8PanelKnob8Bit oscAFreqKnob;
	P8PanelKnob8Bit oscBFreqKnob;
	P8PanelKnob8Bit oscAAmpKnob;
	P8PanelKnob8Bit oscBAmpKnob;


	
protected:
private:
	volatile uint8_t flasherState;
	volatile uint8_t fastFlasherState;

};

#endif // P8PANEL_H



