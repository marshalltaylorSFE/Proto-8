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
#include "P8Panel.h"
#include "Arduino.h"

//This is where PanelComponents are joined to form the custom panel


P8Panel::P8Panel( void )
{
	flasherState = 0;
	fastFlasherState = 0;
}

void P8Panel::init( void )
{
	//Bendvelope1
	bv1Attack.init(25);
	bv1AttackBend.init(24);
	bv1Hold.init(26);
	bv1Decay.init(28);
	bv1DecayBend.init(27);
	bv1Sustain.init(29);
	bv1Release.init(30);
	bv1ReleaseBend.init(31);
	//bv1Select.init(32, 255, 0 ); //With max and min ranges
	bv1Select.init(32);
	bv1Trigger.init(41, &flasherState, &fastFlasherState);
	
	//Bendvelope2
	bv2Attack.init(16);
	bv2AttackBend.init(15);
	bv2Hold.init(17);
	bv2Decay.init(19);
	bv2DecayBend.init(18);
	bv2Sustain.init(20);
	bv2Release.init(21);
	bv2ReleaseBend.init(22);
	//bv2Select.init(23, 255, 0 ); //With max and min ranges
	bv2Select.init(23);
	bv2Trigger.init(42, &flasherState, &fastFlasherState);
	
	//Bus
	bus1Amp.init(13);
	bus1Offset.init(14);
	bus1SrcPick.init(5,1);
	bus1DestPick.init(4,1);
	bus1SrcLed.init(15, &flasherState, &fastFlasherState);
	bus1DestLed.init(25, &flasherState, &fastFlasherState);
	
	bus2Amp.init(11);
	bus2Offset.init(12);
	bus2SrcPick.init(5,2);
	bus2DestPick.init(4,2);
	bus2SrcLed.init(14, &flasherState, &fastFlasherState);
	bus2DestLed.init(24, &flasherState, &fastFlasherState);

	bus3Amp.init(9);
	bus3Offset.init(10);
	bus3SrcPick.init(5,3);
	bus3DestPick.init(4,3);
	bus3SrcLed.init(13, &flasherState, &fastFlasherState);
	bus3DestLed.init(23, &flasherState, &fastFlasherState);

	bus4Amp.init(7);
	bus4Offset.init(8);
	bus4SrcPick.init(5,4);
	bus4DestPick.init(4,4);
	bus4SrcLed.init(12, &flasherState, &fastFlasherState);
	bus4DestLed.init(22, &flasherState, &fastFlasherState);

	bus5Amp.init(5);
	bus5Offset.init(6);
	bus5SrcPick.init(6,1); //Both want 6,1 ... Need to be rewired!  But bus 5 is last to be implemented...
	bus5DestPick.init(6,1); //Both want 6,1 ... Need to be rewired!  But bus 5 is last to be implemented...
	bus5SrcLed.init(11, &flasherState, &fastFlasherState);
	bus5DestLed.init(21, &flasherState, &fastFlasherState);
	
	modSrcLed0.init(16, &flasherState, &fastFlasherState);
	modSrcLed1.init(17, &flasherState, &fastFlasherState);
	modSrcLed2.init(18, &flasherState, &fastFlasherState);
	modSrcLed3.init(19, &flasherState, &fastFlasherState);
	modSrcLed4.init(20, &flasherState, &fastFlasherState);
	modSrcLed5.init(1, &flasherState, &fastFlasherState);
	modSrcLed6.init(2, &flasherState, &fastFlasherState);
	modSrcLed7.init(3, &flasherState, &fastFlasherState);
	modSrcLed8.init(4, &flasherState, &fastFlasherState);
	modSrcLed9.init(5, &flasherState, &fastFlasherState);
	modSrcLed10.init(6, &flasherState, &fastFlasherState);
	modSrcLed11.init(7, &flasherState, &fastFlasherState);
	modSrcLed12.init(8, &flasherState, &fastFlasherState);
	modSrcLed13.init(9, &flasherState, &fastFlasherState);
	modSrcLed14.init(10, &flasherState, &fastFlasherState);
	
	modDestLed0.init(26, &flasherState, &fastFlasherState);
	modDestLed1.init(27, &flasherState, &fastFlasherState);
	modDestLed2.init(28, &flasherState, &fastFlasherState);
	modDestLed3.init(29, &flasherState, &fastFlasherState);
	modDestLed4.init(30, &flasherState, &fastFlasherState);
	modDestLed5.init(31, &flasherState, &fastFlasherState);
	modDestLed6.init(32, &flasherState, &fastFlasherState);
	modDestLed7.init(33, &flasherState, &fastFlasherState);
	modDestLed8.init(34, &flasherState, &fastFlasherState);
	modDestLed9.init(35, &flasherState, &fastFlasherState);
	modDestLed10.init(36, &flasherState, &fastFlasherState);
	modDestLed11.init(37, &flasherState, &fastFlasherState);
	modDestLed12.init(38, &flasherState, &fastFlasherState);
	modDestLed13.init(39, &flasherState, &fastFlasherState);
	modDestLed14.init(40, &flasherState, &fastFlasherState);
	
	//Master
	masterCoarseTune.init(62);
	masterFineTune.init(63);
	masterVolume.init(64);
	
	//LFO1
	lfo1Freq.init(61);
	lfo1Shape.init(1,3);
	lfo1Led1.init(62, &flasherState, &fastFlasherState);
	lfo1Led2.init(63, &flasherState, &fastFlasherState);
	lfo1Led3.init(64, &flasherState, &fastFlasherState);
	
	//LFO2
	lfo2Freq.init(60);
	lfo2Shape.init(1,4);
	lfo2Led1.init(59, &flasherState, &fastFlasherState);
	lfo2Led2.init(60, &flasherState, &fastFlasherState);
	lfo2Led3.init(61, &flasherState, &fastFlasherState);	
	
	//OSCA
	oscAPitch.init(56);
	oscAOctave.init(57, 185, 71, 4); //With max, min, points
	//oscASyncLed.init(, &flasherState, &fastFlasherState);
	oscASync.init(3,1);
	oscACent.init(58);
	oscAShape.init(2,1);
	oscALed1.init(56, &flasherState, &fastFlasherState);
	oscALed2.init(57, &flasherState, &fastFlasherState);
	oscALed3.init(58, &flasherState, &fastFlasherState);
	oscAPreAmp.init(59);
	
	//OSCB
	oscBPitch.init(52);
	oscBOctave.init(53, 185, 71, 4); //With max, min, points
	oscBSyncLed.init(46, &flasherState, &fastFlasherState);
	oscBSync.init(3,2);
	oscBCent.init(54);
	oscBShape.init(2,2);
	oscBLed1.init(53, &flasherState, &fastFlasherState);
	oscBLed2.init(54, &flasherState, &fastFlasherState);
	oscBLed3.init(55, &flasherState, &fastFlasherState);
	oscBPreAmp.init(55);

	//OSCC
	oscCPitch.init(48);
	oscCOctave.init(49, 185, 71, 4); //With max, min, points
	oscCSyncLed.init(45, &flasherState, &fastFlasherState);
	oscCSync.init(3,3);
	oscCCent.init(50);
	oscCShape.init(2,3);
	oscCLed1.init(50, &flasherState, &fastFlasherState);
	oscCLed2.init(51, &flasherState, &fastFlasherState);
	oscCLed3.init(52, &flasherState, &fastFlasherState);
	oscCPreAmp.init(51);

	//OSCD
	oscDPitch.init(44);
	oscDOctave.init(45, 185, 71, 4); //With max, min, points
	oscDSyncLed.init(44, &flasherState, &fastFlasherState);
	oscDSync.init(3,4);
	oscDCent.init(46);
	oscDShape.init(2,4);
	oscDLed1.init(47, &flasherState, &fastFlasherState);
	oscDLed2.init(48, &flasherState, &fastFlasherState);
	oscDLed3.init(49, &flasherState, &fastFlasherState);
	oscDPreAmp.init(47);
	
	//Wave Shape
	wave1Ramp.init(39);
	wave1Sine.init(36);
	wave1Pulse.init(33);
	wave2Ramp.init(40);
	wave2Sine.init(37);
	wave2Pulse.init(34);
	wave3Width.init(38);
	wave3Pulse.init(35);
	
	//General
	Select.init(43);

 	flasherState = 0;
	fastFlasherState = 0;
}

