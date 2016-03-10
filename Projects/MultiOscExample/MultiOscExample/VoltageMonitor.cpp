//
//  Change log;
//    2/24/2016 -- Created;

#include "Arduino.h"
#include <SPI.h>
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

VoltageMonitor::VoltageMonitor()
{
	
}

void VoltageMonitor::tickSeg()
{
	if( state < 8 )
	{
		SPI.transfer(LEDData[7-state]);
		state++;
	}
	else if( state == 8 )
	{
		//Fwap the clock
		digitalWrite(LCLKPin, 0);
		state++;
	}
	else if( state == 9 )
	{
		digitalWrite(LCLKPin, 1);		
		state = 0;
		if(scanDigit == 0)
		{
			LEDData[5] = 0x00;
		}
		else
		{
			LEDData[5] = 0x80;
		}

		//LEDData[5] = (LEDData[5] & ~0x80) | ((0x00800000 & digitSelectLUT[scanDigit]) >> 16);
		//Serial.println(LEDData[5],BIN);
		LEDData[6] = ((((digitSelectLUT[10] & digitSelectLUT[scanDigit]) >> 8 ) & 0x00FF) | ((segmentsSelectLUT[dispBuffer[scanDigit]] >> 8) & 0x00FF));
		//Serial.println(LEDData[6],BIN);
		LEDData[7] = ((((digitSelectLUT[10] & digitSelectLUT[scanDigit])) & 0x000FF) | ((segmentsSelectLUT[dispBuffer[scanDigit]]) & 0x00FF));
		//Serial.println(LEDData[7],BIN);
		//Serial.println();
		//LEDData[5] = 0x00; 
		//LEDData[6] = 0x55;
		//LEDData[7] = 0x57;
		if(decimals[scanDigit] == 1)
		{
			LEDData[7] |= (segmentsSelectLUT[11] & 0x000FF);
		}
		scanDigit++;
		if(scanDigit > 8) scanDigit = 0;
	}

}

void VoltageMonitor::setNumber1( uint16_t inputVal )
{
	uint16_t inputTemp = inputVal;
	uint16_t mathTemp = 0;
	for( int i = 0; i < 9; i++ )
	{
		mathTemp = inputTemp%10;
		if(( inputTemp > 0 )||( i == 0 ))
		{
			dispBuffer[8 - i] = mathTemp;
		}
		else
		{
			dispBuffer[8 - i] = 10;
		}
		inputTemp /= 10;
	}
}

void VoltageMonitor::setVoltage( float inputVal, uint8_t inputPos )
{
	float wholePart = 0;
	float workingReg = 0;
	//Sanitize pos
	//... nope, be real

	decimals[inputPos] = 0;
	//Find the whole part
	wholePart = (uint8_t)inputVal;
	//Give it the clamps
	if( wholePart > 9 )
	{
		dispBuffer[inputPos] = 11;
	}
	else
	{
		dispBuffer[inputPos] = wholePart;
	}
	
	//Place the decimal
	decimals[inputPos] = 1;
	//Find the 1/10 decimal
	workingReg = ((inputVal - wholePart) * 10);
	wholePart = (uint8_t)workingReg;
	dispBuffer[inputPos + 1] = wholePart;
	//Find the 1/100 decimal
	workingReg = ((workingReg - wholePart) * 10);
	wholePart = (uint8_t)workingReg;
	dispBuffer[inputPos + 2] = wholePart;
}