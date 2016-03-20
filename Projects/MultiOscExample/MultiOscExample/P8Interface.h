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
//    2016/2/29: Moved seven segment stuff to voltage monitor
//
//**********************************************************************//
#ifndef P8INTERFACE_H
#define P8INTERFACE_H

#include "stdint.h"
#include "timeKeeper.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "flagMessaging.h"


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
	uint8_t lastAttack;
	uint8_t lastAttackBend;
	uint8_t lastAttackHold;
	uint8_t lastDecay;
	uint8_t lastDecayBend;
	uint8_t lastSustain;
	uint8_t lastRelease;
	uint8_t lastReleaseBend;
		
		
	//  ..and data.

private:
	//Internal Flags
	//MessagingFlag quantizeHoldOffFlag;
	MessagingFlag changeVolume;
	//  ..and data
	int8_t waveformShape1 = 1;
	int8_t waveformShape2 = 1;
	int8_t waveformShape3 = 1;
	int8_t waveformShape4 = 1;
	int8_t group1Store = 0;
	int8_t group2Store = 0;
	int8_t group3Store = 0;
	
	int8_t oscASelect = 0;
	int8_t oscBSelect = 0;
	
	//State machine stuff  
	PStates state;
	uint8_t debugTemp = 0;
	
};


#endif