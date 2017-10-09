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
	
protected:
	//Bendvelope1
	FastWindowed10BitKnob bv1Attack;
	FastWindowed10BitKnob bv1AttackBend;
	FastWindowed10BitKnob bv1Hold;
	FastWindowed10BitKnob bv1Decay;
	FastWindowed10BitKnob bv1DecayBend;
	FastWindowed10BitKnob bv1Sustain;
	Windowed10BitKnob bv1Release;
	FastWindowed10BitKnob bv1ReleaseBend;
	FastWindowed10BitKnob bv1Select;
public:
	Led bv1Trigger;
protected:

	//OSC
	Windowed10BitKnob oscPitch;
	Selector oscOctave;
	Led oscOptionLed;
	Led miscLed;
	Button oscOption;
	Button oscShape;
	Led oscLed1;
	Led oscLed2;
	Led oscLed3;
	FastWindowed10BitKnob oscPreAmp;

	//General
	FastWindowed10BitKnob env2Attack;
	FastWindowed10BitKnob env2Decay;
	FastWindowed10BitKnob param1Knob;
	FastWindowed10BitKnob param2Knob;

	Selector tone;
	Selector effect;

};

#endif // P8PANEL_H



