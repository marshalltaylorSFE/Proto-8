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
#include "proto-8PanelComponents.h"
#include "proto-8HardwareInterfaces.h"

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
	Selector fixtureKnob;

	//State machine stuff  
	PStates state;
	
};

#endif // P8PANEL_H



