// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
//Knob 1: Pitch
//Knob 2: Glide rate
//Knob 3: Volume
//Knob 4: Mod depth
//Knob 5: Mod frequency

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "synth_dc_binary.h"
#include "synth_dc_binary_glide.h"
#include "synth_monoosc.h"
#include "wavegen.h"
#include "TeensyView.h"  // Include the TeensyView library


// Don't touch includes when using web gui

// GUItool: begin automatically generated code
AudioSynthWaveformDcBinaryGlide dc_glide_4_12;  //xy=184,225
AudioSynthWaveformSine   sine1;          //xy=255,375
AudioMixer4              mixer1;         //xy=415,316
AudioOutputAnalog        dac1;           //xy=419,146
AudioSynthWaveformDcBinary dc_amplitude;   //xy=579,237
AudioSynthWaveformDcBinary dc_cent;        //xy=579,347
AudioSynthWaveformDcBinary dc_out_volume;  //xy=580,421
AudioSynthMonoOsc        monoosc1;       //xy=792,277
AudioEffectMultiply      multiply1;      //xy=924,440
AudioOutputI2S           i2s1;           //xy=1078,397
AudioConnection          patchCord1(dc_glide_4_12, 0, mixer1, 0);
//AudioConnection          patchCord2(dc_glide_4_12, dac1);
  AudioConnection          patchCord2(multiply1, dac1);
AudioConnection          patchCord3(sine1, 0, mixer1, 1);
AudioConnection          patchCord4(mixer1, 0, monoosc1, 1);
AudioConnection          patchCord5(dc_amplitude, 0, monoosc1, 0);
AudioConnection          patchCord6(dc_cent, 0, monoosc1, 2);
AudioConnection          patchCord7(dc_out_volume, 0, multiply1, 1);
AudioConnection          patchCord8(monoosc1, 0, multiply1, 0);
AudioConnection          patchCord9(multiply1, 0, i2s1, 0);
AudioConnection          patchCord10(multiply1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1067,338
// GUItool: end automatically generated code


extern const float note2bpo[129];

//////////////////////////////////
// TeensyView Object Declaration //
//////////////////////////////////
#define PIN_RESET 2 
#define PIN_DC    3 
#define PIN_CS    4 
#define PIN_SCK   14
#define PIN_MOSI  7 

TeensyView oled(PIN_RESET, PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI);

uint16_t graphCounter = 0;
uint8_t displayedKnob = 0;
uint8_t xCounter = 64;

//Set knob names to analog input names here (use for remapping)
// Knobs pins are:
//  1   2   3
//    4   5
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
	delay(500);
	Serial.println("Sketch has started");
	delay(1500);

	//**** Timer Setup ****//
	next = millis() + 2000;

	//**** TeensyView Setup ****//
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

	//**** Audio Setup ****//
	AudioNoInterrupts();
	
	AudioMemory(100);

	sgtl5000_1.enable();
	sgtl5000_1.volume(1); //Force check first volume
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.unmuteHeadphone();
	sgtl5000_1.lineInLevel(1); //use 2 for 1:1
	sgtl5000_1.lineOutLevel(13);
	
	//Configure initial system here
	dc_amplitude.amplitude_int(1);
	dc_cent.amplitude_int(1);
	dc_glide_4_12.amplitude_int(1);
	//dc_glide_4_12.amplitude_4_12(note2bpo[24]);
	dc_out_volume.amplitude_int(0x8000);

	mixer1.gain(0,1);
	mixer1.gain(1,1);
	sine1.frequency(6);
	sine1.amplitude(0);
	
	//Start the OSC with default wave.
	monoosc1.amplitude( 0, 255 );
	monoosc1.begin();

	//**** Gen Waveforms ****//
	WaveGenerator testWave;
	testWave.setParameters( 255, 0, 255, 0, 45 );			
	testWave.writeWaveU16_257( monoosc1.getPointer( 0 ) );

	dac1.analogReference(EXTERNAL);
	
	AudioInterrupts();
	
}

