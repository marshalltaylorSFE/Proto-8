##Modified Audio Gui
-------
This directory contains files to modify the teensy audio gui.
The files were obtained from: [https://github.com/PaulStoffregen/Audio](https://github.com/PaulStoffregen/Audio),
SHA: 60865a2e4aa191b420ad3eaa38309ea5e49902ed and
customized for use in the proto-8 synthesizer project.

Thanks to Paul for putting this together!  It is an awesome tool.

**Modified files:**
Replace the following files in the audio tool source.

\red\main.js -- Modified to allow export without RED.nodes.hasIO()
\index.html -- has new blocks added

**Blocks added:**

* dc_binary -- int16 and Q3.12 access to audio stream
* multiosc -- master amp and pitch/freq mod with 4 table based oscillators
* monoosc -- same but single osc
* bendvelope -- A envelope with variable rate parameters, dc output

Modified from original Node-Red source, for audio system visualization

**Legal:**

Copyright 2013 IBM Corp.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.