//**********************************************************************//
//
//  A synth that consists of 3 oscillators, 2 envelopes, and a selection
//  of modulation paths
//
//  MIT License: http://opensource.org/licenses/MIT
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2017/05/01: Created
//
//**********************************************************************//
#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"
#include "synth_bendvelope.h"
#include "synth_monoosc.h"
#include "synth_dc_binary.h"
#include "synth_dc_binary_glide.h"
#include "P8Interface.h"
//#include "MicroLLTemplate.h"

//// GUItool: begin automatically generated code
//AudioSynthWaveformDcBinary dc_one;     //xy=190.75,700.75
//AudioSynthWaveformDcBinary dc_zero;        //xy=199.75,414
//AudioEffectEnvelope      envelope1;      //xy=346.75,708
//AudioSynthWaveformSine   lfo1;           //xy=354.75,657
//AudioSynthWaveformDcBinary dc1PitchB;     //xy=374.75,461.75
//AudioSynthWaveformDcBinary dc1CentB;       //xy=377.75,508
//AudioSynthWaveformDcBinary dc1PitchA;     //xy=384.75,369.75
//AudioSynthWaveformDcBinary dc1PitchC;     //xy=403.75,556.75
//AudioSynthBendvelope     bendvelope1;    //xy=427.75,319
//AudioSynthWaveformDcBinary dc1CentC;       //xy=429.75,607
//AudioSynthMonoOsc        monoosc3;       //xy=629.75,561
//AudioSynthMonoOsc        monoosc2;       //xy=633.75,487
//AudioSynthMonoOsc        monoosc1;       //xy=635.75,412
//AudioSynthWaveformDcBinary dc_filter;      //xy=789.75,599
//AudioMixer4              mixer5;         //xy=827.75,475
//AudioFilterStateVariable filter1;        //xy=973.75,485
//AudioOutputI2SQuad       is_quad23;      //xy=1200.75,495
//AudioSynthWaveformDcBinary modGain;        //xy=1343.75,589
//AudioEffectMultiply      modAmp;         //xy=1484.75,583
//AudioSynthWaveformDcBinary modOffset;      //xy=1491.75,628
//AudioMixer4              effectMixer;    //xy=1657.75,561
//AudioConnection          patchCord1(dc_one, envelope1);
//AudioConnection          patchCord2(dc_zero, 0, monoosc1, 2);
//AudioConnection          patchCord3(dc1PitchB, 0, monoosc2, 1);
//AudioConnection          patchCord4(dc1CentB, 0, monoosc2, 2);
//AudioConnection          patchCord5(dc1PitchA, 0, monoosc1, 1);
//AudioConnection          patchCord6(dc1PitchC, 0, monoosc3, 1);
//AudioConnection          patchCord7(bendvelope1, 0, monoosc1, 0);
//AudioConnection          patchCord8(bendvelope1, 0, monoosc2, 0);
//AudioConnection          patchCord9(bendvelope1, 0, monoosc3, 0);
//AudioConnection          patchCord10(dc1CentC, 0, monoosc3, 2);
//AudioConnection          patchCord11(monoosc3, 0, mixer5, 2);
//AudioConnection          patchCord12(monoosc2, 0, mixer5, 1);
//AudioConnection          patchCord13(monoosc1, 0, mixer5, 0);
//AudioConnection          patchCord14(dc_filter, 0, filter1, 1);
//AudioConnection          patchCord15(mixer5, 0, filter1, 0);
//AudioConnection          patchCord16(filter1, 0, is_quad23, 0);
//AudioConnection          patchCord17(filter1, 0, is_quad23, 1);
//AudioConnection          patchCord18(filter1, 0, is_quad23, 2);
//AudioConnection          patchCord19(filter1, 0, is_quad23, 3);
//AudioConnection          patchCord20(modGain, 0, modAmp, 1);
//AudioConnection          patchCord21(modAmp, 0, effectMixer, 2);
//AudioConnection          patchCord22(modOffset, 0, effectMixer, 3);
//AudioControlSGTL5000     sgtl5000_1;     //xy=1163.75,390
//AudioControlSGTL5000     sgtl5000_2;     //xy=1167.75,346
//// GUItool: end automatically generated code

