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
	
	
	//Bus
	P8PanelKnob8Bit bus1Amp;
	P8PanelKnob8Bit bus1Offset;
	P8PanelButton bus1SrcPick;
	P8PanelButton bus1DestPick;
	P8PanelLed bus1SrcLed;
	P8PanelLed bus1DestLed;
	
	P8PanelKnob8Bit bus2Amp;
	P8PanelKnob8Bit bus2Offset;
	P8PanelButton bus2SrcPick;
	P8PanelButton bus2DestPick;
	P8PanelLed bus2SrcLed;
	P8PanelLed bus2DestLed;

	P8PanelKnob8Bit bus3Amp;
	P8PanelKnob8Bit bus3Offset;
	P8PanelButton bus3SrcPick;
	P8PanelButton bus3DestPick;
	P8PanelLed bus3SrcLed;
	P8PanelLed bus3DestLed;

	P8PanelKnob8Bit bus4Amp;
	P8PanelKnob8Bit bus4Offset;
	P8PanelButton bus4SrcPick;
	P8PanelButton bus4DestPick;
	P8PanelLed bus4SrcLed;
	P8PanelLed bus4DestLed;

	P8PanelKnob8Bit bus5Amp;
	P8PanelKnob8Bit bus5Offset;
	P8PanelButton bus5SrcPick;
	P8PanelButton bus5DestPick;
	P8PanelLed bus5SrcLed;
	P8PanelLed bus5DestLed;
	
	P8PanelLed modSrcLed0;
	P8PanelLed modSrcLed1;
	P8PanelLed modSrcLed2;
	P8PanelLed modSrcLed3;
	P8PanelLed modSrcLed4;
	P8PanelLed modSrcLed5;
	P8PanelLed modSrcLed6;
	P8PanelLed modSrcLed7;
	P8PanelLed modSrcLed8;
	P8PanelLed modSrcLed9;
	P8PanelLed modSrcLed10;
	P8PanelLed modSrcLed11;
	P8PanelLed modSrcLed12;
	P8PanelLed modSrcLed13;
	P8PanelLed modSrcLed14;
	
	P8PanelLed modDestLed0;
	P8PanelLed modDestLed1;
	P8PanelLed modDestLed2;
	P8PanelLed modDestLed3;
	P8PanelLed modDestLed4;
	P8PanelLed modDestLed5;
	P8PanelLed modDestLed6;
	P8PanelLed modDestLed7;
	P8PanelLed modDestLed8;
	P8PanelLed modDestLed9;
	P8PanelLed modDestLed10;
	P8PanelLed modDestLed11;
	P8PanelLed modDestLed12;
	P8PanelLed modDestLed13;
	P8PanelLed modDestLed14;
	
	//Master
	P8PanelKnob8Bit masterCoarseTune;
	P8PanelKnob8Bit masterFineTune;
	P8PanelKnob8Bit masterVolume;
	
	//General
	P8PanelKnob8Bit Select;
	
protected:
private:
	volatile uint8_t flasherState;
	volatile uint8_t fastFlasherState;

};

#endif // P8PANEL_H



