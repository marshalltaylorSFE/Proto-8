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
//AudioSynthWaveformDcBinary dc1A;           //xy=320.8888854980469,331
//AudioSynthWaveformDcBinary dc1CentA;       //xy=328.8888854980469,367
//AudioSynthWaveformDcBinary dc1B;           //xy=347.8888854980469,402
//AudioSynthWaveformDcBinary dc1CentB;       //xy=355.8888854980469,435
//AudioSynthBendvelope     bendvelope1;    //xy=384.8888854980469,252
//AudioSynthBendvelope     bendvelope2;    //xy=400.8888854980469,538.0000305175781
//AudioSynthMonoOsc        monoosc2;       //xy=590.8889465332031,420.8888854980469
//AudioSynthMonoOsc        monoosc1;       //xy=592.8888854980469,345.8888854980469
//AudioMixer4              mixer5;         //xy=784.8889465332031,408
//AudioFilterStateVariable filter1;        //xy=930.8889465332031,418
//AudioFilterStateVariable filter2;        //xy=1076.8889465332031,417
//AudioOutputI2SQuad       is_quad23;      //xy=1266.8889465332031,426
//AudioConnection          patchCord1(dc1A, 0, monoosc1, 1);
//AudioConnection          patchCord2(dc1CentA, 0, monoosc1, 2);
//AudioConnection          patchCord3(dc1B, 0, monoosc2, 1);
//AudioConnection          patchCord4(dc1CentB, 0, monoosc2, 2);
//AudioConnection          patchCord5(bendvelope1, 0, monoosc1, 0);
//AudioConnection          patchCord6(bendvelope1, 0, monoosc2, 0);
//AudioConnection          patchCord7(monoosc2, 0, mixer5, 1);
//AudioConnection          patchCord8(monoosc1, 0, mixer5, 0);
//AudioConnection          patchCord9(mixer5, 0, filter1, 0);
//AudioConnection          patchCord10(filter1, 0, filter2, 0);
//AudioConnection          patchCord11(filter2, 0, is_quad23, 0);
//AudioConnection          patchCord12(filter2, 0, is_quad23, 1);
//AudioConnection          patchCord13(filter2, 0, is_quad23, 2);
//AudioConnection          patchCord14(filter2, 0, is_quad23, 3);
//AudioControlSGTL5000     sgtl5000_1;     //xy=1220.8889465332031,281
//AudioControlSGTL5000     sgtl5000_2;     //xy=1224.8889465332031,237
//// GUItool: end automatically generated code

