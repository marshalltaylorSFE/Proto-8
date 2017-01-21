### Proto-8
#### *Hardware and software to extend the Teensy Audio system*
 ![alt text](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Images/Proto-8_in_fixture.jpg "Proto-8 Circuit in fixture")

*The Proto-8 hardware, shown in a test fixture*

------

#### Overview
 The Proto-8 system has two aspects: hardware that is compatible with the [Teensy Audio Board](https://www.pjrc.com/store/teensy3_audio.html) and associated Teensyduino libraries, and a software add-on package for the TeensyDuino libraries that adds specific functions.

**Hardware:**

* 2x SGTL5000 audio codecs for 4 in, 4 out.
* 8 unassigned 1/2 inch TRS connectors
* 64 knob inputs (analog multiplexed)
* 64 switch inputs (4x16 diode multiplexed)
* 64 LED outputs (shift registers to remove flicker)

![alt text](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Images/Proto-8_render.jpg "Render of Proto-8 Circuit")

*A KiCad render of the circuit board* 

**Software:**

* Hardware abstraction layer for running the knobs, switches, and leds
* New Teensy Audio blocks:
  * Oscillators with bit-per-octave (BPO) style control signals, mono and multi-voice
  * DC blocks with glide, suitable for BPO output
  * Bendvelope, a non-linear envelope
* Arbitrary wave generator of mixed sine, square, and pulse shapes
* AudioGUI modifications:
  * Blocks added in new shade
  * Requirement for output object removed
* Core audio files modified to allow live re- connection of patch cords.

![alt text](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Images/Audio_Blocks.jpg "Render of Proto-8 Circuit")

*New audio system blocks* 

#### Windows Installation
1. Obtain Arduino 1.6.12 from [arduino.cc](https://www.arduino.cc/en/Main/OldSoftwareReleases#previous) and install.  I recommend the zip file extracted to a non-system-integrated install.
3. Install [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html) and all libraries to the 1.6.12 installation.
2. Download [the Audio GUI](https://github.com/PaulStoffregen/Audio/tree/master/gui) and place in a directory of your computer.  Test that you can view "index.html" in a browser and that the system functions like [the online version](https://www.pjrc.com/teensy/gui/).
3. Replace the modified files from this repo into the local audio gui's folder (described in [Proto-8/Platform/GUI_mods/readme.md](https://github.com/marshalltaylorSFE/Proto-8/tree/master/Platform/GUI_mods)).  Refresh the index.html file in your browser and the new modules should appear in a pinker color.
4. Replace AudioStream.cpp and AudioStream.h in _Arduino_\hardware\teensy\avr\cores\teensy3 with those from [Proto-8/Platform/core_mods/](https://github.com/marshalltaylorSFE/Proto-8/tree/master/Platform/core_mods), where _Arduino_ is the path of the 1.6.12 installation.
5.  Install the following libraries to your arduino libraries directory:
  * [Proto-8/Platform/library/Proto-8_Audio](https://github.com/marshalltaylorSFE/Proto-8/tree/master/Platform/proto-8_library/Proto-8_Audio)
  * [uCModules](https://github.com/marshalltaylorSFE/uCModules)

