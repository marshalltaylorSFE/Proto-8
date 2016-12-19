##Modified Audio Gui
-------
This directory contains files to modify the teensy audio gui.
The files were obtained from: [https://github.com/PaulStoffregen/Audio](https://github.com/PaulStoffregen/Audio),
SHA: 60865a2e4aa191b420ad3eaa38309ea5e49902ed and
customized for use in the proto-8 synthesizer project.

Thanks to Paul for putting this together!  It is an awesome tool.

**Modified files:**
Replace the following files in the audio tool source.

* \red\main.js -- Modified to allow export without RED.nodes.hasIO()
* \index.html -- has new blocks added

**Blocks added:**

* dc_binary -- int16 and Q3.12 access to audio stream
* multiosc -- master amp and pitch/freq mod with 4 table based oscillators
* monoosc -- same but single osc
* bendvelope -- A envelope with variable rate parameters, dc output

Modified from original Node-Red source, for audio system visualization
Licensed under Apache within.