// GUItool: begin automatically generated code
AudioSynthWaveformDcBinary glideRate;           //xy=118.88888549804688,205
AudioSynthWaveformDcBinary dc_zero;     //xy=156.88888549804688,429.888916015625
AudioSynthWaveformDcBinaryGlide dc1A; //xy=344.888916015625,331.888916015625
AudioSynthWaveformDcBinaryGlide dc1B; //xy=351.8888854980469,385.8888854980469
AudioSynthBendvelope     bendvelope2;    //xy=351.8888854980469,521.0001525878906
AudioSynthWaveformDcBinary dc1CentB;       //xy=355.8888854980469,435
AudioSynthWaveformSine   lfo1;          //xy=369,570
AudioSynthBendvelope     bendvelope1;    //xy=384.8888854980469,252
AudioSynthMonoOsc        monoosc2;       //xy=590.8889465332031,420.8888854980469
AudioSynthMonoOsc        monoosc1;       //xy=592.8888854980469,345.8888854980469
AudioSynthWaveformDcBinary dc_filter;     //xy=732.8889465332031,536.8889465332031
AudioMixer4              mixer5;         //xy=784.8889465332031,408
AudioFilterStateVariable filter1;        //xy=930.8889465332031,418
AudioOutputI2SQuad       is_quad23;      //xy=1157.8889465332031,428
AudioConnection          patchCord1(glideRate, dc1A);
AudioConnection          patchCord2(glideRate, dc1B);
AudioConnection          patchCord3(dc_zero, 0, monoosc1, 2);
AudioConnection          patchCord4(dc1A, 0, monoosc1, 1);
AudioConnection          patchCord5(dc1B, 0, monoosc2, 1);
AudioConnection          patchCord6(dc1CentB, 0, monoosc2, 2);
AudioConnection          patchCord7(bendvelope1, 0, monoosc1, 0);
AudioConnection          patchCord8(bendvelope1, 0, monoosc2, 0);
AudioConnection          patchCord9(monoosc2, 0, mixer5, 1);
AudioConnection          patchCord10(monoosc1, 0, mixer5, 0);
AudioConnection          patchCord11(dc_filter, 0, filter1, 1);
AudioConnection          patchCord12(mixer5, 0, filter1, 0);
AudioConnection          patchCord13(filter1, 0, is_quad23, 0);
AudioConnection          patchCord14(filter1, 0, is_quad23, 1);
AudioConnection          patchCord15(filter1, 0, is_quad23, 2);
AudioConnection          patchCord16(filter1, 0, is_quad23, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=1120.8889465332031,323
AudioControlSGTL5000     sgtl5000_2;     //xy=1124.8889465332031,279
// GUItool: end automatically generated code


AudioAnalyzePeak         peak1;          //xy=1396,593
AudioConnection          patchCord20(lfo1, 0, peak1, 0);

#define CordDCPA patchCord4
#define CordDCCA patchCord3
#define CordDCPB patchCord5
#define CordDCCB patchCord6


#define CordFilter patchCord11


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
TimerClass32 panelUpdateTimer(10000);
uint8_t debugLedStates = 1;

TimerClass32 LEDsTimer(20);
TimerClass32 switchesTimer(500);
TimerClass32 knobsTimer(500);

TimerClass32 ledToggleTimer( 333000 );
uint8_t ledToggleState = 0;
TimerClass32 ledToggleFastTimer( 100000 );
uint8_t ledToggleFastState = 0;

TimerClass32 envTimer( 200 );

//TimerClass32 processSMTimer( 50000 );

TimerClass32 debounceTimer(5000);

TimerClass32 debugTimer(1000000);

//tick variable for interrupt driven timer1
uint32_t usTicks = 0;
uint8_t usTicksMutex = 1; //start locked out

//**Panel State Machine***********************//
P8Interface p8hid;
volatile uint32_t pUTStartTime = 0;
volatile uint32_t pUTLastTime = 0;
volatile uint32_t pUTStopTime = 0;
volatile uint32_t GPStartTime = 0;
volatile uint32_t GPLastTime = 0;
volatile uint32_t GPStopTime = 0;


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

//New voice trackers
uint8_t voicesUsed[4] = {0,0,0,0};
float fineTuneA = 68 * .00261438 + 0.6666666;
float coarseTuneA = 2 * 9 * .0137255 + 0.25;
float fineTuneB = 68 * .00261438 + 0.6666666;
float coarseTuneB = 2 * 27 * .0137255 + 0.25;
float fineTuneC = 64 * .00261438 + 0.6666666;
float coarseTuneC = 2 * 64 * .0137255 + 0.25;
float fineTuneD = 64 * .00261438 + 0.6666666;
float coarseTuneD = 2 * 64 * .0137255 + 0.25;


float last1 = 1;
float last2 = 1;
float last3 = 1;
float last4 = 1;

uint8_t lastAttack = 10;
int8_t lastAttackBend = 0;
uint8_t lastDecay = 10;
int8_t lastDecayBend = 0;
uint8_t lastRelease = 10;
int8_t lastReleaseBend = 0;

#include "note_values.h"

void HandleNoteOn(byte channel, byte pitch, byte velocity)
{
	rxLedFlag = 1;
	MidiEvent tempEvent;

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
	//Clear voice flags
	voicesUsed[0] = 0;
	voicesUsed[1] = 0;
	voicesUsed[2] = 0;
	voicesUsed[3] = 0;

	//Send note offs to all envelopes
	bendvelope1.noteOff();
	bendvelope2.noteOff();
	
	p8hid.bv1Trigger.setState(LEDOFF);
	p8hid.bv2Trigger.setState(LEDOFF);
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
	
	bendvelope1.attack( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope1.decay( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope1.sustain( 150 );// 0 to 255 for level
	bendvelope1.release( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope1.setAttackHold( 10 );
	bendvelope2.attack( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope2.decay( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope2.sustain( 150 );// 0 to 255 for level
	bendvelope2.release( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope2.setAttackHold( 10 );
	
	LEDs.begin();
	knobs.begin();
	switches.begin();
	
	//Init panel.h stuff
	p8hid.init();
	
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	
	//Update the panel
	p8hid.update();
	p8hid.reset();
	
	//Connect MIDI handlers
	midiA.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
	midiA.setHandleNoteOff(HandleNoteOff);
	midiA.setHandleControlChange(HandleControlChange);
	midiA.setHandleSystemReset(handleSystemReset);
	// Initiate MIDI communications, listen to all channels
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

	dc_filter.amplitude_int( 0 );
	
	filter1.frequency(8000);  
	filter1.octaveControl(2.5);
	
	//multiosc1.amplitude(0x7FFF);
	glideRate.amplitude_int( 10000 );
	dc_zero.amplitude_int( 0 );
	//dc_one.amplitude_int( 25000 );
	lfo1.amplitude(0.2);
	//lfo1Pitch.amplitude_4_12( 1.0 );
	//lfo1.begin();
	//lfo1.staticAmp[0] = 255;
	monoosc1.begin(); //allocates + default shape
	monoosc2.begin(); //allocates + default shape
	//--This would be useful for enumerating multiple multiosc blocks
	//int16_t * tempPointer = multiosc1.getPointer(0);
	//multiosc2.setPointer(0, tempPointer);

	//dc1A.amplitude_4_12(6.459432);
	//dc1B.amplitude_4_12(6.459432);
	mixer5.gain(0, 1);
	mixer5.gain(1, 1);
	mixer5.gain(2, 0);
	mixer5.gain(3, 0);

}

void loop()
{
//**Copy to make a new timer******************//  
//   msTimerA.update(usTicks);

	midiRecordTimer.update(usTicks);

	debounceTimer.update(usTicks);
	envTimer.update(usTicks);

	ledToggleTimer.update(usTicks);
	ledToggleFastTimer.update(usTicks);
	panelUpdateTimer.update(usTicks);
	switchesTimer.update(usTicks);
	knobsTimer.update(usTicks);
	LEDsTimer.update(usTicks);

	debugTimer.update(usTicks);
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
		bendvelope1.tick(100);
		bendvelope2.tick(100);
		GPStopTime = usTicks;
	}
	//**Debounce timer****************************//  
	if(debounceTimer.flagStatus() == PENDING)
	{
		p8hid.timersMIncrement(5);
	
	}
		
	//**Process the panel and state machine***********//  
	if(panelUpdateTimer.flagStatus() == PENDING)
	{
		pUTLastTime = pUTStartTime;
		pUTStartTime = usTicks;
		//Provide inputs

		//Tick the machine
		p8hid.processMachine();
		
		//Deal with outputs
		//float ampTemp = 0;
		//ampTemp = bendvelope1.amp;
		
		//--This part from poly
		//if( bendvelope2.amp > ampTemp )
		//{
		//	ampTemp = bendvelope2.amp;
		//}		
		//if( bendvelope3.amp > ampTemp )
		//{
		//	ampTemp = bendvelope2.amp;
		//}
		//if( bendvelope4.amp > ampTemp )
		//{
		//	ampTemp = bendvelope2.amp;
		//}
		
		//dc1.amplitude((ampTemp / 128.0) - 1.0);
		//LEDs.setNumber1( ampTemp );
		
		pUTStopTime = usTicks;

	}
	if(midiRecordTimer.flagStatus() == PENDING)
	{
		//
		listIdemNumber_t unservicedNoteCount = rxNoteList.listLength();
		//Get a note for this round
		MidiEvent tempNote;
		if( unservicedNoteCount > 0 )
		{
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
					dc1A.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[0]);
					dc1B.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[1]);
					digitalWrite(syncPin, 1);
					bendvelope1.noteOn();
					bendvelope2.noteOn();
					p8hid.bv1Trigger.setState(LEDON);
					p8hid.bv2Trigger.setState(LEDON);

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
			}
			else if( tempNote.eventType == 0x80 )
			{
				//Congratulations! It's a note off!
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
					Serial.print("Dropping ");
					Serial.println( tempSeekDepth );
					//Find the note and learn its voice
					
					/////This is where we might turn the note off -- repurpose tempNote
					tempNote = *noteOnInList.readObject( tempSeekDepth );
					bendvelope1.noteOff();
					bendvelope2.noteOff();
					p8hid.bv1Trigger.setState(LEDOFF);
					p8hid.bv2Trigger.setState(LEDOFF);

					//--old
					//Serial.print("Voice silenced: ");
					//Serial.println(tempNote.voice);					

					noteOnInList.dropObject( tempSeekDepth );

					rxNoteList.dropObject( unservicedNoteCount - 1 );
					
					//Find oldest note still on. For now, retrigger
					int16_t listLength = noteOnInList.listLength();
					if( listLength > 0 )
					{
						//Print full list
						noteOnInList.printfMicroLL();

						tempNote = *noteOnInList.readObject( listLength - 1 );
						float tempbpoA = note2bpo[tempNote.value];
						dc1A.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[0]);
						dc1B.amplitude_4_12(tempbpoA + p8hid.dcTuneOffset[1]);
						digitalWrite(syncPin, 1);
						// This should be: if note dropped was not playing, do not
						// regrigger.  if note was playing, restart oldest note
						//bendvelope1.noteOn();
						//bendvelope2.noteOn();
						digitalWrite(syncPin, 0);
					}
					
				}				
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
	}

	//**Fast LED toggling of the panel class***********//  
	if(ledToggleFastTimer.flagStatus() == PENDING)
	{
		p8hid.toggleFastFlasherState();
		
	}

	//**LED toggling of the panel class***********//  
	if(ledToggleTimer.flagStatus() == PENDING)
	{
		p8hid.toggleFlasherState();
		
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
		Serial.print("panelUpdateTimer (sTime, length): ");
		Serial.print(pUTStartTime - pUTLastTime);
		Serial.print(", ");
		Serial.println(pUTStopTime - pUTStartTime);
		//Serial.print(", ");
		//Serial.println(usTicks - tempTime);
		if(peak1.available())
		{
			Serial.print("Peak value: ");
			Serial.println(peak1.read());
		}
		Serial.println();

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
    returnVar = usTicks - maxTimer;

  }
  else
  {
    returnVar = usTicks + 1;
  }
  usTicks = returnVar;
  usTicksMutex = 0;  //unlock
}

uint32_t tapTempoTimerMath( uint16_t BPMInput )
{
	uint32_t returnVar = 0;
	
	returnVar = 2500000 /( (uint32_t)BPMInput );
	return returnVar;
}