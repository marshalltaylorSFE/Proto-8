#### /Proto-8/Projects
The project folder contains builds of individual synths and concepts that run on hardware not standard to the Teensy.

The additional hardware is for using the knobs, switches, and LEDs of the proto-8 circuit board.  Teensy Audio is compatible,
but these won't run on just a teensy and audio board.

**Contents:**

* BendvelopeExample -- Antiquated example for the bendvelope before library creation.  This project requires no libraries (except uCModules)
* CaseBringup -- The hardware layer with panel components matching to the locations of the "big panel".  This has been migrated to use with the proto-8 libs
* Classic2OSC -- A simple emulation of the pro-one.  This require the proto-8 libs and the big panel.
* MonoMultiOsc -- Antiquated example that contains some ideas I'm not ready to delete.
* Monster -- A failed attempt to implement full 4 voice on the big panel.  This eventually should run on the 3.6.
* MultiOscExample -- An early project working with the multiosc block.  This is stand alone and is out of date with the libraries.
* PatchCordChanger -- (successful) Experiment in swapping patch cords live.
* PCCBlock -- An experiment with creating a audio system block for manipulating patchcords.
* README.md -- This file