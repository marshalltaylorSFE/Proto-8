#include "stdint.h"
#include "PanelComponents.h"
#include "proto-8PanelComponents.h"
#include "HardwareInterfaces.h"

//---Selector---------------------------------------------------------
Selector::Selector( void )
{
	points = 10;
}

Selector::~Selector( void )
{
	delete[] thresholds;
}

// 8 bit resolution on the ADC should be fine.
void Selector::init( uint16_t maxInput, uint16_t minInput, uint8_t pointsInput )
{
	if( pointsInput < 2 )
	{
		points = 2;
	}
	else
	{
		points = pointsInput - 1; //( by (n-1) not n )
	}
	thresholds = new uint16_t[points];

	//Set up the ranges
	uint16_t stepHeight = ( maxInput - minInput ) / points;
	thresholds[0] = minInput + ( stepHeight / 2 );
	int i;
	for( i = 1; i < points; i++ )
	{
		thresholds[i] = thresholds[i - 1] + stepHeight;
	
	}

}

void Selector::freshen( uint16_t msTickDelta )
{
	//Throw away input
	//Cause the interface to get the data
	hardwareInterface->readHardware();
	//Collect the data
	KnobDataObject tempObject;
	hardwareInterface->getData(&tempObject);
	
	uint16_t freshData = *(uint16_t *)tempObject.data;

	state = 0;
	//Seek the position
	int i;
	for( i = 0; i < points; i++ )
	{
		if( freshData > thresholds[i] )
		{
			state = i + 1; //It's this or higher
		}
	}
	//Check if new
	if( state != lastState )
	{
		newData = 1;
		lastState = state;
	}

}

uint16_t Selector::getState( void )
{
   return state;
}

//---Windowed10BitKnob--------------------------------------------------------
FastWindowed10BitKnob::FastWindowed10BitKnob( void )
{
}

void FastWindowed10BitKnob::freshen( uint16_t msTickDelta )
{
	//Throw away input
	//Cause the interface to get the data
	hardwareInterface->readHardware();
	//Collect the data
	KnobDataObject tempObject;
	hardwareInterface->getData(&tempObject);
	
//		Serial.println("knobFreshen");
//		Serial.print("Temp ");
//		dumpObject(&tempObject);
	uint16_t tempState = *(uint16_t *)tempObject.data;
	//Read the knob value into the buffer
	//Serial.println(tempState);
	if( tempState > windowUpper )
	{
		moveWindowUpper( tempState );
		newData = 1;
	}
	if( tempState < windowLower )
	{
		moveWindowLower( tempState );
		newData = 1;
	}
	uint32_t temp = windowLower + (window >> 1);
	//scale it
	currentValue = ((temp - (window >> 1)) << 10 ) / (1024 - window );
}

void FastWindowed10BitKnob::setWindow( int16_t input )
{
	window = input;
}

void FastWindowed10BitKnob::moveWindowUpper( uint16_t input )
{
	windowUpper = input;
	windowLower = input - window;
}

void FastWindowed10BitKnob::moveWindowLower( uint16_t input )
{
	windowLower = input;
	windowUpper = input + window;
	
}