//**********************************************************************//
//
//  Patch cord changer interface.
//
//  Hardware:
//    16 buttons
//    16 LEDs
//    Knob on 64
//    scanned matrix 7 segment display.
//  
//  This file defines the human interaction of the panel parts
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//    2016/2/29: Moved seven segment stuff to voltage monitor
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
#ifndef P8INTERFACE_H
#define P8INTERFACE_H

#include "stdint.h"
#include "timeKeeper.h"
#include "PanelComponents.h"
#include "P8Panel.h"
#include "flagMessaging.h"

#include "Audio.h"

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
	void processMachine( uint16_t );
	void tickStateMachine( void );
	
private:
	//Internal Flags
	//MessagingFlag quantizeHoldOffFlag;

	//Internal Data
	int8_t select1;
	int8_t select2;
	int8_t select3;
	int8_t select4;

	//State machine stuff  
	PStates state;
	uint8_t debugTemp;
};


#endif