void showKnobInfo( uint8_t knob, uint16_t value, uint16_t lastValue )
{
	oled.setCursor(0,0);
	oled.print("           ");
	oled.setCursor(0,0);
	oled.print("Knob");
	oled.print(knob);
	oled.print(": ");
	oled.print(value);
	oled.setCursor(0,8);
	oled.print("           ");
	oled.setCursor(0,8);
	oled.print("Last");
	oled.print(knob);
	oled.print(": ");
	oled.print(lastValue);
	oled.display();
}

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

		//Check for large change for display purposes
		if( ((lastKnob1Value >> 5) != (newKnob1Value >> 5)) || (displayedKnob == 1) )
		{
			displayedKnob = 1;
			showKnobInfo( displayedKnob, newKnob1Value, lastKnob1Value );
		}			
		if( ((lastKnob2Value >> 5) != (newKnob2Value >> 5)) || (displayedKnob == 2) )
		{
			displayedKnob = 2;
			showKnobInfo( displayedKnob, lastKnob2Value, lastKnob2Value );
		}			
		if( ((lastKnob3Value >> 5) != (newKnob3Value >> 5)) || (displayedKnob == 3) )
		{
			displayedKnob = 3;
			showKnobInfo( displayedKnob, lastKnob3Value, lastKnob3Value );
		}			
		if( ((lastKnob4Value >> 5) != (newKnob4Value >> 5)) || (displayedKnob == 4) )
		{
			displayedKnob = 4;
			showKnobInfo( displayedKnob, lastKnob4Value, lastKnob4Value );
		}			
		if( ((lastKnob5Value >> 5) != (newKnob5Value >> 5)) || (displayedKnob == 5) )
		{
			displayedKnob = 5;
			showKnobInfo( displayedKnob, lastKnob5Value, lastKnob5Value );
		}
		
		//Knob 1: Pitch
		if( (newKnob1Value > lastKnob1Value + 8) || ((int16_t)newKnob4Value < (int16_t)lastKnob1Value - 8))
		{
			lastKnob1Value = newKnob1Value;
			//if( newKnob1Value < 512 )
			//{
			//	float tempbpo = note2bpo[(uint32_t)newKnob1Value * 127 / 512];
			//	//Serial.println(tempbpo, HEX);
			//	dc_glide_4_12.amplitude_4_12(tempbpo); //add for dc tune
			//}
			//else
			//{
			//	dc_glide_4_12.amplitude_int((int16_t)(newKnob1Value - 512) << 6);
			//}
			//float tempbpo = note2bpo[36 + (uint32_t)newKnob1Value * 24 / 1024]; //24 is full range, starting at octave 3
			float tempbpo = note2bpo[(uint32_t)newKnob1Value * 129 / 1024]; //129 is full range
			//Serial.println(tempbpo, HEX);
			dc_glide_4_12.amplitude_4_12(tempbpo); //add for dc tune
			
		}
		//Knob 2: Glide rate
		if( (lastKnob2Value >> 4) != (newKnob2Value >> 4) )
		{
			lastKnob2Value = newKnob2Value;
			//dc_cent.amplitude_int(((int32_t)newKnob2Value<<6) - 0x7FFF); //This sets cent bend level
			dc_glide_4_12.glideOffset((int16_t)newKnob2Value<<5);
		}
		//Set audio platform parameters based on those values
		//Knob 3: Volume
		if( (lastKnob3Value >> 2) != (newKnob3Value >> 2) )
		{
			lastKnob3Value = newKnob3Value;
			dc_amplitude.amplitude_int((int16_t)newKnob3Value<<5);
		}
		//Knob 4: Mod depth
		if( (lastKnob4Value >> 2) != (newKnob4Value >> 2) )
		{
			lastKnob4Value = newKnob4Value;
			sine1.amplitude(float((int32_t)newKnob4Value<<3) / 0x8000);
		}
		//Knob 5: Mod frequency
		if( (lastKnob5Value >> 2) != (newKnob5Value >> 2) )
		{
			lastKnob5Value = newKnob5Value;
			sine1.frequency(20* float(newKnob5Value) / 256);
		}
		//Draw a graph every 3 times
		if( graphCounter > 3 )
		{
			graphCounter = 0;
			//  Erase the column
			oled.line(xCounter,0,xCounter,32,BLACK,0);
			//  Draw a new dot
			int32_t yPos = (dc_glide_4_12.accumulator >> 12);
			yPos *= 32;
			yPos /= 47000;
			yPos = 31 - yPos;
			if(yPos < 0 )yPos = 0;
			if(yPos > 31 )yPos = 31;
			oled.pixel(xCounter,yPos);
			oled.display();
			xCounter++;
			if( xCounter > 127 ) xCounter = 64;
		}
		graphCounter++;
		
		//When enough regular 15ms loops have occured, send out debug data to the serial
		if( debugCounter > 50 )
		{
			debugCounter = 0;
			Serial.println((int32_t)(monoosc1.debugSave >> 32), HEX);
			Serial.println((int32_t)monoosc1.debugSave, HEX);
			monoosc1.debugFlag = 1;
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