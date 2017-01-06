// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
#include "TeensyView.h"  // Include the TeensyView library

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
#define KNOB3 A3 //
#define KNOB2 A2 //
#define KNOB1 A1 //Main Parameter
#define KNOB4 A6 //
#define KNOB5 A7 //


uint16_t lastKnob1Value = 0;
uint16_t lastKnob2Value = 0;
uint16_t lastKnob3Value = 0;
uint16_t lastKnob4Value = 0;
uint16_t lastKnob5Value = 0;

uint16_t debugCounter = 0;

//Used to prevent free run looping
uint32_t next;

void setup() {
	//**** General Setup ****//
	Serial.begin(115200);
	delay(1500);
	Serial.println("Sketch has started");

	//**** Timer Setup ****//
	next = millis() + 2000;

	//**** Audio Setup ****//
	AudioNoInterrupts();

	AudioMemory(35);

	sgtl5000_1.enable();
	sgtl5000_1.volume(0.6); //Force check first volume
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.unmuteHeadphone();
	sgtl5000_1.lineInLevel(1); //use 2 for 1:1
	sgtl5000_1.lineOutLevel(13);

	//Configure initial system here
	sine1.frequency(440);
	sine2.frequency(1760);

	sine1.amplitude(0.0);
	sine2.amplitude(0.0);
	
	AudioInterrupts();

	//Initialize the OLED
	oled.begin();
	oled.command(COMSCANINC); //Flip display top-bottom
	oled.command(0xA0); //Flip display left-right
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

void showKnobValue( uint8_t knob, uint16_t value )
{
	oled.setCursor(0,0);
	oled.print("           ");
	oled.setCursor(0,0);
	oled.print("Knob");
	oled.print(knob);
	oled.print(": ");
	oled.print(value);
	oled.display();
}

uint8_t xCounter = 64;

void loop() {
	//Do this at the interval defined above, don't just free run the loop
	if (millis() >= next)
	{
		next = millis() + 15;

		//Get the knob values
		uint16_t newKnob1Value = analogRead(KNOB1);
		uint16_t newKnob2Value = analogRead(KNOB2);
		uint16_t newKnob3Value = analogRead(KNOB3);
		uint16_t newKnob4Value = analogRead(KNOB4);
		uint16_t newKnob5Value = analogRead(KNOB5);

		
		//Set audio platform parameters based on those values
		if( (lastKnob1Value > newKnob1Value + 5) || ((int16_t)lastKnob1Value < (int16_t)newKnob1Value - 5))
		{
			showKnobValue( 1, newKnob1Value );
			//Take action
			lastKnob1Value = newKnob1Value;
			sine1.amplitude((float)analogRead(KNOB1) / 1024);
			sine2.amplitude((float)analogRead(KNOB1) / 1024);
		}
		if( (lastKnob2Value > newKnob2Value + 5) || ((int16_t)lastKnob2Value < (int16_t)newKnob2Value - 5))
		{
			showKnobValue( 2, newKnob2Value );
			lastKnob2Value = newKnob2Value;
		}
		if( (lastKnob3Value > newKnob3Value + 5) || ((int16_t)lastKnob3Value < (int16_t)newKnob3Value - 5))
		{
			showKnobValue( 3, newKnob3Value );
			lastKnob3Value = newKnob3Value;
		}
		if( (newKnob4Value > lastKnob4Value + 5) || ((int16_t)newKnob4Value < (int16_t)lastKnob4Value - 5))
		{
			showKnobValue( 4, newKnob4Value );
			lastKnob4Value = newKnob4Value;
		}
		if( (lastKnob5Value > newKnob5Value + 5) || ((int16_t)lastKnob5Value < (int16_t)newKnob5Value - 5))
		{
			showKnobValue( 5, newKnob5Value );
			lastKnob5Value = newKnob5Value;
		}
		
		////Set audio platform parameters based on those values
		//if( (lastKnob1Value >> 4) != (newKnob1Value >> 4) )
		//{
		//	showKnobValue( 1, newKnob1Value );
		//	//Take action
		//	lastKnob1Value = newKnob1Value;
		//	sine1.amplitude((float)analogRead(KNOB1) / 1024);
		//	sine2.amplitude((float)analogRead(KNOB1) / 1024);
		//}
		//if( (lastKnob2Value >> 4) != (newKnob2Value >> 4) )
		//{
		//	showKnobValue( 2, newKnob2Value );
		//	lastKnob2Value = newKnob2Value;
		//}
		//if( (lastKnob3Value >> 4) != (newKnob3Value >> 4) )
		//{
		//	showKnobValue( 3, newKnob3Value );
		//	lastKnob3Value = newKnob3Value;
		//}
		//if( (lastKnob4Value >> 4) != (newKnob4Value >> 4) )
		//{
		//	showKnobValue( 4, newKnob4Value );
		//	lastKnob4Value = newKnob4Value;
		//}
		//if( (lastKnob5Value >> 4) != (newKnob5Value >> 4) )
		//{
		//	showKnobValue( 5, newKnob5Value );
		//	lastKnob5Value = newKnob5Value;
		//}
		
		//Draw a graph
		//  Erase the column
		oled.line(xCounter,0,xCounter,31,BLACK,0);
		//  Draw a new dot
		float yPos = peak1.read();
		yPos = 31 - (yPos * 31);
		if(yPos < 0 )yPos = 0;
		if(yPos > 31 )yPos = 31;
		oled.pixel(xCounter,yPos);
		oled.display();
		xCounter++;
		if( xCounter > 127 ) xCounter = 64;
		
		
		//When enough regular 15ms loops have occured, send out debug data to the serial
		if( debugCounter > 50 )
		{
			debugCounter = 0;
			
			Serial.println("Knob values: ");
			Serial.print("1: ");
			Serial.println(newKnob1Value);
			Serial.print("2: ");
			Serial.println(newKnob2Value);
			Serial.print("3: ");
			Serial.println(newKnob3Value);
			Serial.print("4: ");
			Serial.println(newKnob4Value);
			Serial.print("5: ");
			Serial.println(newKnob5Value);
			
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