void P8Panel::update( void )
{
	//Bendvelope1
	bv1Attack.update();
	bv1AttackBend.update();
	bv1Hold.update();
	bv1Decay.update();
	bv1DecayBend.update();
	bv1Sustain.update();
	bv1Release.update();
	bv1ReleaseBend.update();
	bv1Select.update();
	bv1Trigger.update();
	
	//Bendvelope2
	bv2Attack.update();
	bv2AttackBend.update();
	bv2Hold.update();
	bv2Decay.update();
	bv2DecayBend.update();
	bv2Sustain.update();
	bv2Release.update();
	bv2ReleaseBend.update();
	bv2Select.update();
	bv2Trigger.update();
	
	//Bus
	bus1Amp.update();
	bus1Offset.update();
	bus1SrcPick.update();
	bus1DestPick.update();
	bus1SrcLed.update();
	bus1DestLed.update();
	
	bus2Amp.update();
	bus2Offset.update();
	bus2SrcPick.update();
	bus2DestPick.update();
	bus2SrcLed.update();
	bus2DestLed.update();

	bus3Amp.update();
	bus3Offset.update();
	bus3SrcPick.update();
	bus3DestPick.update();
	bus3SrcLed.update();
	bus3DestLed.update();

	bus4Amp.update();
	bus4Offset.update();
	bus4SrcPick.update();
	bus4DestPick.update();
	bus4SrcLed.update();
	bus4DestLed.update();

	bus5Amp.update();
	bus5Offset.update();
	bus5SrcPick.update();
	bus5DestPick.update();
	bus5SrcLed.update();
	bus5DestLed.update();
	
	modSrcLed0.update();
	modSrcLed1.update();
	modSrcLed2.update();
	modSrcLed3.update();
	modSrcLed4.update();
	modSrcLed5.update();
	modSrcLed6.update();
	modSrcLed7.update();
	modSrcLed8.update();
	modSrcLed9.update();
	modSrcLed10.update();
	modSrcLed11.update();
	modSrcLed12.update();
	modSrcLed13.update();
	modSrcLed14.update();
	
	modDestLed0.update();
	modDestLed1.update();
	modDestLed2.update();
	modDestLed3.update();
	modDestLed4.update();
	modDestLed5.update();
	modDestLed6.update();
	modDestLed7.update();
	modDestLed8.update();
	modDestLed9.update();
	modDestLed10.update();
	modDestLed11.update();
	modDestLed12.update();
	modDestLed13.update();
	modDestLed14.update();
	
	//Master
	masterCoarseTune.update();
	masterFineTune.update();
	masterVolume.update();
	
	//LFO1
	lfo1Freq.update();
	lfo1Shape.update();
	lfo1Led1.update();
	lfo1Led2.update();
	lfo1Led3.update();
	
	//LFO2
	lfo2Freq.update();
	lfo2Shape.update();
	lfo2Led1.update();
	lfo2Led2.update();
	lfo2Led3.update();	
	
	//OSCA
	oscAPitch.update();
	oscAOctave.update();
	//oscASyncLed.update();
	oscASync.update();
	oscACent.update();
	oscAShape.update();
	oscALed1.update();
	oscALed2.update();
	oscALed3.update();
	oscAPreAmp.update();
	
	//OSCB
	oscBPitch.update();
	oscBOctave.update();
	oscBSyncLed.update();
	oscBSync.update();
	oscBCent.update();
	oscBShape.update();
	oscBLed1.update();
	oscBLed2.update();
	oscBLed3.update();
	oscBPreAmp.update();

	//OSCC
	oscCPitch.update();
	oscCOctave.update();
	oscCSyncLed.update();
	oscCSync.update();
	oscCCent.update();
	oscCShape.update();
	oscCLed1.update();
	oscCLed2.update();
	oscCLed3.update();
	oscCPreAmp.update();

	//OSCD
	oscDPitch.update();
	oscDOctave.update();
	oscDSyncLed.update();
	oscDSync.update();
	oscDCent.update();
	oscDShape.update();
	oscDLed1.update();
	oscDLed2.update();
	oscDLed3.update();
	oscDPreAmp.update();
	
	//Wave Shape
	wave1Ramp.update();
	wave1Sine.update();
	wave1Pulse.update();
	wave2Ramp.update();
	wave2Sine.update();
	wave2Pulse.update();
	wave3Width.update();
	wave3Pulse.update();
	
	//General
	Select.update();
	
}

void P8Panel::toggleFlasherState( void )
{
	flasherState ^= 0x01;
}

void P8Panel::toggleFastFlasherState( void )
{
	fastFlasherState ^= 0x01;
}