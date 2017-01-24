// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
#include "TeensyView.h"  // Include the TeensyView library
#include "ADCKnob.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=644,1501
AudioSynthWaveformSine   sine2;          //xy=644,1541
AudioAnalyzePeak         peak1;          //xy=866,1486
AudioOutputAnalog        dac1;           //xy=868,1558
AudioOutputI2S           i2s2;           //xy=881,1522
AudioConnection          patchCord1(sine1, 0, i2s2, 0);
AudioConnection          patchCord2(sine1, peak1);
AudioConnection          patchCord3(sine2, 0, i2s2, 1);
AudioConnection          patchCord4(sine2, dac1);
AudioControlSGTL5000     sgtl5000_1;     //xy=831,1627
// GUItool: end automatically generated code



//////////////////////////////////
// TeensyView Object Declaration //
//////////////////////////////////
#define PIN_RESET 2 
#define PIN_DC    3 
#define PIN_CS    4 
#define PIN_SCK   14
#define PIN_MOSI  7 

TeensyView oled(PIN_RESET, PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI);

//Set knob names to analog input names here (use for remapping)
// Knobs go:
//  1   2   3
//  (OLED)
//  4   5

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

uint16_t debugCounter = 0;

uint8_t knob4OnlyMode = 0;
uint8_t requestClearScreenFlag = 0;
uint8_t screenClearedFlag = 0;
uint8_t requestKnob4ScreenFlag = 0;
uint8_t knob4ScreenFlag = 0;

//Used to prevent free run looping
uint32_t next;

void setup() {
	//**** General Setup ****//
	Serial.begin(115200);
	delay(1500);
	Serial.println("Sketch has started");

	//**** Knob Setup ****//
	knob1.init(KNOB1POS);
	knob2.init(KNOB2POS);
	knob3.init(KNOB3POS);
	knob4.init(KNOB4POS);
	knob5.init(KNOB5POS);
	//set params
	knob1.setLowerFloatVal(0);
	knob1.setUpperFloatVal(1.0);
	knob1.setLowerUIntVal(0);
	knob1.setUpperUIntVal(11);
	knob1.setHysteresis(10);
	knob1.setSamplesAveraged(10);
	
	knob2.setLowerUIntVal(1);
	knob2.setUpperUIntVal(128);
	knob2.setHysteresis(10);
	knob2.setSamplesAveraged(10);
	
	knob3.setLowerUIntVal(1);
	knob3.setUpperUIntVal(15);
	knob3.setHysteresis(10);
	knob3.setSamplesAveraged(10);
	
	knob4.setLowerUIntVal(0);
	knob4.setUpperUIntVal(1023);
	knob4.setLowerFloatVal(0);
	knob4.setUpperFloatVal(440);
	knob4.setHysteresis(10);
	knob4.setSamplesAveraged(10);
	
	knob5.setLowerUIntVal(0);
	knob5.setUpperUIntVal(1023);
	knob5.setLowerFloatVal(0);
	knob5.setUpperFloatVal(440);
	knob5.setHysteresis(10);
	knob5.setSamplesAveraged(10);
	//Run update a few times to fill the averaging buffers
	for(int i = 0; i < 10; i++) 
	{
		knob1.update();
		knob2.update();
		knob3.update();
		knob4.update();
		knob5.update();
	}

	//**** Timer Setup ****//
	next = millis() + 2000;

	//**** Audio Setup ****//
	AudioNoInterrupts();

	AudioMemory(35);

	sgtl5000_1.enable();
	sgtl5000_1.volume(0.8); //Force check first volume
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.unmuteHeadphone();
	sgtl5000_1.lineInLevel(1); //use 2 for 1:1
	sgtl5000_1.lineOutLevel(13);

	//Configure initial values here
	//sine1.frequency(440);
	//sine2.frequency(1760);

	sine1.amplitude(0.0);
	sine2.amplitude(0.0);
	
	AudioInterrupts();

	//Initialize the OLED
	oled.begin();
	oled.command(COMSCANINC); //Vertical flip
	oled.command(0xA0); //Horizontal flip
	// clear(ALL) will clear out the OLED's graphic memory.
	// clear(PAGE) will clear the Arduino's display buffer.
	oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
	// To actually draw anything on the display, you must call the
	// display() function. 
	oled.display(); 
	// Give the splash screen some time to shine
	delay(2000);
	oled.clear(PAGE);
	oled.display(); 
}

