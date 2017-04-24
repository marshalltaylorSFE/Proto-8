Proto-8_Audio Library
========================================

This arduino library contains audio blocks that extend the capibilities of the Teensy audio platform.

Requirements:
-------------------

* Teensy 3.2
* Audio board
* 5 Knobs on analog inputs (0 to 3.3V)

Optionally, many examples require [SparkFun_TeensyView_Arduino_Library](https://github.com/sparkfun/SparkFun_TeensyView_Arduino_Library) to compile.  These will work even without a TeensyView present, as long as the library is available.

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
  * **dc_binary_glideDemo**
  * **TeensyView_lfo**
  * **TeensyView_monoosc**
  * **TeensyView_monoosc_glide**
  * **TeensyView_multiosc**
  * **TeensyView_template**
  * **template**
  * **waveGeneration_TeensyView**
* **/extras** - Additional documentation for the user. These files are ignored by the IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 
