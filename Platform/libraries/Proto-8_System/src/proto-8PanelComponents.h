#ifndef PROTO_8_PANEL_COMPONENTS
#define PROTO_8_PANEL_COMPONENTS

#include "stdint.h"
#include "PanelComponents.h"
#include "HardwareInterfaces.h"

//---Selector----------------------------------------------------
class Selector : public KnobParentClass
{
public:
	Selector( void );
	~Selector( void );
	virtual void freshen( uint16_t msTickDelta );
	uint16_t getState( void );
	void init( uint16_t, uint16_t, uint8_t);//maxInput, minInput, number of points

protected:
private:
	uint16_t state;
	uint16_t lastState;
	uint16_t * thresholds;
	uint8_t points;
};

//---FastWindowed10BitKnob---------------------------------------------
class FastWindowed10BitKnob : public Complex10BitKnob
{
public:
	FastWindowed10BitKnob( void );
	virtual void freshen( uint16_t msTickDelta );
	void setWindow( int16_t input );
protected:
	void moveWindowUpper( uint16_t input );
	void moveWindowLower( uint16_t input );
	int16_t windowUpper = 60;
	int16_t windowLower = 40;
	int16_t window = 50;
	int8_t lastSlope = 1;
};

#endif
