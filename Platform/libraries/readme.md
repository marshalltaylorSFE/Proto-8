##Audio Block Test Code
-------

Contains two arduino style libraries, one for the Proto-8 hardware and the other for the audio system blocks.

**Proto-8_Audio library**

This library contains audio system compatible objects.

These run on a teensy 3.2 with audio board, and five knobs.  A [proto pedal with teensy](https://learn.sparkfun.com/tutorials/proto-pedal-example-programmable-digital-pedal) works well for the job.

Examples:

* bendvelopeDemo -- 
* dc_binary_and_multioscDemo -- 
* dc_binary_glideDemo -- 
* monooscDemo -- 
* monoosc_glideDemo -- 
* Proto-2_template -- Template for 5 knob pedal with TeensyView OLED screen
* template -- Template for 5 knob mono pedal (as in SparkFun guide)

**Proto-8_System library**

Examples:

* knobDemo -- Demonstrates the stand alone knob filter and scale object
* knobDemoTeensyView -- Demonstrates knobDemo with filter on knobs and TeensyView
* proto-8HardwareDemo -- Shows a demo using a panel (P8Panel / P8Interface), with serial output
* proto-8HardwareTest -- Walks through various IO testing of the Proto-8 circuit board