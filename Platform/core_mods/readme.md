## Audio Core Modifications


These files need to be placed in \___Arduino___\hardware\teensy\avr\cores\teensy3

* 7/9/2016 -- files are a crude example that patchcords can be moved live.
* 7/9/2016 -- Use with \Proto-8\Projects\PatchCordChanger
* 12/12/2016 -- Heavy overhaul.  Seems stable now.  Also added unconnected patchcord constructor
* 12/12/2016 -- PCCBlock made to demo chages on the moster panel
* 2/5/2015 -- Updated files for TeensyDuino [version 1.35](https://www.pjrc.com/teensy/td_135/TeensyduinoInstall.exe)
  * (Older version was probably using [version 1.31](https://www.pjrc.com/teensy/td_131/TeensyduinoInstall.exe))

  ![demo diagram](https://raw.githubusercontent.com/marshalltaylorSFE/Proto-8/master/Projects/PCCBlock/AudioToolDiagram.jpg)

*The latest example changes taps between the filter outputs, and the quad output.*