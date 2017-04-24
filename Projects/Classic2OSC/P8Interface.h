//**********************************************************************//
//
//  Interface example for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//  This file defines the human interaction of the panel parts
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//    2016/2/29: Moved seven segment stuff to voltage monitor
//
//**********************************************************************//
#ifndef P8INTERFACE_H
#define P8INTERFACE_H

#include "stdint.h"
#include "timeKeeper.h"
#include "PanelComponents.h"
#include "P8Panel.h"
#include "flagMessaging.h"

#include "Audio.h"
#include "synth_dc_binary.h"

enum PStates
{
	PInit,
	PIdle,

};

enum BusStates
{
	BInit,
	BShowAll,
	BPickSrc,
	BPickDest,
};

//enum BusDestStates
//{
//	BusDestInit,
//	BusDestShowAll,
//	BusDestSelect,
//};

class ModSourceItem
{
public:
	ModSourceItem( void ) : src(NULL), src_index(0) {}
	void set(AudioStream * source, unsigned char sourceOutput)
	{
		src = source;
		src_index = sourceOutput;
	}
	AudioStream* src;
	unsigned char src_index;
	
private:

};

class EffectPathItem
{
public:
	EffectPathItem( void ) : src(NULL), dst(NULL), src_index(0), dest_index(0) {}
	void set(AudioConnection * audioPath) //copy passed cord
	{
		associatedPatchCord = audioPath;
		src = audioPath->getSrc();
		dst = audioPath->getDst();
		src_index = audioPath->getSrc_Index();
		dest_index = audioPath->getDest_Index();
	}
	AudioStream* src;
	AudioStream* dst;
	unsigned char src_index;
	unsigned char dest_index;
	AudioConnection * associatedPatchCord = NULL;
	friend class AudioConnection;
private:

};

class ModulatorBlock
{
public:
	ModulatorBlock( void ) : connected(0)
	{
		effectMixer.gain(0, 1.0);
		effectMixer.gain(1, 1.0);
		effectMixer.gain(2, 1.0);
		effectMixer.gain(3, 1.0);
	}
	void init( void )
	{
		patchCord1.reconnect(&modGain, 0, &modAmp, 1);
		patchCord2.reconnect(&modAmp, 0, &effectMixer, 2);
		patchCord3.reconnect(&modOffset, 0, &effectMixer, 3);
	}
	void insert( EffectPathItem * path, AudioStream * modSourceObject, uint8_t modSourceIndex)
	{
		if(( path->associatedPatchCord != NULL )&&(connected == 0))
		{
			connected = 1;
			modSourcePatchCord.reconnect(modSourceObject, modSourceIndex, &modAmp, 0);
			path->associatedPatchCord->disconnect();
			modulatedOutputPatchCord.reconnect(path->src, path->src_index, &effectMixer, 1);
			path->associatedPatchCord->reconnect(&effectMixer, 0, path->dst, path->dest_index);
		}
	}
	void remove( EffectPathItem * path )
	{
		if(( path->associatedPatchCord != NULL )&&(connected == 1))
		{
			connected = 0;
			modulatedOutputPatchCord.disconnect();
			path->associatedPatchCord->disconnect();
			path->associatedPatchCord->reconnect(path->src, path->src_index, path->dst, path->dest_index);
			modSourcePatchCord.disconnect();
		}
	}

	uint8_t connected;
	AudioSynthWaveformDcBinary modGain;     //xy=514,982
	AudioEffectMultiply      modAmp;      //xy=655,976
	AudioSynthWaveformDcBinary modOffset;     //xy=662,1021
	AudioMixer4              effectMixer;    //xy=828,954
private:
	AudioConnection          patchCord1;
	AudioConnection          patchCord2;
	AudioConnection          patchCord3;
	AudioConnection modSourcePatchCord;
	AudioConnection modulatedOutputPatchCord;
};
//// GUItool: begin automatically generated code
//AudioSynthWaveformDcBinary modGain;        //xy=397,1203
//AudioEffectMultiply      modAmp;         //xy=538,1197
//AudioSynthWaveformDcBinary modOffset;      //xy=545,1242
//AudioMixer4              effectMixer;    //xy=711,1175
//AudioConnection          patchCord1(modGain, 0, modAmp, 1);
//AudioConnection          patchCord2(modAmp, 0, effectMixer, 2);
//AudioConnection          patchCord3(modOffset, 0, effectMixer, 3);
//// GUItool: end automatically generated code


class P8Interface : public P8Panel
{
public:
	P8Interface( void );
	void reset( void );
	//State machine stuff  
	void processMachine( uint16_t );
	void printDebugInfo( void );
	void tickStateMachine( void );
	void tickBusStateMachine( void );
	void tickBusDestStateMachine( void );
	void displayBusMapping( void );
	
	//For waveforms?  Kind of unsure about this function
	//Maybe it chooses a waveform pointer to use?
	void setPointer( uint8_t, int16_t * );
	
	//Flags coming in from the system
	//  ..and data.
	
	//Internal - and going out to the system - Flags
	uint8_t lastAttack;
	uint8_t lastAttackBend;
	uint8_t lastAttackHold;
	uint8_t lastDecay;
	uint8_t lastDecayBend;
	uint8_t lastSustain;
	uint8_t lastRelease;
	uint8_t lastReleaseBend;
	
	//Data going out to the system
	float dcTuneOffset[4]; //osc A thru D


private:
	//Internal Flags
	MessagingFlag changeVolume;

	//  ..and data
	int8_t waveformShape1 = 1;
	int8_t waveformShape2 = 1;
	int8_t waveformShape3 = 1;
	int8_t waveformShape4 = 1;
	int8_t group1Store = 0;
	int8_t group2Store = 0;
	int8_t group3Store = 0;
	
	int8_t oscASelect = 0;
	int8_t oscBSelect = 0;
	
	int16_t * waveFormPointerA;
	int16_t * waveFormPointerB;

	uint8_t waveShapeParams[3][4];

	uint8_t lfo1WaveSrc;
	uint8_t lfo2WaveSrc;
	uint8_t oscAWaveSrc;
	uint8_t oscBWaveSrc;
	uint8_t oscCWaveSrc;
	uint8_t oscDWaveSrc;

	uint8_t oscAOctaveState;
	uint8_t oscBOctaveState;
	uint8_t oscCOctaveState;
	uint8_t oscDOctaveState;
	uint8_t bv1SelectorState;
	uint8_t bv2SelectorState;
	
	//State machine stuff  
	PStates state;
	BusStates busState;
	
	uint8_t srcBusSelected;
	uint8_t srcCursorOn;
	uint8_t destBusSelected;
	uint8_t destCursorOn;
	
	uint8_t srcMapping[6];
	uint8_t destMapping[6];
	uint8_t srcCursor;
	uint8_t destCursor;
	
	//AudioConnection tables
	ModSourceItem modSources[15];
	EffectPathItem effectPaths[15];

};


#endif