#### /Proto-8/Projects
The project folder contains builds of individual synths and concepts that run on hardware not standard to the Teensy.

These are designed to run on Teensys with expanded IO (Proto-8).

**Requirements**

Libraries

* uCModules 2.0 
* Proto-8_Audio
* Proto-8_System

Also requires core_mods applied to AudioStream source and header files within \hardware\teensy\avr\cores\teensy3, for patchcord moving

**Contents**

* Classic2OSC -- A simple emulation of the pro-one.  This require the proto-8 libs and the big panel.
* ClassicTemplate -- The hardware layer with panel components matching to the locations of the "big panel".
* PatchCordChanger -- Swaps outputs between 4 waveforms
* PatchCordChangerTwo -- Swaps filter taps and chooses L/R output combinations
* README.md -- This file