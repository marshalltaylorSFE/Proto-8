
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine3;          //xy=176.88888549804688,208
AudioSynthWaveformSine   sine1;          //xy=177.88888549804688,112
AudioSynthWaveformSine   sine2;          //xy=177.88888549804688,160
AudioSynthWaveformSine   sine4;          //xy=177.88888549804688,258
AudioOutputI2SQuad       i2s_quad1;      //xy=454.888916015625,147
AudioConnection          patchCord1(sine3, 0, i2s_quad1, 2);
AudioConnection          patchCord2(sine1, 0, i2s_quad1, 0);
AudioConnection          patchCord3(sine2, 0, i2s_quad1, 1);
AudioConnection          patchCord4(sine4, 0, i2s_quad1, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=429.888916015625,226
AudioControlSGTL5000     sgtl5000_2;     //xy=429.888916015625,271
// GUItool: end automatically generated code


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
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

//**Timers and stuff**************************//
#include "timerModule32.h"

#include "timeKeeper.h"

//**Panel*************************************//
#include "P8Panel.h"

P8Panel p8hid;

//**Timers and stuff**************************//
IntervalTimer myTimer;

//HOW TO OPERATE
//  Make TimerClass objects for each thing that needs periodic service
//  pass the interval of the period in ticks
//  Set maxInterval to the max foreseen interval of any TimerClass
//  Set maxTimer to overflow number in the header.  maxTimer + maxInterval
//    cannot exceed variable size.
//Globals
uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;

TimerClass32 panelUpdateTimer(10000);

TimerClass32 LEDsTimer(200);
TimerClass32 switchesTimer(500);
TimerClass32 knobsTimer(500);

TimerClass32 debugTimer(333000);

//tick variable for interrupt driven timer1
uint32_t usTicks = 0;
uint8_t usTicksMutex = 1; //start locked out

//proto-8Hardware
VoltageMonitor LEDs;
AnalogMuxTree knobs;
SwitchMatrix switches;

void setup()
{
	//**** Audio Section ****//
	AudioMemory(35);
	
	sgtl5000_1.setAddress(LOW);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);
	
	sgtl5000_2.setAddress(HIGH);
	sgtl5000_2.enable();
	sgtl5000_2.volume(0.5);
	
	sine1.amplitude(1);
	sine1.frequency(440);
	
	sine2.amplitude(1);
	sine2.frequency(220);
	
	sine3.amplitude(1);
	sine3.frequency(440);
	
	sine4.amplitude(1);
	sine4.frequency(350);
	
	Serial.begin(115200);
	
	LEDs.begin();
	knobs.begin();
	switches.begin();
	delay(1000);

	p8hid.reset();
	
	delay(1000);
	Serial.println("Program Started");
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	
}

void loop()
{
//**Copy to make a new timer******************//  
//   msTimerA.update(usTicks);
	panelUpdateTimer.update(usTicks);
	LEDsTimer.update(usTicks);
	switchesTimer.update(usTicks);
	knobsTimer.update(usTicks);
	debugTimer.update(usTicks);
	
//**Copy to make a new timer******************//  
	//  if(msTimerA.flagStatus() == PENDING)
	//  {
	//    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
	//  }
	
	//**uCModules timer***************************//  
	if(panelUpdateTimer.flagStatus() == PENDING)
	{
		p8hid.tickStateMachine(10);
	
	}
	//**proto-8Hardware timers********************//  
	if(LEDsTimer.flagStatus() == PENDING)
	{
		LEDs.tickSeg();
	
	}
	if(switchesTimer.flagStatus() == PENDING)
	{
		switches.tick();
	
	}
	if(knobsTimer.flagStatus() == PENDING)
	{
		knobs.tick();
	
	}	

	//**Debug timer*******************************//  
	if(debugTimer.flagStatus() == PENDING)
	{
		Serial.println("**************************Debug Service**************************");
		Serial.println("Reading Knobs.");
		
		int temp;
		for(int j = 0; j < 8; j++)
		{
			for(int i = 0; i < 8; i++)
			{
				temp = (j * 8) + i + 1;
				Serial.print(knobs.fetch(temp));
				Serial.print(", ");
			}
			Serial.print("\n");
		}
		
		Serial.print("\nReading Switches.");
		for(int i = 1; i < 65; i++)
		{
			if((i == 1)||(i == 17)||(i == 33)||(i == 49))
			{
				Serial.println();
			}
			Serial.print(switches.fetch(i));
			//Serial.print(i);
			Serial.print(", ");
		}
		Serial.println();
		
		Serial.println("\nLED data");
		for(int i = 0; i < 8; i++)
		{
			uint8_t ledpack = LEDs.LEDData[i];
			if(ledpack < 0x80) Serial.print("0");
			if(ledpack < 0x40) Serial.print("0");
			if(ledpack < 0x20) Serial.print("0");
			if(ledpack < 0x10) Serial.print("0");
			if(ledpack < 0x08) Serial.print("0");
			if(ledpack < 0x04) Serial.print("0");
			if(ledpack < 0x02) Serial.print("0");
			Serial.println(ledpack, BIN);
			//Serial.print(i);
		}
		Serial.println();		
		Serial.println();

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