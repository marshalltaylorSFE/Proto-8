//
//  Change log;
//    2/24/2016 -- Created;

#if !defined(VOLTAGE_MONITOR_H)
#define VOLTAGE_MONITOR_H

#include "Arduino.h"
#include "proto-8Hardware.h"

const uint8_t digitsLUT [11] = 
{
0x7b,
0x60,
0x5d,
0x75,
0x66,
0x37,
0x3f,
0x61,
0x7f,
0x67,
0x00
};

const uint32_t digitSelectLUT [11] = 
{
0xFFEFFFFF,//0x00100000,
0xFFFFFFBF,//0x00000040,
0xFFFFFFEF,//0x00000010,
0xFFFFFFFB,//0x00000020,
0xFFFFFFFE,//0x00000080,
0xFFFFBFFF,//0x00000200,
0xFFFFEFFF,//0x00000800,
0xFFFFFBFF,//0x00002000,
0xFFFFFEFF,//0x00008000,
0xFFFFFFFF,//0x00000000
0x00105555
};
const uint32_t segmentsSelectLUT [12] = 
{
0x00008A8A,
0x00000880,
0x0000A80A,
0x0000A888,
0x00002A80,
0x0000A288,
0x0000A28A,
0x00000888,
0x0000AA8A,
0x00002A88,
0x00000000,
0x00000004
};


class VoltageMonitor : public LEDShiftRegister
{
public:
	VoltageMonitor( void );
	void tickSeg( void );
	void setNumber1( uint16_t );
	//void setNumber2( uint8_t );
	//void setNumber3( uint8_t );
private:
	uint8_t scanDigit;
	uint8_t dispBuffer[9];
	
};


#endif