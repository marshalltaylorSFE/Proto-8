//**********************************************************************//
//
//  Patch Cord Changer
//
//  Hardware:
//    16 buttons (5 used)
//    16 LEDs (4 used)
//    Knob on 64
//    scanned matrix 7 segment display.
//  
//  This project demonstrates moving 4 patchcords around on the fly
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//    2017/4/24: Converted to uCModules 2.0 interface
//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//**********************************************************************//

//This is a audio tool configuration that is unmodified

//// GUItool: begin automatically generated code
//AudioSynthWaveform       waveform1;     //xy=240,7
//AudioSynthWaveform       waveform2;     //xy=248,157
//AudioSynthWaveform       waveform3;     //xy=256,307
//AudioSynthWaveform       waveform4;     //xy=264,457
//AudioOutputI2SQuad       i2s_quad2;      //xy=1476,238
//AudioConnection          patchCord1(waveform1, 0, i2s_quad2, 0);
//AudioConnection          patchCord2(waveform2, 0, i2s_quad2, 1);
//AudioConnection          patchCord3(waveform3, 0, i2s_quad2, 2);
//AudioConnection          patchCord4(waveform4, 0, i2s_quad2, 3);
//AudioControlSGTL5000     sgtl5000_2;     //xy=1430.0,93.0
//AudioControlSGTL5000     sgtl5000_1;     //xy=1434.0,49.0
//// GUItool: end automatically generated code


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"

AudioSynthWaveform       waveform1;     //xy=240,7
AudioSynthWaveform       waveform2;     //xy=248,157
AudioSynthWaveform       waveform3;     //xy=256,307
AudioSynthWaveform       waveform4;     //xy=264,457
AudioOutputI2SQuad       i2s_quad2;      //xy=1476,238

//These patchcords are created without any connection
AudioConnection          patchCord1;
AudioConnection          patchCord2;
AudioConnection          patchCord3;
AudioConnection          patchCord4;

AudioControlSGTL5000     sgtl5000_2;     //xy=1430.0,93.0
AudioControlSGTL5000     sgtl5000_1;     //xy=1434.0,49.0

#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

//**Timers and stuff**************************//
#include "timerModule32.h"
#include "timeKeeper.h"

//Globals
uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;

IntervalTimer myTimer; // For interrupt

TimerClass32 panelUpdateTimer(30000);

TimerClass32 LEDsTimer(20);
TimerClass32 switchesTimer(500);
TimerClass32 knobsTimer(500);

TimerClass32 debugTimer(5000000);

//#include "MicroLL.h"

uint8_t debugLedStates = 1;

//**P8Panel.h defines the Proto-8 hardware****//
#include "P8Panel.h"

//tick variable for interrupt driven timer1
uint32_t usTicks = 0;
uint8_t usTicksMutex = 1; //start locked out

//**Panel State Machine***********************//
#include "P8Interface.h"

P8Interface p8hid;

volatile int32_t pUTStartTime = 0;
volatile int32_t pUTLastTime = 0;
volatile int32_t pUTStopTime = 0;
volatile int32_t pUTLength = 0;

//Names use in P8PanelComponents.cpp and .h
VoltageMonitor LEDs;
AnalogMuxTree knobs;
SwitchMatrix switches;
//End used names

// MIDI things
#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);

uint8_t rxLedFlag = 0;

// -----------------------------------------------------------------------------
void setup() 
{
	//Initialize serial:
	Serial.begin(9600);
	delay(2000);
	Serial.println("Program Started");
	
	LEDs.begin();
	knobs.begin();
	switches.begin();
	
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	
	//Reset the panel
	p8hid.reset();

	AudioMemory(50);

	sgtl5000_1.setAddress(LOW);	
	sgtl5000_1.enable();
	sgtl5000_1.volume(1.0);
	sgtl5000_1.unmuteHeadphone();
	sgtl5000_1.unmuteLineout();
	
	sgtl5000_2.setAddress(HIGH);
	sgtl5000_2.enable();
	sgtl5000_2.volume(1.0);
	sgtl5000_2.unmuteHeadphone();
	sgtl5000_2.unmuteLineout();
	
	
	waveform1.begin(0.1, 100, WAVEFORM_SINE);
	waveform2.begin(0.1, 100, WAVEFORM_SINE);
	waveform3.begin(0.1, 100, WAVEFORM_SINE);
	waveform4.begin(0.1, 100, WAVEFORM_SINE);
	waveform1.frequency(200);
	waveform2.frequency(400);
	waveform3.frequency(800);
	waveform4.frequency(1600);
}

void loop()
{
	usTicksMutex = 1;

	panelUpdateTimer.update(usTicks);

	switchesTimer.update(usTicks);
	knobsTimer.update(usTicks);
	LEDsTimer.update(usTicks);

	debugTimer.update(usTicks);
	
	usTicksMutex = 0;

	//**Switches timer****************************//  
	if(switchesTimer.flagStatus() == PENDING)
	{
		switches.tick();
	
	}
	//**Knobs timer****************************//  
	if(knobsTimer.flagStatus() == PENDING)
	{
		knobs.tick();
	
	}		
	//**LEDs timer****************************//  
	if(LEDsTimer.flagStatus() == PENDING)
	{
		LEDs.tick();
	
	}
	//**Process the panel and state machine***********//  
	if(panelUpdateTimer.flagStatus() == PENDING)
	{
		pUTLastTime = pUTStartTime;
		pUTStartTime = usTicks;
		//Provide inputs

		//Tick the machine
		p8hid.processMachine(30);
		
		//Deal with potential outputs here
		
		pUTStopTime = usTicks;
		int32_t length = pUTStopTime - pUTStartTime;
		if(length > pUTLength )
		{
			pUTLength = length;
		}
	}
	//**Debug timer*******************************//  
	if(debugTimer.flagStatus() == PENDING)
	{
		Serial.println("--Processor--");
		Serial.print("millis: ");
		Serial.println( millis() );
		Serial.print("usTicks: ");
		Serial.println( usTicks );
		Serial.print("AudioUsage:");
		//Serial.print(AudioProcessorUsage());
		//Serial.print(",");
		Serial.print((float)AudioProcessorUsageMax(), 2);
		AudioProcessorUsageMaxReset();
		Serial.print("    ");
		Serial.print("MemoryUsage: ");
		//Serial.print(AudioMemoryUsage());
		//Serial.print(",");
		Serial.print(AudioMemoryUsageMax());
		AudioMemoryUsageMaxReset();//reset
		Serial.print(",   FreeRam: ");
		Serial.print("FreeRam: ");
		Serial.print(FreeRam());
		Serial.println();
	
		Serial.println("--Process Measurements--");
		Serial.print("panelUpdateTimer (sTime, length): ");
		Serial.print(pUTStartTime - pUTLastTime);
		Serial.print(", ");
		Serial.println(pUTStopTime - pUTStartTime);
		Serial.print("pUTLength: ");
		Serial.println(pUTLength);
		pUTLength = 0;

		Serial.println();
	}
	
}

uint32_t FreeRam(){ // for Teensy 3.0
    uint32_t stackTop;
    uint32_t heapTop;

    // current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is the free, available ram.
    return stackTop - heapTop;
}


void serviceUS(void)
{
  uint32_t returnVar = 0;
  if(usTicks >= ( maxTimer + maxInterval ))
  {
	 if( usTicksMutex == 0 )
	 {
		 returnVar = usTicks - maxTimer;
	 }
	 else
	 {
		 returnVar = usTicks + 1;
	 }

  }
  else
  {
    returnVar = usTicks + 1;
  }
  usTicks = returnVar;
}