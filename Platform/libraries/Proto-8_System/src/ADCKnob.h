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
#ifndef ADCKNOB_H
#define ADCKNOB_H

#include "timeKeeper.h"
#include "flagMessaging.h"
#include "CircularBuffer.h"


//---New Knob----------------------------------------------------
class ADCKnob
{
public:
	ADCKnob( void ):values(16),averages(16){};
	void update( void );
	void init( uint8_t );
	uint8_t newDataFlag( void );
	uint8_t getAsUInt8( void );
	int16_t getAsInt16( void );
	uint16_t getAsUInt16( void );
	float getAsFloat( void );
	void setLowerKnobVal( uint16_t input )
	{
		if( input < 0 )input = 0;
		if( input > 1023 )input = 1023;
		lowerKnobVal = input;
	}
	void setUpperKnobVal( uint16_t input )
	{
		if( input < 0 )input = 0;
		if( input > 1023 )input = 1023;
		upperKnobVal = input;
	}
	void setLowerFloatVal( float input )
	{
		lowerFloatVal = input;
	}
	void setUpperFloatVal( float input )
	{
		upperFloatVal = input;
	}
	void setLowerIntVal( int16_t input )
	{
		lowerIntVal = input;
	}
	void setUpperIntVal( int16_t input )
	{
		upperIntVal = input;
	}
	void setLowerUIntVal( uint16_t input )
	{
		lowerUIntVal = input;
	}
	void setUpperUIntVal( uint16_t input )
	{
		upperUIntVal = input;
	}
	void setHysteresis( uint8_t input )
	{
		hysteresis = input;
	}
	CircularBuffer values;
	CircularBuffer averages;
	uint16_t lowerKnobVal = 0;
	uint16_t upperKnobVal = 1024;
	float lowerFloatVal = -1.0;
	float upperFloatVal = 1.0;
	int16_t lowerIntVal = -32768;
	int16_t upperIntVal = 32767;
	uint16_t lowerUIntVal = 0;
	uint16_t upperUIntVal = 65535;
	uint8_t hysteresis = 10;
	int32_t currentValue = 0;
	uint8_t newData;
	uint8_t posNumber;
	uint8_t hystState = 0; //can be 0 for lower or 1 for output (think positive feedback)
protected:
private:

};
#endif
