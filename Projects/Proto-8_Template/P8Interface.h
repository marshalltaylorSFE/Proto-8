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
#include "PanelComponents.h"
#include "P8Panel.h"
#include "flagMessaging.h"

#include "Audio.h"
#include "synth_dc_binary.h"


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
	
	//Flags coming in from the system
	//  ..and data.
	
private:
	//Internal Flags
	uint8_t lfo1WaveSrc;
	uint8_t lfo2WaveSrc;
	uint8_t oscAWaveSrc;
	uint8_t oscBWaveSrc;
	uint8_t oscCWaveSrc;
	uint8_t oscDWaveSrc;

	//State machine stuff  
	PStates state;


};


#endif