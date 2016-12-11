//**********************************************************************//
//
//  Panel example for the Bendvelope panel, 16 button/led bar w/ knob
//  and scanned matrix 7 segment display.
//  
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2016/2/24: Created
//
//**********************************************************************//
#ifndef P8PANEL_H
#define P8PANEL_H

#include "P8PanelComponents.h"

class P8Panel
{
public:
	P8Panel( void );
	void update( void );
	void init( void );
	void toggleFlasherState( void );
	void toggleFastFlasherState( void );
	
	//Bendvelope1
	P8PanelKnob8Bit bv1Attack;
	P8PanelKnob8Bit bv1AttackBend;
	P8PanelKnob8Bit bv1Hold;
	P8PanelKnob8Bit bv1Decay;
	P8PanelKnob8Bit bv1DecayBend;
	P8PanelKnob8Bit bv1Sustain;
	P8PanelKnob8Bit bv1Release;
	P8PanelKnob8Bit bv1ReleaseBend;
	P8PanelKnob8Bit bv1Select;
	P8PanelLed bv1Trigger;
	
	//Bendvelope2
	P8PanelKnob8Bit bv2Attack;
	P8PanelKnob8Bit bv2AttackBend;
	P8PanelKnob8Bit bv2Hold;
	P8PanelKnob8Bit bv2Decay;
	P8PanelKnob8Bit bv2DecayBend;
	P8PanelKnob8Bit bv2Sustain;
	P8PanelKnob8Bit bv2Release;
	P8PanelKnob8Bit bv2ReleaseBend;
	P8PanelKnob8Bit bv2Select;
	P8PanelLed bv2Trigger;
	
	//Bus
	P8PanelKnob8Bit bus1Amp;
	P8PanelKnob8Bit bus1Offset;
	P8PanelButton bus1SrcPick;
	P8PanelButton bus1DestPick;
	P8PanelLed bus1SrcLed;
	P8PanelLed bus1DestLed;
	
	P8PanelKnob8Bit bus2Amp;
	P8PanelKnob8Bit bus2Offset;
	P8PanelButton bus2SrcPick;
	P8PanelButton bus2DestPick;
	P8PanelLed bus2SrcLed;
	P8PanelLed bus2DestLed;

	P8PanelKnob8Bit bus3Amp;
	P8PanelKnob8Bit bus3Offset;
	P8PanelButton bus3SrcPick;
	P8PanelButton bus3DestPick;
	P8PanelLed bus3SrcLed;
	P8PanelLed bus3DestLed;

	P8PanelKnob8Bit bus4Amp;
	P8PanelKnob8Bit bus4Offset;
	P8PanelButton bus4SrcPick;
	P8PanelButton bus4DestPick;
	P8PanelLed bus4SrcLed;
	P8PanelLed bus4DestLed;

	P8PanelKnob8Bit bus5Amp;
	P8PanelKnob8Bit bus5Offset;
	P8PanelButton bus5SrcPick;
	P8PanelButton bus5DestPick;
	P8PanelLed bus5SrcLed;
	P8PanelLed bus5DestLed;
	
	P8PanelLed modSrcLed0;
	P8PanelLed modSrcLed1;
	P8PanelLed modSrcLed2;
	P8PanelLed modSrcLed3;
	P8PanelLed modSrcLed4;
	P8PanelLed modSrcLed5;
	P8PanelLed modSrcLed6;
	P8PanelLed modSrcLed7;
	P8PanelLed modSrcLed8;
	P8PanelLed modSrcLed9;
	P8PanelLed modSrcLed10;
	P8PanelLed modSrcLed11;
	P8PanelLed modSrcLed12;
	P8PanelLed modSrcLed13;
	P8PanelLed modSrcLed14;
	
	P8PanelLed modDestLed0;
	P8PanelLed modDestLed1;
	P8PanelLed modDestLed2;
	P8PanelLed modDestLed3;
	P8PanelLed modDestLed4;
	P8PanelLed modDestLed5;
	P8PanelLed modDestLed6;
	P8PanelLed modDestLed7;
	P8PanelLed modDestLed8;
	P8PanelLed modDestLed9;
	P8PanelLed modDestLed10;
	P8PanelLed modDestLed11;
	P8PanelLed modDestLed12;
	P8PanelLed modDestLed13;
	P8PanelLed modDestLed14;
	
	//Master
	P8PanelKnob8Bit masterCoarseTune;
	P8PanelKnob8Bit masterFineTune;
	P8PanelKnob8Bit masterVolume;
	
	//LFO1
	P8PanelKnob8Bit lfo1Freq;
	P8PanelButton lfo1Shape;
	P8PanelLed lfo1Led1;
	P8PanelLed lfo1Led2;
	P8PanelLed lfo1Led3;
	
	//LFO2
	P8PanelKnob8Bit lfo2Freq;
	P8PanelButton lfo2Shape;
	P8PanelLed lfo2Led1;
	P8PanelLed lfo2Led2;
	P8PanelLed lfo2Led3;	
	
	//OSCA
	P8PanelKnob8Bit oscAPitch;
	P8PanelSelector oscAOctave;
	//P8PanelLed oscASyncLed;
	P8PanelButton oscASync;
	P8PanelKnob8Bit oscACent;
	P8PanelButton oscAShape;
	P8PanelLed oscALed1;
	P8PanelLed oscALed2;
	P8PanelLed oscALed3;
	P8PanelKnob8Bit oscAPreAmp;
	
	//OSCB
	P8PanelKnob8Bit oscBPitch;
	P8PanelSelector oscBOctave;
	P8PanelLed oscBSyncLed;
	P8PanelButton oscBSync;
	P8PanelKnob8Bit oscBCent;
	P8PanelButton oscBShape;
	P8PanelLed oscBLed1;
	P8PanelLed oscBLed2;
	P8PanelLed oscBLed3;
	P8PanelKnob8Bit oscBPreAmp;

	//OSCC
	P8PanelKnob8Bit oscCPitch;
	P8PanelSelector oscCOctave;
	P8PanelLed oscCSyncLed;
	P8PanelButton oscCSync;
	P8PanelKnob8Bit oscCCent;
	P8PanelButton oscCShape;
	P8PanelLed oscCLed1;
	P8PanelLed oscCLed2;
	P8PanelLed oscCLed3;
	P8PanelKnob8Bit oscCPreAmp;

	//OSCD
	P8PanelKnob8Bit oscDPitch;
	P8PanelSelector oscDOctave;
	P8PanelLed oscDSyncLed;
	P8PanelButton oscDSync;
	P8PanelKnob8Bit oscDCent;
	P8PanelButton oscDShape;
	P8PanelLed oscDLed1;
	P8PanelLed oscDLed2;
	P8PanelLed oscDLed3;
	P8PanelKnob8Bit oscDPreAmp;
	
	//Wave Shape
	P8PanelKnob8Bit wave1Ramp;
	P8PanelKnob8Bit wave1Sine;
	P8PanelKnob8Bit wave1Pulse;
	P8PanelKnob8Bit wave2Ramp;
	P8PanelKnob8Bit wave2Sine;
	P8PanelKnob8Bit wave2Pulse;
	P8PanelKnob8Bit wave3Width;
	P8PanelKnob8Bit wave3Pulse;
	
	//General
	P8PanelKnob8Bit Select;
	
protected:
private:
	volatile uint8_t flasherState;
	volatile uint8_t fastFlasherState;

};

#endif // P8PANEL_H