// GUItool: begin automatically generated code
AudioSynthWaveformDcBinary dc_one;     //xy=190.75,700.75
AudioSynthWaveformDcBinary dc_zero;        //xy=199.75,414
AudioEffectEnvelope      envelope1;      //xy=346.75,708
AudioSynthWaveformSine   lfo1;           //xy=354.75,657
AudioSynthWaveformDcBinary dc1PitchB;     //xy=374.75,461.75
AudioSynthWaveformDcBinary dc1CentB;       //xy=377.75,508
AudioSynthWaveformDcBinary dc1PitchA;     //xy=384.75,369.75
AudioSynthWaveformDcBinary dc1PitchC;     //xy=403.75,556.75
AudioSynthBendvelope     bendvelope1;    //xy=427.75,319
AudioSynthWaveformDcBinary dc1CentC;       //xy=429.75,607
AudioSynthMonoOsc        monoosc3;       //xy=629.75,561
AudioSynthMonoOsc        monoosc2;       //xy=633.75,487
AudioSynthMonoOsc        monoosc1;       //xy=635.75,412
AudioSynthWaveformDcBinary dc_filter;      //xy=789.75,599
AudioMixer4              mixer5;         //xy=827.75,475
AudioFilterStateVariable filter1;        //xy=973.75,485
AudioOutputI2SQuad       is_quad23;      //xy=1200.75,495
AudioSynthWaveformDcBinary modGain;        //xy=1343.75,589
AudioEffectMultiply      modAmp;         //xy=1484.75,583
AudioSynthWaveformDcBinary modOffset;      //xy=1491.75,628
AudioMixer4              effectMixer;    //xy=1657.75,561
AudioConnection          patchCord1(dc_one, envelope1);
AudioConnection          patchCord2(dc_zero, 0, monoosc1, 2);
AudioConnection          patchCord3(dc1PitchB, 0, monoosc2, 1);
AudioConnection          patchCord4(dc1CentB, 0, monoosc2, 2);//Modulatable
AudioConnection          patchCord5(dc1PitchA, 0, monoosc1, 1);
AudioConnection          patchCord6(dc1PitchC, 0, monoosc3, 1);
AudioConnection          patchCord7(bendvelope1, 0, monoosc1, 0);
AudioConnection          patchCord8(bendvelope1, 0, monoosc2, 0);
AudioConnection          patchCord9(bendvelope1, 0, monoosc3, 0);
AudioConnection          patchCord10(dc1CentC, 0, monoosc3, 2);//Modulatable
AudioConnection          patchCord11(monoosc3, 0, mixer5, 2);
AudioConnection          patchCord12(monoosc2, 0, mixer5, 1);
AudioConnection          patchCord13(monoosc1, 0, mixer5, 0);
AudioConnection          patchCord14(dc_filter, 0, filter1, 1);//Modulatable
AudioConnection          patchCord15(mixer5, 0, filter1, 0);
AudioConnection          patchCord16(filter1, 0, is_quad23, 0);
AudioConnection          patchCord17(filter1, 0, is_quad23, 1);
AudioConnection          patchCord18(filter1, 0, is_quad23, 2);
AudioConnection          patchCord19(filter1, 0, is_quad23, 3);
AudioConnection          patchCord20(modGain, 0, modAmp, 1);
AudioConnection          patchCord21(modAmp, 0, effectMixer, 2);
AudioConnection          patchCord22(modOffset, 0, effectMixer, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=1163.75,390
AudioControlSGTL5000     sgtl5000_2;     //xy=1167.75,346
// GUItool: end automatically generated code

AudioAnalyzePeak         peak1;          //xy=1396,593
AudioConnection          patchCord9000(lfo1, 0, peak1, 0);

#define CordDCCB patchCord4
#define CordDCCC patchCord10
#define CordFilter patchCord14

ModulatorBlock modulator[4];

extern "C" {
extern const uint16_t twoPowers12bit[4096];
extern const float note2bpo[129];
}

//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  March 21, 2015
//
//**********************************************************************//

//Note to self:  To us the audio tool, use the bitcrusher as a 1:1 object, then replace name with bendvelope[N]

#include "proto-8Hardware.h"

//**Timers and stuff**************************//
#include "timerModule32.h"
//Globals
uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;

#include "timeKeeper.h"
//**Panels and stuff**************************//
#include "P8Panel.h"

#include "MicroLL.h"

//**Timers and stuff**************************//
IntervalTimer myTimer;

//HOW TO OPERATE
//  Make TimerClass objects for each thing that needs periodic service
//  pass the interval of the period in ticks
//  Set maxInterval to the max foreseen interval of any TimerClass
//  Set maxTimer to overflow number in the header.  maxTimer + maxInterval
//    cannot exceed variable size.

TimerClass32 midiRecordTimer( 1000 );
TimerClass32 panelUpdateTimer(30000);

uint8_t debugLedStates = 1;

TimerClass32 LEDsTimer(20);
TimerClass32 switchesTimer(500);
TimerClass32 knobsTimer(500);

TimerClass32 envTimer( 200 );

TimerClass32 debugTimer(5000000);

//tick variable for interrupt driven timer1
uint32_t usTicks = 0;
uint8_t usTicksMutex = 1; //start locked out

//**Panel State Machine***********************//
P8Interface p8hid;
volatile int32_t pUTStartTime = 0;
volatile int32_t pUTLastTime = 0;
volatile int32_t pUTStopTime = 0;
volatile int32_t pUTLength = 0;

volatile int32_t GPStartTime = 0;
volatile int32_t GPLastTime = 0;
volatile int32_t GPStopTime = 0;
volatile int32_t GPLength = 0;

volatile int32_t MIDIStartTime = 0;
volatile int32_t MIDILastTime = 0;
volatile int32_t MIDIStopTime = 0;
volatile int32_t MIDILength = 0;

volatile int32_t rStartTime = 0;
volatile int32_t rLastTime = 0;
volatile int32_t rStopTime = 0;
volatile int32_t rLength = 0;

//Names use in P8PanelComponents.cpp and .h
LEDShiftRegister LEDs;
AnalogMuxTree knobs;
SwitchMatrix switches;
//End used names

// MIDI things
#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);

MicroLL rxNoteList;
MicroLL noteOnInList;


uint8_t rxLedFlag = 0;


uint8_t const syncPin = 31;

#include "note_values.h"

void HandleNoteOn(byte channel, byte pitch, byte velocity)
{
	rxLedFlag = 1;
	MidiEvent tempEvent;

	tempEvent.timeStamp = 0;
	tempEvent.eventType = 0x90;
	tempEvent.channel = channel;
	tempEvent.value = pitch;
	tempEvent.data = velocity;
	tempEvent.voice = -1;	
	//Hackery
	if( velocity == 0 )
	{
		tempEvent.eventType = 0x80;
	}
	rxNoteList.pushObject( tempEvent );
	
	//midiA.sendNoteOn(pitch, velocity, channel);
}

void HandleNoteOff(byte channel, byte pitch, byte velocity)
{
	rxLedFlag = 1;
	
	MidiEvent tempEvent;

	tempEvent.timeStamp = 0;
	tempEvent.eventType = 0x80;
	tempEvent.channel = channel;
	tempEvent.value = pitch;
	tempEvent.data = 0;
	tempEvent.voice = -1;	

	rxNoteList.pushObject( tempEvent );
	
	//midiA.sendNoteOff(pitch, velocity, channel);
	
}

void HandleControlChange(byte channel, byte number, byte value)
{
	Serial.print(number);
	Serial.print(", ");
	Serial.println(value);

	switch( number )
	{
		case 1:
		//Filter
		filter1.frequency((value * value * 0.9) + 40);  
		break;
		default:
		break;
	}

	
}

void handleSystemReset(void)
{
	//Flush all notes
	while(rxNoteList.listLength())
	{
		rxNoteList.dropObject( 0 );
	}

	//Send note offs to all envelopes
	bendvelope1.noteOff();
	envelope1.noteOff();
	
	p8hid.bv1Trigger.setState(LEDOFF);
}


// -----------------------------------------------------------------------------
void setup() 
{
	//Initialize serial:
	Serial.begin(115200);
	//delay(2000);
	Serial.println("Program Started");
	
	pinMode(syncPin, OUTPUT);
	digitalWrite(syncPin, 0);
	
	LEDs.begin();
	knobs.begin();
	switches.begin();
	
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	
	//Connect MIDI handlers
	midiA.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
	midiA.setHandleNoteOff(HandleNoteOff);
	midiA.setHandleControlChange(HandleControlChange);
	midiA.setHandleSystemReset(handleSystemReset);
	// Initiate MIDI communications
	//midiA.begin(2);
  midiA.begin(MIDI_CHANNEL_OMNI);
	//midiA.turnThruOn();
	midiA.turnThruOff();
	
	AudioMemory(50);

	sgtl5000_1.setAddress(LOW);	
	sgtl5000_1.enable();
	sgtl5000_1.volume(1.0);
	sgtl5000_1.unmuteHeadphone();

	sgtl5000_2.setAddress(HIGH);
	sgtl5000_2.enable();
	sgtl5000_2.volume(1.0);
	sgtl5000_2.unmuteHeadphone();

	dc_filter.amplitude_int( 30000 );
	
	filter1.frequency(1000);  
	filter1.octaveControl(2.5);
	
	dc_zero.amplitude_int( 0 );
	dc_one.amplitude_int( 25000 );
	lfo1.amplitude(0.2);

	monoosc1.begin(); //allocates + default shape
	monoosc2.begin(); //allocates + default shape
	monoosc3.begin(); //allocates + default shape

	mixer5.gain(0, 1);
	mixer5.gain(1, 1);
	mixer5.gain(2, 1);
	mixer5.gain(3, 0);

	//Reset the hid states
	p8hid.reset();

}

void loop()
{
//**Copy to make a new timer******************//  
//   msTimerA.update(usTicks);

	usTicksMutex = 1;

	midiRecordTimer.update(usTicks);

	envTimer.update(usTicks);

	panelUpdateTimer.update(usTicks);

	switchesTimer.update(usTicks);
	knobsTimer.update(usTicks);
	LEDsTimer.update(usTicks);

	debugTimer.update(usTicks);
	
	usTicksMutex = 0;
	
	//**Copy to make a new timer******************//  
	//  if(msTimerA.flagStatus() == PENDING)
	//  {
	//    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
	//  }
	//**Debounce timer****************************//  
	if(switchesTimer.flagStatus() == PENDING)
	{
		switches.tick();
	}
	//**Debounce timer****************************//  
	if(knobsTimer.flagStatus() == PENDING)
	{
		knobs.tick();
	}		
	//**Debounce timer****************************//  
	if(LEDsTimer.flagStatus() == PENDING)
	{
		LEDs.tick();
	}
	//**Bendvelope timer**************************//  
	if(envTimer.flagStatus() == PENDING)
	{
		GPLastTime = GPStartTime;
		GPStartTime = usTicks;
		
		bendvelope1.tick(200);
		
		GPStopTime = usTicks;
		
		int32_t length = GPStopTime - GPStartTime;
		if(length > GPLength )
		{
			GPLength = length;
		}
		//GPCycle = GPStartTime - GPLastTime;

	}
	//**Process the panel and state machine***********//  
	if(panelUpdateTimer.flagStatus() == PENDING)
	{
		pUTLastTime = pUTStartTime;
		pUTStartTime = usTicks;
		//Provide inputs

		//Tick the machine
		p8hid.processMachine( 30 );
		
		pUTStopTime = usTicks;
		int32_t length = pUTStopTime - pUTStartTime;
		if(length > pUTLength )
		{
			pUTLength = length;
		}
	midiA.read();

	}
	if(midiRecordTimer.flagStatus() == PENDING)
	{
		MIDILastTime = MIDIStartTime;
		MIDIStartTime = usTicks;
		//
		listIdemNumber_t unservicedNoteCount = rxNoteList.listLength();
		//Get a note for this round
		MidiEvent tempNote;
		if( unservicedNoteCount > 0 )
		{
//Print full list
rxNoteList.printfMicroLL();
			tempNote = *rxNoteList.readObject( unservicedNoteCount - 1 );
			if( tempNote.eventType == 0x90 )//We got a new note-on
			{
				//For the poly synth, this part high prioritizes notes,
				//while remembering some number of 'on' keys
				
				
				//Search for the note on.  If found, do nothing, else write
				if( noteOnInList.seekObjectbyNoteValue( tempNote ) == -1 )
				{
					//Not found to be not playing by the internal memory of state
					//* Record current note
					noteOnInList.pushObject( tempNote );
					
					//* Play the note with the oscillators
					float tempbpoA = note2bpo[tempNote.value];
					dc1PitchA.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[0]);
					dc1PitchB.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[1]);
					dc1PitchC.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[2]);
					digitalWrite(syncPin, 1);
					bendvelope1.noteOn();
					envelope1.noteOn();
					p8hid.bv1Trigger.setState(LEDON);

					digitalWrite(syncPin, 0);
					rxNoteList.dropObject( unservicedNoteCount - 1 );

					//--The old idea was to track amplitudes, and pick the quietest one to
					//--replace
					//
					//int nextAvailable = -1;
					//int seek;
					//uint8_t currentAmps[4];
					//currentAmps[0] = bendvelope1.amp;
					//Serial.print("CurrentAmp data: ");
					//Serial.print(currentAmps[0]);
					//Serial.print("/n");
					//
					//Serial.print("Used voice: ");
					//Serial.println(tempNote.voice);
						
					
				}
				else
				{
					//Was found
					//do nothing
				}
//Print full list
//noteOnInList.printfMicroLL();
			}
			else if( tempNote.eventType == 0x80 )
			{
				//Congratulations! It's a note off!
//Print full list
noteOnInList.printfMicroLL();
				//Search for the note on.  If found, do nothing, else write
				int8_t tempSeekDepth = noteOnInList.seekObjectbyNoteValue( tempNote );
				if( tempSeekDepth == -1 )
				{
					//not found.
					//Do nothing
					
				}
				else
				{
					//Was found.  Time for note off actions
					//tempNote = *noteOnInList.readObject( tempSeekDepth );

					//Take actions depending on how many notes are requested to be on.
					int16_t listLength = noteOnInList.listLength();
					if( listLength == 1 )
					{
						//Only one note in the list, turn it off
						bendvelope1.noteOff();
						envelope1.noteOff();
						p8hid.bv1Trigger.setState(LEDOFF);
						
					}
					else if( tempSeekDepth == listLength - 1 )
					{
						//The youngest note is turned off, change pitch only
						tempNote = *noteOnInList.readObject( listLength - 2 );
						float tempbpoA = note2bpo[tempNote.value];
						dc1PitchA.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[0]);
						dc1PitchB.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[1]);
						dc1PitchC.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[2]);
						
					}
