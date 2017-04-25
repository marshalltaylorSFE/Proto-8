//**********************************************************************//
//
//  Interface
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
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

	void timersMIncrement( uint8_t );

	//Internal - and going out to the system - Flags
	uint8_t filterOutputState;
	uint8_t audioChanState;


private:
	//Internal Flags

	//State machine stuff  
	PStates state;


};


#endif