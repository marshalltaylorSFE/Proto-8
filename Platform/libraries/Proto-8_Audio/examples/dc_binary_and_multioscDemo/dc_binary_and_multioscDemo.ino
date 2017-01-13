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

#include "synth_dc_binary.h"
//#include "synth_multiosc.h"
#include "wavegen.h"

// GUItool: begin automatically generated code
AudioSynthWaveformDcBinary dc_amplitude;     //xy=269,1047
AudioSynthWaveformDcBinary dc_cent;     //xy=269,1157
AudioSynthWaveformDcBinary dc_3_12;     //xy=270,1104
AudioSynthWaveformDcBinary dc_out_volume;     //xy=270,1231
AudioSynthMultiOsc       multiosc1;      //xy=460,1127
AudioEffectMultiply      multiply1;      //xy=614,1250
AudioOutputI2S           i2s1;           //xy=768,1207
AudioConnection          patchCord1(dc_amplitude, 0, multiosc1, 0);
AudioConnection          patchCord2(dc_cent, 0, multiosc1, 5);
AudioConnection          patchCord3(dc_cent, 0, multiosc1, 6);
AudioConnection          patchCord4(dc_cent, 0, multiosc1, 7);
AudioConnection          patchCord5(dc_cent, 0, multiosc1, 8);
AudioConnection          patchCord6(dc_3_12, 0, multiosc1, 1);
AudioConnection          patchCord7(dc_3_12, 0, multiosc1, 2);
AudioConnection          patchCord8(dc_3_12, 0, multiosc1, 3);
AudioConnection          patchCord9(dc_3_12, 0, multiosc1, 4);
AudioConnection          patchCord10(dc_out_volume, 0, multiply1, 1);
AudioConnection          patchCord11(multiosc1, 0, multiply1, 0);
AudioConnection          patchCord12(multiply1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=757,1148
// GUItool: end automatically generated code

