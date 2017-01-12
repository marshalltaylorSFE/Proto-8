### Proto-8
#### *Hardware and software to extend the Teensy Audio system*
 ![alt text](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Images/Proto-8_in_fixture.jpg "Proto-8 Circuit in fixture")

*The Proto-8 hardware, shown in a test fixture*

------

#### Overview
 The Proto-8 system has two aspects: hardware that is compatible with the [Teensy Audio Board](https://www.pjrc.com/store/teensy3_audio.html) and associated TeensyDuino libraries, and a software add-on package for the TeensyDuino libraries that adds specific functions.

**Hardware:**

* 2x SGTL5000 audio codecs for 4 in, 4 out.
* 8 unassigned 1/2 inch TRS connectors
* 64 knob inputs (analog multiplexed)
* 64 switch inputs (4x16 diode multiplexed)
* 64 LED outputs (shift registers based for low flicker)

![alt text](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Images/Proto-8_render.jpg "Render of Proto-8 Circuit")

*A KiCad Render of the circuit board* 

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
 
#### Windows Installation
1. Obtain Arduino 1.6.12 from [arduino.cc](https://www.arduino.cc/en/Main/OldSoftwareReleases#previous) and install.  I recommend the zip file extracted to a non-system-integrated install.
2. Download [the Audio GUI](https://github.com/PaulStoffregen/Audio/tree/master/gui) and place in a directory of your computer.  Test that you can view "index.html" in a browser and that the system functions like [the online version](https://www.pjrc.com/teensy/gui/).
3. Replace the modified files from this repo into the local audio gui's folder (described in [Proto-8/Platform/modified AudioGUI files/readme.md](https://github.com/marshalltaylorSFE/Proto-8/tree/master/Platform/modified%20AudioGUI%20files)).
4. Replace AudioStream.cpp and AudioStream.h in _Arduino_\hardware\teensy\avr\cores\teensy3 with those from [Proto-8/Platform/modified teensy core files/](https://github.com/marshalltaylorSFE/Proto-8/tree/master/Platform/modified%20teensy%20core%20files), where _Arduino_ is the path of the 1.6.12 installation.


