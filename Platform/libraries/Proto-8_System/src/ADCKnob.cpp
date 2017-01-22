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
#include "ADCKnob.h"
#include "Arduino.h"
#include "CircularBuffer.h"

//---New Knob----------------------------------------------------
void ADCKnob::init( uint8_t posInput )
{
  posNumber = posInput;
  pinMode(posInput, INPUT);
  update();
}

void ADCKnob::update( void )
{
	//Read the knob value into the buffer
	values.write(analogRead( posNumber ));
	//Get the averages
	int32_t accumulator = 0;
	accumulator += values.read(0);
	accumulator += values.read(1);
	accumulator += values.read(2);
	accumulator += values.read(3);
	accumulator += values.read(4);
	accumulator += values.read(5);
	accumulator += values.read(6);
	accumulator += values.read(7);
	accumulator += values.read(8);
	accumulator += values.read(9);
	averages.write(accumulator/10);
	if(hystState == 0)
	{
		if( averages.read(0) > currentValue )
		{
			//Allow current to go up only
			currentValue = averages.read(0);
			newData = 1;
		}
		if( averages.read(0) < currentValue - hysteresis )
		{
			//toggle behavior
			hystState = 1;
			currentValue = averages.read(0);
			newData = 1;			
		}
	}
	else
	{
		if( averages.read(0) < currentValue )
		{
			//Allow current to go up only
			currentValue = averages.read(0);
			newData = 1;
		}
		if( averages.read(0) > currentValue + hysteresis )
		{
			//toggle behavior
			hystState = 0;
			currentValue = averages.read(0);
			newData = 1;			
		}
	}
}
uint8_t ADCKnob::getAsUInt8( void )
{
	newData = 0;
	return currentValue >> 2;
}
int16_t ADCKnob::getAsInt16( void )
{
	uint32_t tempValue = currentValue;
	if( tempValue < lowerKnobVal ) tempValue = lowerKnobVal;
	if( tempValue > upperKnobVal ) tempValue = upperKnobVal;
	// now find scalar from 0 to 1
	float inputPercent = ((float)(tempValue - lowerKnobVal))/(float)(upperKnobVal - lowerKnobVal);
	float outputRange = upperIntVal - lowerIntVal;
	newData = 0;
	return lowerIntVal + (inputPercent * outputRange);
}
uint16_t ADCKnob::getAsUInt16( void )
{
	uint32_t tempValue = currentValue;
	if( tempValue < lowerKnobVal ) tempValue = lowerKnobVal;
	if( tempValue > upperKnobVal ) tempValue = upperKnobVal;
	// now find scalar from 0 to 1
	float inputPercent = ((float)(tempValue - lowerKnobVal))/(float)(upperKnobVal - lowerKnobVal);
	float outputRange = upperUIntVal - lowerUIntVal;
	newData = 0;
	return lowerUIntVal + (inputPercent * outputRange);
}
float ADCKnob::getAsFloat( void )
{
	uint32_t tempValue = currentValue;
	if( tempValue < lowerKnobVal ) tempValue = lowerKnobVal;
	if( tempValue > upperKnobVal ) tempValue = upperKnobVal;
	// now find scalar from 0 to 1
	float inputPercent = ((float)(tempValue - lowerKnobVal))/(float)(upperKnobVal - lowerKnobVal);
	float outputRange = upperFloatVal - lowerFloatVal;
	newData = 0;
	return lowerFloatVal + (inputPercent * outputRange);
}
uint8_t ADCKnob::newDataFlag( void )
{
	return newData;
}