void loop() {
	//Do this at the interval defined above, don't just free run the loop
	if (millis() >= next)
	{
		next = millis() + 15;

		//Get the knob values
		knob1.update();
		knob2.update();
		knob3.update();
		knob4.update();
		knob5.update();

		//Set audio platform parameters based on those values
		uint8_t displayData = 0;
		if(knob1.newDataFlag())
		{
			if( knob4OnlyMode == 0 )
			{
				oled.setCursor(0,0);
				oled.print("             ");
				oled.setCursor(0,0);
				oled.print("Volume: ");
				oled.print((uint8_t)knob1.getAsUInt16());
				oled.display();
			}
			//Take action
			sine1.amplitude(knob1.getAsFloat());
			sine2.amplitude(knob1.getAsFloat());
			if(knob1.getAsUInt16() == 0)
			{
				knob4OnlyMode = 1;
				requestClearScreenFlag = 0;
				screenClearedFlag = 0;
				requestKnob4ScreenFlag = 1;
			}
			else
			{
				knob4OnlyMode = 0;
				requestClearScreenFlag = 1;
				requestKnob4ScreenFlag = 0;
				knob4ScreenFlag = 0;
			}
			displayData = 1;
		}
		if(knob2.newDataFlag())
		{
			if( knob4OnlyMode == 0 )
			{
				oled.setCursor(0,0);
				oled.print("             ");
				oled.setCursor(0,0);
				oled.print("Hyst.: ");
				oled.print(knob2.getAsUInt16());
				oled.display();
			}
			displayData = 2;
			knob4.setHysteresis(knob2.getAsUInt16());
			knob5.setHysteresis(knob2.getAsUInt16());
		}
		if(knob3.newDataFlag())
		{
			if( knob4OnlyMode == 0 )
			{
				oled.setCursor(0,0);
				oled.print("             ");
				oled.setCursor(0,0);
				oled.print("Ave'd: ");
				oled.print(knob3.getAsUInt16());
				oled.display();
			}
			displayData = 3;
			knob4.setSamplesAveraged(knob3.getAsUInt16());
			knob5.setSamplesAveraged(knob3.getAsUInt16());
		}
		if((knob4.newDataFlag())||((requestKnob4ScreenFlag == 1)&&(knob4ScreenFlag == 0)))
		{
			knob4ScreenFlag = 1;
			requestKnob4ScreenFlag = 0;
			
			if( knob4OnlyMode == 0 )
			{
				oled.setCursor(0,0);
				oled.print("             ");
				oled.setCursor(0,0);
				oled.print("L Hz: ");
				oled.print(knob4.getAsFloat() + 30);
				oled.display();
			}
			else
			{
				oled.setCursor(0,0);
				oled.print("                 ");
				oled.setCursor(0,0);
				oled.print("Knob 4 Only: ");
				oled.print(knob4.getAsUInt16());
				oled.setFontType(2);  // Set font to type 1
				oled.setCursor(4,10);
				uint16_t tempKnobValue = knob4.getAsUInt16();
				for( int i = 9; i >= 0; i--)
				{
					oled.print((tempKnobValue >> i) & 0x0001);
				}
				oled.display();
				oled.setFontType(0);  // Set font to type 0
			}
			displayData = 4;
			sine1.frequency(knob4.getAsFloat() + 30);
		}
		if(knob5.newDataFlag())
		{
			if( knob4OnlyMode == 0 )
			{
				oled.setCursor(0,0);
				oled.print("             ");
				oled.setCursor(0,0);
				oled.print("R Hz: ");
				oled.print(knob5.getAsFloat() + 30.25);
				oled.display();
			}
			displayData = 5;
			sine2.frequency(knob5.getAsFloat() + 30.25);
		}
		
		if((requestClearScreenFlag == 1)&&(screenClearedFlag == 0))
		{
			screenClearedFlag = 1;
			requestClearScreenFlag = 0;
			oled.clear(PAGE);
			oled.display();
		}
		
		//When enough regular 15ms loops have occured, send out debug data to the serial
		if( debugCounter > 50 )
		{
			debugCounter = 0;
			
			if(displayData == 1)
			{
				Serial.println("Knob 1 data:");
				Serial.println(knob1.getAsUInt8());
				Serial.println(knob1.getAsInt16());
				Serial.println(knob1.getAsUInt16());
				Serial.println(knob1.getAsFloat());
			}
			if(displayData == 2)
			{
				Serial.println("Knob 2 data:");
				Serial.println(knob2.getAsUInt8());
				Serial.println(knob2.getAsInt16());
				Serial.println(knob2.getAsUInt16());
				Serial.println(knob2.getAsFloat());
			}
			if(displayData == 3)
			{
				Serial.println("Knob 3 data:");
	
				Serial.println(knob3.getAsUInt8());
				Serial.println(knob3.getAsInt16());
				Serial.println(knob3.getAsUInt16());
				Serial.println(knob3.getAsFloat());
			}
			if(displayData == 4)
			{
				Serial.println("Knob 4 data:");
				Serial.println(knob4.getAsUInt8());
				Serial.println(knob4.getAsInt16());
				Serial.println(knob4.getAsUInt16());
				Serial.println(knob4.getAsFloat());
			}
			if(displayData == 5)
			{
				Serial.println("Knob 5 data:");
				Serial.println(knob5.getAsUInt8());
				Serial.println(knob5.getAsInt16());
				Serial.println(knob5.getAsUInt16());
				Serial.println(knob5.getAsFloat());
			}
			
			Serial.print("Processor: ");
			Serial.print((float)AudioProcessorUsageMax(), 2);
			AudioProcessorUsageMaxReset();
			Serial.print("    Memory: ");
			Serial.print(AudioMemoryUsageMax());
			AudioMemoryUsageMaxReset();//reset
			Serial.print("    FreeRam: ");
			Serial.print(FreeRam());
			
			
			Serial.println();
		}
		debugCounter++;
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