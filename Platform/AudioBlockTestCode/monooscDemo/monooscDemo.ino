#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "synth_dc_binary.h"
#include "synth_monoosc.h"
#include "wavegen.h"


// Don't touch includes when using web gui

//// GUItool: begin automatically generated code
//AudioSynthWaveformDcBinary dc_amplitude;   //xy=463,1011
//AudioSynthWaveformDcBinary dc_cent;        //xy=463,1121
//AudioSynthWaveformDcBinary dc_3_12;        //xy=464,1068
//AudioSynthWaveformDcBinary dc_out_volume;  //xy=464,1195
//AudioSynthMonoOsc        monoosc1;       //xy=676,1051
//AudioEffectMultiply      multiply1;      //xy=808,1214
//AudioOutputI2S           i2s1;           //xy=962,1171
//AudioOutputAnalog        dac1;           //xy=965,1254
//AudioConnection          patchCord1(dc_amplitude, 0, monoosc1, 0);
//AudioConnection          patchCord2(dc_cent, 0, monoosc1, 2);
//AudioConnection          patchCord3(dc_3_12, 0, monoosc1, 1);
//AudioConnection          patchCord4(dc_out_volume, 0, multiply1, 1);
//AudioConnection          patchCord5(monoosc1, 0, multiply1, 0);
//AudioConnection          patchCord6(multiply1, 0, i2s1, 0);
//AudioConnection          patchCord7(multiply1, dac1);
//AudioControlSGTL5000     sgtl5000_1;     //xy=951,1112
//// GUItool: end automatically generated code

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=87,1428
AudioSynthWaveformDcBinary dc_3_12;        //xy=97,1355
AudioMixer4              mixer1;         //xy=247,1369
AudioSynthWaveformDcBinary dc_amplitude;   //xy=411,1290
AudioSynthWaveformDcBinary dc_cent;        //xy=411,1400
AudioSynthWaveformDcBinary dc_out_volume;  //xy=412,1474
AudioSynthMonoOsc        monoosc1;       //xy=624,1330
AudioEffectMultiply      multiply1;      //xy=756,1493
AudioOutputI2S           i2s1;           //xy=910,1450
AudioOutputAnalog        dac1;           //xy=913,1533
AudioConnection          patchCord1(sine1, 0, mixer1, 1);
AudioConnection          patchCord2(dc_3_12, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, 0, monoosc1, 1);
AudioConnection          patchCord4(dc_amplitude, 0, monoosc1, 0);
AudioConnection          patchCord5(dc_cent, 0, monoosc1, 2);
AudioConnection          patchCord6(dc_out_volume, 0, multiply1, 1);
AudioConnection          patchCord7(monoosc1, 0, multiply1, 0);
AudioConnection          patchCord8(multiply1, 0, i2s1, 0);
AudioConnection          patchCord9(multiply1, dac1);
AudioControlSGTL5000     sgtl5000_1;     //xy=899,1391
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
	dc_amplitude.amplitude_int(1);
	dc_cent.amplitude_int(1);
	dc_3_12.amplitude_int(1);
	//dc_3_12.amplitude_3_12(note2bpo[24]);
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
		if( (lastKnob1Value >> 2) != (newKnob1Value >> 2) )
		{
			//Serial.println("New Knob Input");
			//Take action
			lastKnob1Value = newKnob1Value;
			dc_amplitude.amplitude_int((int16_t)newKnob1Value<<5);
		}
		if( (lastKnob2Value >> 2) != (newKnob2Value >> 2) )
		{
			//Take action
			lastKnob2Value = newKnob2Value;
			sine1.amplitude(float((int32_t)newKnob2Value<<3) / 0x8000);
		}
		if( (lastKnob3Value >> 2) != (newKnob3Value >> 2) )
		{
			//Take action
			lastKnob3Value = newKnob3Value;
			sine1.frequency(20* float(newKnob3Value) / 256);
		}
		if( (lastKnob4Value ) != (newKnob4Value ) )
		{
			//Serial.println("New Knob Input");
			//Take action
			lastKnob4Value = newKnob4Value;
			//if( newKnob4Value < 512 )
			//{
			//	float tempbpo = note2bpo[(uint32_t)newKnob4Value * 127 / 512];
			//	//Serial.println(tempbpo, HEX);
			//	dc_3_12.amplitude_3_12(tempbpo); //add for dc tune
			//}
			//else
			//{
			//	dc_3_12.amplitude_int((int16_t)(newKnob4Value - 512) << 6);
			//}
			//float tempbpo = note2bpo[36 + (uint32_t)newKnob4Value * 24 / 1024]; //24 is full range, starting at octave 3
			float tempbpo = note2bpo[(uint32_t)newKnob4Value * 129 / 1024]; //129 is full range
			//Serial.println(tempbpo, HEX);
			dc_3_12.amplitude_3_12(tempbpo); //add for dc tune
			
		}
		if( (lastKnob5Value) != (newKnob5Value) )
		{
			//Serial.println("New Knob Input");
			//Take action
			lastKnob5Value = newKnob5Value;
			dc_cent.amplitude_int(((int32_t)newKnob5Value<<6) - 0x7FFF);
		}
		
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