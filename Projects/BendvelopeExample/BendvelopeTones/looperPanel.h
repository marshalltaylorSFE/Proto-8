//Header
#ifndef LOOPERPANEL_H_INCLUDED
#define LOOPERPANEL_H_INCLUDED


#include "stdint.h"
#include "timeKeeper.h"
#include "PanelComponents.h"
#include "Panel.h"
#include "flagMessaging.h"

enum PStates
{
	PInit,
	PIdle,
	PFirstRecord,
	PPlay,
	POverdub,
	PUndoClearOverdub,
	PUndoDecrement,
	PUndoClearTrack

};

class LooperPanel : public Panel
{
public:
	LooperPanel( void );
	void setRxLed( void );
	ledState_t serviceRxLed( void );
	//State machine stuff  
	void processMachine( void );
	void tickStateMachine( void );

	void timersMIncrement( uint8_t );

	
	//Flags coming in from the system
	uint8_t rxLedFlag;
	

private:
	//State machine stuff  
	PStates state;

};

#endif