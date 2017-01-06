// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
#include "TeensyView.h"  // Include the TeensyView library
#include "wavegen.h"
#include "synth_monoosc.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=268,274
AudioSynthWaveformDc     dc2;            //xy=268,319
AudioSynthWaveformDc     dc3;            //xy=270,365
AudioSynthMonoOsc        monoosc1;       //xy=538,319
AudioSynthMonoOsc        monoosc2;       //xy=540,390
AudioOutputAnalog        dac1;           //xy=751,385
AudioOutputI2S           i2s2;           //xy=764,349
AudioConnection          patchCord1(dc1, 0, monoosc1, 0);
AudioConnection          patchCord2(dc1, 0, monoosc2, 0);
AudioConnection          patchCord3(dc2, 0, monoosc1, 1);
AudioConnection          patchCord4(dc2, 0, monoosc2, 1);
AudioConnection          patchCord5(dc3, 0, monoosc1, 2);
AudioConnection          patchCord6(dc3, 0, monoosc2, 2);
AudioConnection          patchCord7(monoosc1, 0, i2s2, 0);
AudioConnection          patchCord8(monoosc1, dac1);
AudioConnection          patchCord9(monoosc2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=714,454
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

//Global waveforms:
WaveGenerator testWaveform;
int16_t * waveformPointer1;

char banner[20];


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
	sgtl5000_1.volume(1); //Force check first volume
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.unmuteHeadphone();
	sgtl5000_1.lineInLevel(1); //use 2 for 1:1
	sgtl5000_1.lineOutLevel(13);

	//Configure initial system here

	//configure waveform
	//setParameters(
	// uint8_t masterAmpVar,
	// uint8_t rampAmpVar,
	// uint8_t sineAmpVar,
	// uint8_t pulseAmpVar,
	// uint8_t pulseDutyVar )
	monoosc1.begin();
	monoosc2.begin();
	waveformPointer1 = monoosc1.getPointer( 0 );
	monoosc2.setPointer( 0, waveformPointer1 );
	
	testWaveform.setParameters( 128, 0, 127, 0, 0 );
	testWaveform.writeWaveU16_257( waveformPointer1 );

	dc1.amplitude(1.0);
	dc2.amplitude(0.2);
	dc3.amplitude(0.0);
	
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
	delay(900);
	oled.clear(PAGE);
	oled.display(); 
	sprintf(banner, ".");
	
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

void drawBanner()
{
	oled.setCursor(0,0);
	for( char * i = banner; *i != '\0' ; i++)
	{
		oled.print(" ");
		Serial.print("X");
		//Serial.print(*i, HEX);
	}
	oled.setCursor(0,0);
	for( char * i = banner; *i != '\0'; i++)
	{
		oled.print(*i);
		Serial.print(*i);
	}
}


void drawWaveform( int16_t * waveformPointer, uint8_t xOrigin )
{
	//Refresh the waveform globally
	testWaveform.writeWaveU16_257( waveformPointer1 );
	
	int32_t yTemp = 0;
	int16_t * sample = waveformPointer;
	for( int i = 0; i < 32; i++ )
	{
		//  Erase the column
		oled.line((xOrigin + i),0,(xOrigin + i),31,BLACK,0);
		//  Draw a sample
		yTemp = 15 - ((int32_t)*sample * 15) / 16383;
		//Serial.println(*sample, HEX);
		sample = sample + 8;
		
		oled.pixel(i + xOrigin, yTemp);
	}

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

		uint8_t drawScreen = 0;
		//Set audio platform parameters based on those values
		if( (lastKnob1Value > newKnob1Value + 10) || ((int16_t)lastKnob1Value < (int16_t)newKnob1Value - 10))
		{
			sprintf(banner, "Ramp: %4d\0", newKnob1Value >> 2);
			lastKnob1Value = newKnob1Value;
			drawScreen = 1;
		}
		if( (lastKnob2Value > newKnob2Value + 10) || ((int16_t)lastKnob2Value < (int16_t)newKnob2Value - 10))
		{
			lastKnob2Value = newKnob2Value;
			sprintf(banner, "Sine: %4d\0", newKnob2Value >> 2);
			drawScreen = 1;
		}
		if( (lastKnob3Value > newKnob3Value + 10) || ((int16_t)lastKnob3Value < (int16_t)newKnob3Value - 10))
		{
			lastKnob3Value = newKnob3Value;
			sprintf(banner, "Pulse: %4d\0", newKnob3Value >> 2);
			drawScreen = 1;
		}
		if( (newKnob4Value > lastKnob4Value + 10) || ((int16_t)newKnob4Value < (int16_t)lastKnob4Value - 10))
		{
			lastKnob4Value = newKnob4Value;
			sprintf(banner, "Master: %4d\0", newKnob4Value >> 2);
			drawScreen = 1;
		}
		if( (lastKnob5Value > newKnob5Value + 10) || ((int16_t)lastKnob5Value < (int16_t)newKnob5Value - 10))
		{
			lastKnob5Value = newKnob5Value;
			sprintf(banner, "Width: %4d\0", newKnob5Value >> 2);
			drawScreen = 1;
		}
		
		if( drawScreen == 1 )
		{
			testWaveform.setParameters( lastKnob4Value >> 2, lastKnob1Value >> 2, lastKnob2Value >> 2, lastKnob3Value >> 2, lastKnob5Value >> 2 );
			drawWaveform( waveformPointer1, 0 );
			drawWaveform( waveformPointer1, 32 );
			drawWaveform( waveformPointer1, 64 );
			drawWaveform( waveformPointer1, 96 );
			drawBanner();
			oled.display();

		}
		////Draw a graph
		////  Erase the column
		//oled.line(xCounter,0,xCounter,31,BLACK,0);
		////  Draw a new dot
		//float yPos = peak1.read();
		//yPos = 31 - (yPos * 31);
		//if(yPos < 0 )yPos = 0;
		//if(yPos > 31 )yPos = 31;
		//oled.pixel(xCounter,yPos);
		//oled.display();
		//xCounter++;
		//if( xCounter > 127 ) xCounter = 64;
		
		
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