//**********************************************************************//
//
//  Interface example for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//  This file defines the human interaction of the panel parts
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//
//**********************************************************************//
#ifndef P8INTERFACE_H
#define P8INTERFACE_H

#include "stdint.h"
#include "timeKeeper.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "flagMessaging.h"

const uint8_t digitsLUT [11] = 
{
0x7b,
0x60,
0x5d,
0x75,
0x66,
0x37,
0x3f,
0x61,
0x7f,
0x67,
0x00
};

class HpSeg
{
public:
	HpSeg( void );
	void update( void );
	void setNumber1( uint16_t );
private:
	uint16_t number1;
	uint8_t scanDigit;
	uint8_t dispBuffer[9];
	
};


enum PStates
{
	PInit,
	PIdle,

};

class P8Interface : public P8Panel
{
public:
	P8Interface( void );
	void reset( void );
	//State machine stuff  
	void processMachine( void );
	void tickStateMachine( void );

	void timersMIncrement( uint8_t );
	
	//Flags coming in from the system
	
	//Internal - and going out to the system - Flags
	
	//  ..and data.

private:
	//Internal Flags
	//MessagingFlag quantizeHoldOffFlag;
	//  ..and data

	//State machine stuff  
	PStates state;
	
	HpSeg display1;

};


#endif