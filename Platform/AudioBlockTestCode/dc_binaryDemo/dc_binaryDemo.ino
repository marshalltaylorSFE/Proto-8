#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "synth_dc_binary.h"
//#include "wavegen.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=311,1634
AudioSynthWaveformSine   sine1;          //xy=503,1496
AudioSynthWaveformDcBinary dc_out_volume;  //xy=506,1649
AudioEffectMultiply      multiply1;      //xy=716,1622
AudioOutputAnalog        dac1;           //xy=733,1690
AudioOutputI2S           i2s1;           //xy=870,1579
AudioConnection          patchCord1(dc1, dc_out_volume);
AudioConnection          patchCord2(sine1, 0, multiply1, 0);
AudioConnection          patchCord3(dc_out_volume, 0, multiply1, 1);
AudioConnection          patchCord4(dc_out_volume, dac1);
AudioConnection          patchCord5(multiply1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=859,1520
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
int8_t toggle;

void setup() {
	//**** General Setup ****//
	Serial.begin(115200);
	delay(500);
	Serial.println("Sketch has started");
	delay(1500);

	//**** Timer Setup ****//
	next = millis() + 2000;

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
	dc_out_volume.amplitude_int(0);
	dc1.amplitude(0);

	//**** Gen Waveforms ****//
	sine1.frequency(440);

	AudioInterrupts();
			toggle = 0;
	
}

// getKnobInt16 gets a knob value as a full -2^15 to 2^15
int16_t getKnobInt16( uint16_t knob10bit )
{
	int32_t temp = (int32_t)knob10bit << 6;
	temp -= 0x8000;
	
	return (int16_t)temp;
}

// getKnobUint15 gets a knob value as a half, 0 to 2^15
int16_t getKnobUint15( uint16_t knob10bit )
{
	int32_t temp = (int32_t)knob10bit << 5;
	
	return (int16_t)temp;
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
		if( (lastKnob2Value >> 2) != (newKnob2Value >> 2) )
		{
			//Set the audio stream control input from 0 to 2^15
			lastKnob2Value = newKnob2Value;
			dc1.amplitude((float)getKnobUint15(lastKnob2Value)/32768); //set float value 0 to 1
		}
		if( (lastKnob3Value >> 2) != (newKnob3Value >> 2) )
		{
			//Set new target DC level, as -2^15 to 2^15
			lastKnob3Value = newKnob3Value;
			dc_out_volume.amplitude_int((uint16_t)lastKnob3Value << 6);
		}
		if( (lastKnob4Value >> 2) != (newKnob4Value >> 2) )
		{
			//Set an offset rate from -1 to 1
			lastKnob4Value = newKnob4Value;
			dc_out_volume.glideOffset(getKnobInt16(lastKnob4Value));
		}
		//if( (lastKnob5Value >> 2) != (newKnob5Value >> 2) )
		//{
		//	//Take action
		//	lastKnob5Value = newKnob5Value;
		//	dc1.amplitude(getKnobUint15(lastKnob5Value));
		//}
		
		//When enough regular 15ms loops have occured, send out debug data to the serial
		if( debugCounter > 50 )
		{
			debugCounter = 0;
			Serial.println("Debug:");
			Serial.println((int32_t)dc_out_volume.debugSave1, HEX);
			Serial.println((int32_t)dc_out_volume.debugSave2, HEX);
			dc_out_volume.debugFlag = 1;
			if( toggle == 0 )
			{
				toggle = 1;
			//	dc_out_volume.amplitude_int(0);
			}
			else
			{
				toggle = 0;
			//	dc_out_volume.amplitude_int(0xFFFF);
			}
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