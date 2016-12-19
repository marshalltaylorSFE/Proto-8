//The modulator subsystem
// GUItool: begin automatically generated code
AudioSynthWaveformDcBinary modGain;        //xy=397,1203
AudioEffectMultiply      modAmp;         //xy=538,1197
AudioSynthWaveformDcBinary modOffset;      //xy=545,1242
AudioMixer4              effectMixer;    //xy=711,1175
AudioConnection          patchCord1(modGain, 0, modAmp, 1);
AudioConnection          patchCord2(modAmp, 0, effectMixer, 2);
AudioConnection          patchCord3(modOffset, 0, effectMixer, 3);
// GUItool: end automatically generated code




//The main synthesizer
// GUItool: begin automatically generated code
AudioSynthBendvelope     bendvelope2;    //xy=593,713
AudioSynthBendvelope     bendvelope1;    //xy=596,651
AudioSynthWaveformDcBinary dc1CentD;       //xy=608,1037
AudioSynthWaveformDcBinary dc1CentA;       //xy=609,944
AudioSynthWaveformDcBinary dc1CentB;       //xy=609,975
AudioSynthWaveformDcBinary dc1CentC;       //xy=609,1006
AudioSynthWaveformDcBinary dc1A;           //xy=611,818
AudioSynthWaveformDcBinary dc1B;           //xy=613,851
AudioSynthWaveformDcBinary dc1C;           //xy=614,882
AudioSynthWaveformDcBinary dc1D;           //xy=614,912
AudioSynthWaveformDcBinary dc_binary1;     //xy=838,1174
AudioMixer4              mixer5;         //xy=856,1074
AudioSynthMultiOsc       multiosc1;      //xy=864,919
AudioFilterStateVariable filter1;        //xy=995,1103
AudioSynthWaveformDcBinary lfoPitch;       //xy=1061,782
AudioSynthWaveformDcBinary lfoAmp;         //xy=1081,731
AudioSynthWaveformDcBinary lfoCent;        //xy=1082,835
AudioFilterStateVariable filter2;        //xy=1148,1121
AudioSynthMonoOsc        lfo2;           //xy=1287,820
AudioSynthMonoOsc        lfo1;           //xy=1289,744
AudioOutputI2SQuad       is_quad23;      //xy=1327,1085
AudioConnection          patchCord1(bendvelope1, 0, multiosc1, 0);
AudioConnection          patchCord2(dc1CentD, 0, multiosc1, 8);
AudioConnection          patchCord3(dc1CentA, 0, multiosc1, 5);
AudioConnection          patchCord4(dc1CentB, 0, multiosc1, 6);
AudioConnection          patchCord5(dc1CentC, 0, multiosc1, 7);
AudioConnection          patchCord6(dc1A, 0, multiosc1, 1);
AudioConnection          patchCord7(dc1B, 0, multiosc1, 2);
AudioConnection          patchCord8(dc1C, 0, multiosc1, 3);
AudioConnection          patchCord9(dc1D, 0, multiosc1, 4);
AudioConnection          patchCord10(dc_binary1, 0, filter1, 1);
AudioConnection          patchCord11(dc_binary1, 0, filter2, 1);
AudioConnection          patchCord12(mixer5, 0, filter1, 0);
AudioConnection          patchCord13(multiosc1, 0, mixer5, 0);
AudioConnection          patchCord14(filter1, 0, filter2, 0);
AudioConnection          patchCord15(lfoPitch, 0, lfo1, 1);
AudioConnection          patchCord16(lfoPitch, 0, lfo2, 1);
AudioConnection          patchCord17(lfoAmp, 0, lfo1, 0);
AudioConnection          patchCord18(lfoAmp, 0, lfo2, 0);
AudioConnection          patchCord19(lfoCent, 0, lfo2, 2);
AudioConnection          patchCord20(lfoCent, 0, lfo1, 2);
AudioConnection          patchCord21(filter2, 0, is_quad23, 0);
AudioConnection          patchCord22(filter2, 0, is_quad23, 1);
AudioConnection          patchCord23(filter2, 0, is_quad23, 2);
AudioConnection          patchCord24(filter2, 0, is_quad23, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=1327,1183
AudioControlSGTL5000     sgtl5000_2;     //xy=1327,1225
// GUItool: end automatically generated code

