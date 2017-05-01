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

#include "Panel.h"
#include "PanelComponents.h"
#include "proto-8PanelComponents.h"
#include "proto-8HardwareInterfaces.h"

class P8Panel : public Panel
{
public:
	P8Panel( void );
	void PrintPanelState( void );
	
protected:
	//Bendvelope1
	FastWindowed10BitKnob bv1Attack;
	FastWindowed10BitKnob bv1AttackBend;
	FastWindowed10BitKnob bv1Hold;
	FastWindowed10BitKnob bv1Decay;
	FastWindowed10BitKnob bv1DecayBend;
	FastWindowed10BitKnob bv1Sustain;
	FastWindowed10BitKnob bv1Release;
	FastWindowed10BitKnob bv1ReleaseBend;
	FastWindowed10BitKnob bv1Select;
public:
	Led bv1Trigger;
protected:
	//Bendvelope2
	FastWindowed10BitKnob bv2Attack;
	FastWindowed10BitKnob bv2AttackBend;
	FastWindowed10BitKnob bv2Hold;
	FastWindowed10BitKnob bv2Decay;
	FastWindowed10BitKnob bv2DecayBend;
	FastWindowed10BitKnob bv2Sustain;
	FastWindowed10BitKnob bv2Release;
	FastWindowed10BitKnob bv2ReleaseBend;
	FastWindowed10BitKnob bv2Select;
public:
	Led bv2Trigger;
protected:

	//Bus
	Windowed10BitKnob bus1Amp;
	Windowed10BitKnob bus1Offset;
	Button bus1SrcPick;
	Button bus1DestPick;
	Led bus1SrcLed;
	Led bus1DestLed;
	
	Windowed10BitKnob bus2Amp;
	Windowed10BitKnob bus2Offset;
	Button bus2SrcPick;
	Button bus2DestPick;
	Led bus2SrcLed;
	Led bus2DestLed;

	Windowed10BitKnob bus3Amp;
	Windowed10BitKnob bus3Offset;
	Button bus3SrcPick;
	Button bus3DestPick;
	Led bus3SrcLed;
	Led bus3DestLed;

	Windowed10BitKnob bus4Amp;
	Windowed10BitKnob bus4Offset;
	Button bus4SrcPick;
	Button bus4DestPick;
	Led bus4SrcLed;
	Led bus4DestLed;

	Windowed10BitKnob bus5Amp;
	Windowed10BitKnob bus5Offset;
	Button bus5SrcPick;
	Button bus5DestPick;
	Led bus5SrcLed;
	Led bus5DestLed;
	
	Led modSrcLed0;
	Led modSrcLed1;
	Led modSrcLed2;
	Led modSrcLed3;
	Led modSrcLed4;
	Led modSrcLed5;
	Led modSrcLed6;
	Led modSrcLed7;
	Led modSrcLed8;
	Led modSrcLed9;
	Led modSrcLed10;
	Led modSrcLed11;
	Led modSrcLed12;
	Led modSrcLed13;
	Led modSrcLed14;
	
	Led modDestLed0;
	Led modDestLed1;
	Led modDestLed2;
	Led modDestLed3;
	Led modDestLed4;
	Led modDestLed5;
	Led modDestLed6;
	Led modDestLed7;
	Led modDestLed8;
	Led modDestLed9;
	Led modDestLed10;
	Led modDestLed11;
	Led modDestLed12;
	Led modDestLed13;
	Led modDestLed14;
	
	//Master
	FastWindowed10BitKnob masterCoarseTune;
	FastWindowed10BitKnob masterFineTune;
	FastWindowed10BitKnob masterVolume;
	
	//LFO1
	FastWindowed10BitKnob lfo1Freq;
	Button lfo1Shape;
	Led lfo1Led1;
	Led lfo1Led2;
	Led lfo1Led3;
	
	//LFO2
	FastWindowed10BitKnob lfo2Freq;
	Button lfo2Shape;
	Led lfo2Led1;
	Led lfo2Led2;
	Led lfo2Led3;	
	
	//OSCA
	Windowed10BitKnob oscAPitch;
	Selector oscAOctave;
	//Led oscASyncLed;
	Button oscASync;
	Windowed10BitKnob oscACent;
	Button oscAShape;
	Led oscALed1;
	Led oscALed2;
	Led oscALed3;
	FastWindowed10BitKnob oscAPreAmp;
	
	//OSCB
	Windowed10BitKnob oscBPitch;
	Selector oscBOctave;
	Led oscBSyncLed;
	Button oscBSync;
	Windowed10BitKnob oscBCent;
	Button oscBShape;
	Led oscBLed1;
	Led oscBLed2;
	Led oscBLed3;
	FastWindowed10BitKnob oscBPreAmp;

	//OSCC
	FastWindowed10BitKnob oscCPitch;
	Selector oscCOctave;
	Led oscCSyncLed;
	Button oscCSync;
	FastWindowed10BitKnob oscCCent;
	Button oscCShape;
	Led oscCLed1;
	Led oscCLed2;
	Led oscCLed3;
	FastWindowed10BitKnob oscCPreAmp;

	//OSCD
	FastWindowed10BitKnob oscDPitch;
	Selector oscDOctave;
	Led oscDSyncLed;
	Button oscDSync;
	FastWindowed10BitKnob oscDCent;
	Button oscDShape;
	Led oscDLed1;
	Led oscDLed2;
	Led oscDLed3;
	FastWindowed10BitKnob oscDPreAmp;
	
	//Wave Shape
	FastWindowed10BitKnob wave1Ramp;
	FastWindowed10BitKnob wave1Sine;
	FastWindowed10BitKnob wave1Pulse;
	FastWindowed10BitKnob wave2Ramp;
	FastWindowed10BitKnob wave2Sine;
	FastWindowed10BitKnob wave2Pulse;
	FastWindowed10BitKnob wave3Width;
	FastWindowed10BitKnob wave3Pulse;
	
	//General
	Selector Select;

};

#endif // P8PANEL_H



