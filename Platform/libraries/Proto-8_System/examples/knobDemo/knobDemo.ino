//**********************************************************************//
//
//  Top-level for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//  The serial debug shows internal variables
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//
//**********************************************************************//

#include "timerModule32.h"
#include "timeKeeper.h"
#include "ADCKnob.h"

IntervalTimer myTimer;

uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;

TimerClass32 knobTimer(5000);
TimerClass32 debugTimer(333000);

//tick variable for interrupt driven timer1
uint32_t usTicks = 0;
uint8_t usTicksMutex = 1; //start locked out

int8_t loopCount = 0;
int8_t maxLoopCount = 20;

#define	KNOB1POS A1
#define	KNOB2POS A2
#define	KNOB3POS A3
#define	KNOB4POS A6
#define	KNOB5POS A7

ADCKnob knob1;
ADCKnob knob2;
ADCKnob knob3;
ADCKnob knob4;
ADCKnob knob5;

void setup()
{
	knob1.init(KNOB1POS);
	knob2.init(KNOB2POS);
	knob3.init(KNOB3POS);
	knob4.init(KNOB4POS);
	knob5.init(KNOB5POS);
	for(int i = 0; i < 10; i++) //Run update a few times to fill the averaging buffers
	{
		knob1.update();
		knob2.update();
		knob3.update();
		knob4.update();
		knob5.update();
	}

	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	delay(1000);
	Serial.println("Program Started");
	knob1.setLowerKnobVal(300);
	knob1.setUpperKnobVal(700);
	
}

void loop()
{
	knobTimer.update(usTicks);
	debugTimer.update(usTicks);
	
	//**Knob timer*******************************//  
	if(knobTimer.flagStatus() == PENDING)
	{
		knob1.update();
		knob2.update();
		knob3.update();
		knob4.update();
		knob5.update();
	}
	//**Debug timer*******************************//  
	if(debugTimer.flagStatus() == PENDING)
	{
		if(knob1.newDataFlag())
		{
			Serial.println("Knob 1 data:");
			Serial.println(knob1.getAsUInt8());
			Serial.println(knob1.getAsInt16());
			Serial.println(knob1.getAsUInt16());
			Serial.println(knob1.getAsFloat());
		}
		if(knob2.newDataFlag())
		{
			Serial.println("Knob 2 data:");
			Serial.println(knob2.getAsUInt8());
			Serial.println(knob2.getAsInt16());
			Serial.println(knob2.getAsUInt16());
			Serial.println(knob2.getAsFloat());
		}
		if(knob3.newDataFlag())
		{
			Serial.println("Knob 3 data:");
			Serial.println(knob3.getAsUInt8());
			Serial.println(knob3.getAsInt16());
			Serial.println(knob3.getAsUInt16());
			Serial.println(knob3.getAsFloat());
		}
		if(knob4.newDataFlag())
		{
			Serial.println("Knob 4 data:");
			Serial.println(knob4.getAsUInt8());
			Serial.println(knob4.getAsInt16());
			Serial.println(knob4.getAsUInt16());
			Serial.println(knob4.getAsFloat());
		}
		if(knob5.newDataFlag())
		{
			Serial.println("Knob 5 data:");
			Serial.println(knob5.getAsUInt8());
			Serial.println(knob5.getAsInt16());
			Serial.println(knob5.getAsUInt16());
			Serial.println(knob5.getAsFloat());
		}
	}
	
}

void serviceUS(void)
{
  uint32_t returnVar = 0;
  if(usTicks >= ( maxTimer + maxInterval ))
  {
    returnVar = usTicks - maxTimer;

  }
  else
  {
    returnVar = usTicks + 1;
  }
  usTicks = returnVar;
  usTicksMutex = 0;  //unlock
}