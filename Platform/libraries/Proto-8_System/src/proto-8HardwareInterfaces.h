#ifndef PROTO8_HARDWARE_INTERFACES_H
#define PROTO8_HARDWARE_INTERFACES_H

#include <Arduino.h>
#include <HardwareInterfaces.h>
#include <PanelDataObjects.h>

//The abstract class GenericHardwareDescription must be inheireted
// by the interface to whatever external driver is being used.  Data must be present
// or set-able by the readHardware and writeHardware definitions.

//GenericHardwareDescription Supplied by HardwareInterfaces.h

class Proto8DigitalIn : public GenericHardwareDescription
{
public:
	Proto8DigitalIn( int inputCol, int inputRow );
	void readHardware( void );
protected:
	int col;
	int row;
};

class Proto8DigitalOut : public GenericHardwareDescription
{
public:
	Proto8DigitalOut( int inputPosition );
	void writeHardware( void );
protected:
	int position;
};

class Proto8AnalogIn : public GenericHardwareDescription
{
public:
	Proto8AnalogIn( int inputNumber );
	void readHardware( void );
protected:
	int number;
};

#endif