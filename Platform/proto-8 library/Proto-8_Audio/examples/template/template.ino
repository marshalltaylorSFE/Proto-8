// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=789,1171
AudioSynthWaveformSine   sine2;          //xy=789,1211
AudioOutputI2S           i2s2;           //xy=958,1213
AudioConnection          patchCord1(sine1, 0, i2s2, 0);
AudioConnection          patchCord2(sine2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=953,1158
// GUItool: end automatically generated code

//Set knob names to analog input names here (use for remapping)
// Knobs go:
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

		//Set audio platform parameters based on those values
		if( (lastKnob1Value >> 4) != (newKnob1Value >> 4) )
		{
			//Serial.println("New Knob Input");
			//Take action
			lastKnob1Value = newKnob1Value;
			sine1.amplitude((float)analogRead(KNOB1) / 1024);
			sine2.amplitude((float)analogRead(KNOB1) / 1024);
		}
		
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