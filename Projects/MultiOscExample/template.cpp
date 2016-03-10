#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=506.888916015625,291.8888854980469
AudioSynthWaveform       waveform2;      //xy=511.8889465332031,372.8888854980469
AudioSynthWaveform       waveform3;      //xy=517.888916015625,449.8888854980469
AudioSynthWaveform       waveform4;      //xy=522.888916015625,533.8889465332031
AudioSynthWaveformSineModulated sine_fm1;       //xy=653.8889465332031,291.888916015625
AudioSynthWaveformSineModulated sine_fm2;       //xy=661.8889465332031,371.8888854980469
AudioSynthWaveformSineModulated sine_fm3;       //xy=668.8889465332031,453.8888854980469
AudioSynthWaveformSineModulated sine_fm4;       //xy=680.8889465332031,537.8889465332031
AudioMixer4              mixer5;         //xy=987.8888854980469,413
AudioFilterStateVariable filter1;        //xy=1143.8888854980469,421
AudioFilterStateVariable filter3;        //xy=1279.8888854980469,422
AudioOutputI2SQuad       i2s_quad2;      //xy=1469.8888854980469,431
AudioConnection          patchCord1(waveform1, sine_fm1);
AudioConnection          patchCord2(waveform2, sine_fm2);
AudioConnection          patchCord3(waveform3, sine_fm3);
AudioConnection          patchCord4(waveform4, sine_fm4);
AudioConnection          patchCord5(sine_fm1, 0, mixer5, 0);
AudioConnection          patchCord6(sine_fm2, 0, mixer5, 1);
AudioConnection          patchCord7(sine_fm3, 0, mixer5, 2);
AudioConnection          patchCord8(sine_fm4, 0, mixer5, 3);
AudioConnection          patchCord9(mixer5, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 0, filter3, 0);
AudioConnection          patchCord11(filter3, 0, i2s_quad2, 0);
AudioConnection          patchCord12(filter3, 0, i2s_quad2, 1);
AudioConnection          patchCord13(filter3, 0, i2s_quad2, 2);
AudioConnection          patchCord14(filter3, 0, i2s_quad2, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
// GUItool: end automatically generated code