//					else
//					{
//						//Leave benvelopes on but change pitch
//						tempNote = *noteOnInList.readObject( listLength - 1 );
//						float tempbpoA = note2bpo[tempNote.value];
//						dc1A.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[0]);
//						dc1B.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[1]);
////						digitalWrite(syncPin, 1);
////						digitalWrite(syncPin, 0);
//					}

					Serial.print("Dropping ");
					Serial.println( tempSeekDepth );

					noteOnInList.dropObject( tempSeekDepth );
					rxNoteList.dropObject( unservicedNoteCount - 1 );
					
				}				
//Print full list
//noteOnInList.printfMicroLL();
			}
			else
			{
				//Destroy the crappy data!
				rxNoteList.dropObject( unservicedNoteCount );
			}
		}
		//else we no new data!
		else
		{
			
		}
		MIDIStopTime = usTicks;
		int32_t length = MIDIStopTime - MIDIStartTime;
		if(length > MIDILength )
		{
			MIDILength = length;
		}
	}
	//**Debug timer*******************************//  
	if(debugTimer.flagStatus() == PENDING)
	{
		//Serial.print("\n\nrxNoteList\n");
		//rxNoteList.printfMicroLL();
		//Serial.print("\n\nnoteOnInList\n");
		//noteOnInList.printfMicroLL();
		//Serial.print("\n\nnoteOnOutLists\n");
		Serial.print("Processor=");
		//Serial.print(AudioProcessorUsage());
		//Serial.print(",");
		Serial.print((float)AudioProcessorUsageMax(), 2);
		AudioProcessorUsageMaxReset();
		Serial.print("    ");
		Serial.print("Memory: ");
		//Serial.print(AudioMemoryUsage());
		//Serial.print(",");
		Serial.print(AudioMemoryUsageMax());
		AudioMemoryUsageMaxReset();//reset
		Serial.print(",   FreeRam: ");
		Serial.print(FreeRam());
		Serial.print("\n");
		//Serial.print("panelUpdateTimer (sTime, length): ");
		//Serial.print(pUTStartTime - pUTLastTime);
		//Serial.print(", ");
		//Serial.println(pUTStopTime - pUTStartTime);
		
		Serial.print("GPLength: ");
		Serial.println(GPLength);
		GPLength = 0;
		Serial.print("pUTLength: ");
		Serial.println(pUTLength);
		pUTLength = 0;
		Serial.print("MIDILength: ");
		Serial.println(MIDILength);
		MIDILength = 0;
		Serial.print("rLength: ");
		Serial.println(rLength);
		rLength = 0;

		//Serial.print(", ");
		//Serial.println(usTicks - tempTime);
		if(peak1.available())
		{
			Serial.print("Peak value: ");
			Serial.println(peak1.read());
		}
		Serial.println();
		//timers
		Serial.print("millis: ");
		Serial.println( millis() );
		Serial.print("usTicks: ");
		Serial.println( usTicks );
	}
	midiA.read();
}

uint32_t FreeRam(){ // for Teensy 3.0
    uint32_t stackTop;
    uint32_t heapTop;

    // current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is the free, available ram.
    return stackTop - heapTop;
}

void serviceUS(void)
{
  uint32_t returnVar = 0;
  if(usTicks >= ( maxTimer + maxInterval ))
  {
	 if( usTicksMutex == 0 )
	 {
		 returnVar = usTicks - maxTimer;
	 }
	 else
	 {
		 returnVar = usTicks + 1;
	 }

  }
  else
  {
    returnVar = usTicks + 1;
  }
  usTicks = returnVar;
}

uint32_t tapTempoTimerMath( uint16_t BPMInput )
{
	uint32_t returnVar = 0;
	
	returnVar = 2500000 /( (uint32_t)BPMInput );
	return returnVar;
}
