// MIDI things
#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
	Serial.print("Note On :");
	Serial.print("0x");
	Serial.print(channel, HEX);
	Serial.print(" 0x");
	Serial.print(pitch, HEX);
	Serial.print(" 0x");
	Serial.print(velocity, HEX);
	Serial.print("\n");
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
	Serial.print("Note Off:");
	Serial.print("0x");
	Serial.print(channel, HEX);
	Serial.print(" 0x");
	Serial.print(pitch, HEX);
	Serial.print(" 0x");
	Serial.print(velocity, HEX);
	Serial.print("\n");
}

void handlePitchBend(byte channel, int bend)
{
	Serial.print("Pitch   :");
	Serial.print("0x");
	Serial.print(channel, HEX);
	Serial.print(" int:");
	Serial.print(bend);
	Serial.print("\n");
	}

void handleControlChange(byte channel, byte pitch, byte value)
{
	Serial.print("Ctrl    :");
	Serial.print("0x");
	Serial.print(channel, HEX);
	Serial.print(" 0x");
	Serial.print(pitch, HEX);
	Serial.print(" 0x");
	Serial.print(value, HEX);
	Serial.print("\n");
}

void setup()
{
	pinMode(11, OUTPUT);
//	Serial.begin(57600);
	Serial.begin(57600);
	midiA.turnThruOn();
	midiA.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
	midiA.setHandleNoteOff(handleNoteOff);
	midiA.setHandlePitchBend(handlePitchBend);
	midiA.setHandleControlChange(handleControlChange);
	
	// Initiate MIDI communications, listen to all channels
	midiA.begin(MIDI_CHANNEL_OMNI);
	Serial.println("Starting program");
}

void loop()
{
    midiA.read();
}