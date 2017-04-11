#include <Arduino.h>
#include <proto-8Hardware.h>
#include <VoltageMonitor.h>
#include <proto-8HardwareInterfaces.h>

//proto-8Hardware
extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

//Proto8 Digital in
Proto8DigitalIn::Proto8DigitalIn(  int inputCol, int inputRow )
{
	localData.size = 1;
	localData.data = new uint8_t[localData.size];
	col = inputCol;
	row = inputRow - 1; // range: 0-3
}

void Proto8DigitalIn::readHardware( void )
{
	uint16_t tempNumber = (row * 16) + col;
	*localData.data = switches.fetch( tempNumber );
};

//Proto8 Digital out
Proto8DigitalOut::Proto8DigitalOut( int inputPosition )
{
	localData.size = 1;
	localData.data = new uint8_t[localData.size];
	position = inputPosition;
}

void Proto8DigitalOut::writeHardware( void )
{
	LEDs.store(position, *localData.data);
};

//Proto8 Analog in
Proto8AnalogIn::Proto8AnalogIn( int inputNumber )
{
	localData.size = 2;
	localData.data = new uint8_t[localData.size];
	number = inputNumber;
}

void Proto8AnalogIn::readHardware( void )
{
	*(uint16_t *)localData.data = knobs.fetch( number );
};
