#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>




// GUItool: begin automatically generated code
AudioSynthBendvelope     bendvelope1;      //xy=506.888916015625,291.8888854980469
AudioSynthBendvelope     bendvelope2;      //xy=511.8889465332031,372.8888854980469
AudioSynthBendvelope     bendvelope3;      //xy=517.888916015625,449.8888854980469
AudioSynthBendvelope     bendvelope4;      //xy=522.888916015625,533.8889465332031
AudioSynthMultiOsc       multiosc1;       //xy=653.8889465332031,291.888916015625
AudioSynthMultiOsc       multiosc2;       //xy=661.8889465332031,371.8888854980469
AudioSynthMultiOsc       multiosc3;       //xy=668.8889465332031,453.8888854980469
AudioSynthMultiOsc       multiosc4;       //xy=680.8889465332031,537.8889465332031
AudioMixer4              mixer5;         //xy=987.8888854980469,413
AudioFilterStateVariable filter1;        //xy=1143.8888854980469,421
AudioFilterStateVariable filter3;        //xy=1279.8888854980469,422
AudioOutputI2SQuad       i2s_quad2;      //xy=1469.8888854980469,431
AudioConnection          patchCord1(bendvelope1, multiosc1);
AudioConnection          patchCord2(bendvelope2, multiosc2);
AudioConnection          patchCord3(bendvelope3, multiosc3);
AudioConnection          patchCord4(bendvelope4, multiosc4);
AudioConnection          patchCord5(multiosc1, 0, mixer5, 0);
AudioConnection          patchCord6(multiosc2, 0, mixer5, 1);
AudioConnection          patchCord7(multiosc3, 0, mixer5, 2);
AudioConnection          patchCord8(multiosc4, 0, mixer5, 3);
AudioConnection          patchCord9(mixer5, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 0, filter3, 0);
AudioConnection          patchCord11(filter3, 0, i2s_quad2, 0);
AudioConnection          patchCord12(filter3, 0, i2s_quad2, 1);
AudioConnection          patchCord13(filter3, 0, i2s_quad2, 2);
AudioConnection          patchCord14(filter3, 0, i2s_quad2, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
// GUItool: end automatically generated code


// GUItool: begin automatically generated code
AudioSynthMultiOsc       multiosc1;       //xy=518.8889465332031,294.8888854980469
AudioSynthMultiOsc       multiosc2;       //xy=520.8889465332031,372.8888854980469
AudioSynthMultiOsc       multiosc3;       //xy=528.8889465332031,534.8889465332031
AudioSynthMultiOsc       multiosc4;       //xy=529.8889465332031,454.888916015625
AudioSynthBendvelope     bendvelope1;          //xy=558.8889465332031,331.888916015625
AudioSynthBendvelope     bendvelope2;          //xy=586.8888854980469,411.8888854980469
AudioSynthBendvelope     bendvelope3;          //xy=594.8888854980469,499.8888854980469
AudioSynthBendvelope     bendvelope4;          //xy=608.8888854980469,586.8888854980469
AudioEffectMultiply      multiply1;      //xy=718.8889465332031,329.888916015625
AudioEffectMultiply      multiply2;      //xy=751.8889465332031,404.8888854980469
AudioEffectMultiply      multiply3;      //xy=754.8889465332031,469.8888854980469
AudioEffectMultiply      multiply4;      //xy=775.8889465332031,542.8889465332031
AudioMixer4              mixer5;         //xy=987.8888854980469,413
AudioFilterStateVariable filter1;        //xy=1143.8888854980469,421
AudioFilterStateVariable filter3;        //xy=1279.8888854980469,422
AudioOutputI2SQuad       i2s_quad2;      //xy=1469.8888854980469,431
AudioConnection          patchCord1(multiosc1, 0, multiply1, 0);
AudioConnection          patchCord2(multiosc2, 0, multiply2, 0);
AudioConnection          patchCord3(multiosc4, 0, multiply4, 0);
AudioConnection          patchCord4(multiosc3, 0, multiply3, 0);
AudioConnection          patchCord5(bendvelope1, 0, multiply1, 1);
AudioConnection          patchCord6(bendvelope2, 0, multiply2, 1);
AudioConnection          patchCord7(bendvelope3, 0, multiply3, 1);
AudioConnection          patchCord8(bendvelope4, 0, multiply4, 1);
AudioConnection          patchCord9(multiply1, 0, mixer5, 0);
AudioConnection          patchCord10(multiply2, 0, mixer5, 1);
AudioConnection          patchCord11(multiply3, 0, mixer5, 2);
AudioConnection          patchCord12(multiply4, 0, mixer5, 3);
AudioConnection          patchCord13(mixer5, 0, filter1, 0);
AudioConnection          patchCord14(filter1, 0, filter3, 0);
AudioConnection          patchCord15(filter3, 0, i2s_quad2, 0);
AudioConnection          patchCord16(filter3, 0, i2s_quad2, 1);
AudioConnection          patchCord17(filter3, 0, i2s_quad2, 2);
AudioConnection          patchCord18(filter3, 0, i2s_quad2, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
// GUItool: end automatically generated code



// GUItool: begin automatically generated code
AudioSynthMultiOsc       MultiOsc1;      //xy=619.8889465332031,353.8888854980469
AudioSynthMultiOsc       MultiOsc2;      //xy=628.8889465332031,391.8888854980469
AudioSynthMultiOsc       MultiOsc3;      //xy=634.8889465332031,432.888916015625
AudioSynthMultiOsc       MultiOsc4;      //xy=640.888916015625,472.888916015625
AudioEffectBendvelope    bendvelope1;    //xy=772.8889465332031,353
AudioEffectBendvelope    bendvelope2;    //xy=782.8889465332031,391
AudioEffectBendvelope    bendvelope3;    //xy=788.8889465332031,432
AudioEffectBendvelope    bendvelope4;    //xy=794.8889465332031,472
AudioMixer4              mixer5;         //xy=987.8888854980469,413
AudioFilterStateVariable filter1;        //xy=1143.8888854980469,421
AudioFilterStateVariable filter3;        //xy=1279.8888854980469,422
AudioOutputI2SQuad       i2s_quad2;      //xy=1469.8888854980469,431
AudioConnection          patchCord1(MultiOsc1, bendvelope1);
AudioConnection          patchCord2(MultiOsc2, bendvelope2);
AudioConnection          patchCord3(MultiOsc3, bendvelope3);
AudioConnection          patchCord4(MultiOsc4, bendvelope4);
AudioConnection          patchCord5(bendvelope1, 0, mixer5, 0);
AudioConnection          patchCord6(bendvelope2, 0, mixer5, 1);
AudioConnection          patchCord7(bendvelope3, 0, mixer5, 2);
AudioConnection          patchCord8(bendvelope4, 0, mixer5, 3);
AudioConnection          patchCord9(mixer5, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 0, filter3, 0);
AudioConnection          patchCord11(filter3, 0, i2s_quad2, 0);
AudioConnection          patchCord12(filter3, 0, i2s_quad2, 1);
AudioConnection          patchCord13(filter3, 0, i2s_quad2, 2);
AudioConnection          patchCord14(filter3, 0, i2s_quad2, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
// GUItool: end automatically generated code
