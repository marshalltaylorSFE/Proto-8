//**********************************************************************//
//
//  MIT License: http://opensource.org/licenses/MIT
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2015/10/08: Beta Release
//    2016/2/24: Forked to 'P8' set
//    2016/2/29: LEDs wrapped by VoltageMonitor + hysteresis fix
//
//**********************************************************************//
#ifndef P8PANELCOMPONENTS_H
#define P8PANELCOMPONENTS_H

#include "timeKeeper.h"
#include "flagMessaging.h"

//---Switch------------------------------------------------------
class P8PanelSwitch
{
public:
	P8PanelSwitch( void );
	void update( void );
	void init( uint8_t, uint8_t );
	MessagingFlag state;
	uint8_t invert;
	uint8_t posColNumber;
	uint8_t posRowNumber;
	TimeKeeper SwitchDebounceTimeKeeper;
protected:
private:
};

//---Knob--------------------------------------------------------
class P8PanelKnob8Bit
{
public:
	P8PanelKnob8Bit( void );
	void update( void );
	void init( uint8_t );
	uint8_t getState( void );
	uint8_t serviceChanged( void );
	uint8_t state;
	uint8_t lastState;
	const uint8_t hysteresis = 2;
	int8_t lastSlope = 1;
	uint8_t posNumber;
	uint8_t newData;
protected:
private:

};


//---Button------------------------------------------------------
enum buttonState_t
{
	BUTTONOFF = 0,
	BUTTONON = 1,
	BUTTONHOLD = 2,

};

class P8PanelButton
{
public:
	TimeKeeper buttonDebounceTimeKeeper;
	
	P8PanelButton( void );
	void update( void );
	void init( uint8_t, uint8_t );
	buttonState_t getState( void );
	uint8_t serviceRisingEdge( void );
	uint8_t serviceFallingEdge( void );
	uint8_t serviceHoldRisingEdge( void );
	uint8_t serviceHoldFallingEdge( void );
	void setBank( uint8_t );
	buttonState_t state;
	uint8_t invert;
	uint8_t posColNumber;
	uint8_t posRowNumber;
	uint8_t cache;
protected:
private:
	uint8_t beingHeld;
	uint8_t risingEdgeFlag;
	uint8_t fallingEdgeFlag;
	uint8_t holdRisingEdgeFlag;
	uint8_t holdFallingEdgeFlag;
};

//---Led---------------------------------------------------------
enum ledState_t
{
	LEDON = 0,
	LEDOFF = 1,
	LEDFLASHING = 2,
	LEDFLASHINGFAST = 3
};

class P8PanelLed
{
public:
	P8PanelLed( void );
	void update( void );
	void init( uint8_t );
	void init( uint8_t, volatile uint8_t * volatile , volatile uint8_t * volatile );
	ledState_t getState( void );
	void setState( ledState_t );
	void toggle( void );
	ledState_t state;
	uint8_t posNumber;
	uint8_t cache;
protected:
private:
	volatile uint8_t * volatile flasherState;
	volatile uint8_t * volatile fastFlasherState;

};

//---Selector----------------------------------------------------
class P8PanelSelector
{
public:
	P8PanelSelector( void );
	~P8PanelSelector( void );
	void update( void );
	void init( uint8_t, uint8_t, uint8_t );  //calls init(,,,);
	void init( uint8_t, uint8_t, uint8_t, uint8_t);//pinNum, maxInput, minInput, number of points
	uint8_t getState( void );

	uint8_t serviceChanged( void );
protected:
private:
	uint8_t state;
	uint8_t posNumber;
	uint8_t * thresholds;
	uint8_t changedFlag;
	uint8_t points;
};

#endif
