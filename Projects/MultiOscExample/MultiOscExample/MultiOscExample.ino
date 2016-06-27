#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SerialFlash.h"
#include "synth_bendvelope.h"
#include "synth_multiosc.h"
#include "synth_dc_binary.h"

// GUItool: begin automatically generated code
AudioSynthBendvelope     bendvelope1;      //xy=506.888916015625,291.8888854980469
AudioSynthBendvelope     bendvelope2;      //xy=511.8889465332031,372.8888854980469
AudioSynthBendvelope     bendvelope3;      //xy=517.888916015625,449.8888854980469
AudioSynthBendvelope     bendvelope4;      //xy=522.888916015625,533.8889465332031
AudioSynthMultiOsc       multiosc1;       //xy=653.8889465332031,291.888916015625
AudioSynthMultiOsc       multiosc2;       //xy=661.8889465332031,371.8888854980469
AudioSynthMultiOsc       multiosc3;       //xy=668.8889465332031,453.8888854980469
AudioSynthMultiOsc       multiosc4;       //xy=680.8889465332031,537.8889465332031
AudioMixer4              mixer5;         //xy=987.8888854980469,413
AudioFilterStateVariable filter1;        //xy=1143.8888854980469,421
AudioFilterStateVariable filter3;        //xy=1279.8888854980469,422
AudioOutputI2SQuad       i2s_quad2;      //xy=1469.8888854980469,431
//AudioOutputI2S           i2s_quad2;      //xy=1469.8888854980469,431
AudioSynthWaveformDcBinary     dc1;            //xy=285.8888854980469,314.8888854980469
AudioSynthWaveformDcBinary     dc2;            //xy=285.8888854980469,314.8888854980469
AudioSynthWaveformDcBinary     dc3;            //xy=285.8888854980469,314.8888854980469
AudioSynthWaveformDcBinary     dc4;            //xy=285.8888854980469,314.8888854980469
AudioConnection          patchCord1(bendvelope1, 0, multiosc1, 0);
AudioConnection          patchCord2(bendvelope2, 0, multiosc2, 0);
AudioConnection          patchCord3(bendvelope3, 0, multiosc3, 0);
AudioConnection          patchCord4(bendvelope4, 0, multiosc4, 0);
AudioConnection          patchCord15(dc1, 0, multiosc1, 1);//A connection
AudioConnection          patchCord16(dc2, 0, multiosc2, 1);
AudioConnection          patchCord17(dc3, 0, multiosc3, 1);
AudioConnection          patchCord18(dc4, 0, multiosc4, 1);
AudioConnection          patchCord19(dc1, 0, multiosc1, 2);//B connection
AudioConnection          patchCord20(dc2, 0, multiosc2, 2);
AudioConnection          patchCord21(dc3, 0, multiosc3, 2);
AudioConnection          patchCord22(dc4, 0, multiosc4, 2);
AudioConnection          patchCord5(multiosc1, 0, mixer5, 0);
AudioConnection          patchCord6(multiosc2, 0, mixer5, 1);
AudioConnection          patchCord7(multiosc3, 0, mixer5, 2);
AudioConnection          patchCord8(multiosc4, 0, mixer5, 3);
AudioConnection          patchCord9(mixer5, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 0, filter3, 0);
AudioConnection          patchCord11(filter3, 0, i2s_quad2, 0);
AudioConnection          patchCord12(filter3, 0, i2s_quad2, 1);
AudioConnection          patchCord13(filter3, 0, i2s_quad2, 2);
AudioConnection          patchCord14(filter3, 0, i2s_quad2, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=1423.8888854980469,286
AudioControlSGTL5000     sgtl5000_1;     //xy=1427.8888854980469,242
// GUItool: end automatically generated code

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
#include "VoltageMonitor.h"

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
#include "P8Interface.h"
P8Interface p8hid;
volatile uint32_t pUTStartTime = 0;
volatile uint32_t pUTLastTime = 0;
volatile uint32_t pUTStopTime = 0;
volatile uint32_t GPStartTime = 0;
volatile uint32_t GPLastTime = 0;
volatile uint32_t GPStopTime = 0;


//Names use in P8PanelComponents.cpp and .h
VoltageMonitor LEDs;
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
		filter3.frequency((value * value * 0.9) + 40);  
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
	bendvelope3.noteOff();
	bendvelope4.noteOff();
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
	bendvelope3.attack( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope3.decay( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope3.sustain( 150 );// 0 to 255 for level
	bendvelope3.release( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope3.setAttackHold( 10 );
	bendvelope4.attack( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope4.decay( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope4.sustain( 150 );// 0 to 255 for level
	bendvelope4.release( 10, 0 );// 0 to 255 for length, -128 to 127
	bendvelope4.setAttackHold( 10 );
	
	LEDs.begin();
	knobs.begin();
	switches.begin();
	
	//Init panel.h stuff
	p8hid.init();
	
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.001 seconds
	
	//Update the panel
	p8hid.update();

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

	filter1.frequency(8000);  
	filter3.frequency(8000);
	
	multiosc1.amplitude(0.25);
	multiosc2.amplitude(0.25);
	multiosc3.amplitude(0.25);
	multiosc4.amplitude(0.25);
	
	multiosc1.begin(); //allocates + default shape
	int16_t * tempPointer = multiosc1.getPointer(0);
	multiosc2.setPointer(0, tempPointer);
	multiosc3.setPointer(0, tempPointer);
	multiosc4.setPointer(0, tempPointer);
	p8hid.setPointer(0, tempPointer);

	dc1.amplitude_3_12(6.459432);
	
	mixer5.gain(0, 0.25);
	mixer5.gain(1, 0.25);
	mixer5.gain(2, 0.25);
	mixer5.gain(3, 0.25);
	
	
}

void loop()
{
//**Copy to make a new timer******************//  
//   msTimerA.update(usTicks);

	midiRecordTimer.update(usTicks);
	ledToggleTimer.update(usTicks);
	ledToggleFastTimer.update(usTicks);
	panelUpdateTimer.update(usTicks);
	debounceTimer.update(usTicks);
	envTimer.update(usTicks);
	
	debugTimer.update(usTicks);
	LEDsTimer.update(usTicks);
	switchesTimer.update(usTicks);
	knobsTimer.update(usTicks);
	//**Copy to make a new timer******************//  
	//  if(msTimerA.flagStatus() == PENDING)
	//  {
	//    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
	//  }
	//**Debounce timer****************************//  
	if(LEDsTimer.flagStatus() == PENDING)
	{
		LEDs.tickSeg();
	
	}
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
	//**Bendvelope timer**************************//  
	if(envTimer.flagStatus() == PENDING)
	{
		GPLastTime = GPStartTime;
		GPStartTime = usTicks;
		bendvelope1.tick(100);
		bendvelope2.tick(100);
		bendvelope3.tick(100);
		bendvelope4.tick(100);
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
		float ampTemp = 0;
		ampTemp = bendvelope1.amp;
		if( bendvelope2.amp > ampTemp )
		{
			ampTemp = bendvelope2.amp;
		}		
		if( bendvelope3.amp > ampTemp )
		{
			ampTemp = bendvelope2.amp;
		}
		if( bendvelope4.amp > ampTemp )
		{
			ampTemp = bendvelope2.amp;
		}
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
				//Search for the note on.  If found, do nothing, else write
				if( noteOnInList.seekObjectbyNoteValue( tempNote ) == -1 )
				{
					//note not found.
					////////This is where we might play the note
					//Check for available voice by finding the next zero

					int nextAvailable = -1;
					int seek;
					uint8_t currentAmps[4];
					currentAmps[0] = bendvelope1.amp;
					currentAmps[1] = bendvelope2.amp;
					currentAmps[2] = bendvelope3.amp;
					currentAmps[3] = bendvelope4.amp;
					Serial.print("CurrentAmp data: ");
					Serial.print(currentAmps[0]);
					Serial.print(",  ");
					Serial.print(currentAmps[1]);
					Serial.print(", ");
					Serial.print(currentAmps[2]);
					Serial.print(", ");
					Serial.println(currentAmps[3]);
					
					//Seek the next available with the lowest current amp.
					for( seek = 0; seek < 4; seek++ )
					{
						if(voicesUsed[seek] == 0)
						{
							//the voice is free
							if(nextAvailable == -1)
							{
								//no previous note to compare
								nextAvailable = seek;
							}
							else
							{
								//compare, choose the quieter voice
								if( currentAmps[seek] < currentAmps[nextAvailable] )
								{
									nextAvailable = seek;
								}
								
							}
						}

					}
					if( nextAvailable != -1 )//One is free
					{
						//Assign the note to this voice
						tempNote.voice = nextAvailable;
						voicesUsed[nextAvailable] = 1;
						//mixer5.gain(tempNote.voice, 0.25);
						//select voice
						float tempbpoA = note2bpo[tempNote.value];
						//float tempFrequencyB = note_frequency[tempNote.value] * fineTuneB * coarseTuneB;
						//float tempFrequencyC = note_frequency[tempNote.value] * fineTuneC * coarseTuneC;
						//float tempFrequencyD = note_frequency[tempNote.value] * fineTuneD * coarseTuneD;
						//last1 = note2bpo[tempNote.value];
						//last2 = note_frequency[tempNote.value];
						//last3 = note_frequency[tempNote.value];
						//last4 = note_frequency[tempNote.value];
						
						switch( tempNote.voice )
						{
							case 0:
							//multiosc1.frequency(tempFrequencyA);
							dc1.amplitude_3_12(tempbpoA + p8hid.dcAmpOffset[0]);
							digitalWrite(syncPin, 1);
							bendvelope1.noteOn();
							digitalWrite(syncPin, 0);
							break;
							case 1:
							dc2.amplitude_3_12(tempbpoA + p8hid.dcAmpOffset[0]);
							bendvelope2.noteOn();
							break;
							case 2:
							dc3.amplitude_3_12(tempbpoA + p8hid.dcAmpOffset[0]);
							bendvelope3.noteOn();
							break;
							case 3:
							dc4.amplitude_3_12(tempbpoA + p8hid.dcAmpOffset[0]);
							bendvelope4.noteOn();
							break;
							default:
							break;
						}
						Serial.print("Used voice: ");
						Serial.println(tempNote.voice);
						
					}
					else
					{
						//No new voices
					}
					//record
					noteOnInList.pushObject( tempNote );
					
					rxNoteList.dropObject( unservicedNoteCount - 1 );
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
					voicesUsed[tempNote.voice] = 0;
					//mixer5.gain(tempNote.voice, 0);
					switch( tempNote.voice )
						{
							case 0:
							bendvelope1.noteOff();
							break;
							case 1:
							bendvelope2.noteOff();
							break;
							case 2:
							bendvelope3.noteOff();
							break;
							case 3:
							bendvelope4.noteOff();
							break;
							default:
							break;
						}
					Serial.print("Voice silenced: ");
					Serial.println(tempNote.voice);					
					
					noteOnInList.dropObject( tempSeekDepth );

					rxNoteList.dropObject( unservicedNoteCount - 1 );
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
		Serial.print("all=");
		Serial.print(AudioProcessorUsage());
		Serial.print(",");
		Serial.print(AudioProcessorUsageMax());
		Serial.print("    ");
		Serial.print("Memory: ");
		Serial.print(AudioMemoryUsage());
		Serial.print(",");
		Serial.print(AudioMemoryUsageMax());
		Serial.print(",   FreeRam: ");
		Serial.print(FreeRam());
		Serial.print("\n");
		Serial.print("panelUpdateTimer (sTime, length): ");
		Serial.print(pUTStartTime - pUTLastTime);
		Serial.print(", ");
		Serial.println(pUTStopTime - pUTStartTime);
		Serial.print("Gen Prps, bvtick (sTime, length): ");
		Serial.print(GPStartTime - GPLastTime);
		Serial.print(", ");
		Serial.println(GPStopTime - GPStartTime);
		//Serial.print(", ");
		//Serial.println(usTicks - tempTime);
		
		Serial.println();

	}
	midiA.read();

	
}

//uint32_t FreeRam(){ // for Teensy 3.0
//    uint32_t stackTop;
//    uint32_t heapTop;
//
//    // current position of the stack.
//    stackTop = (uint32_t) &stackTop;
//
//    // current position of heap.
//    void* hTop = malloc(1);
//    heapTop = (uint32_t) hTop;
//    free(hTop);
//
//    // The difference is the free, available ram.
//    return stackTop - heapTop;
//}

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