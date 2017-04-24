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
//    2016/2/29: Merged with demo for segment driver
//
//**********************************************************************//
#include "P8Interface.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "Arduino.h"
#include "flagMessaging.h"
#include "proto-8Hardware.h"
#include "effect_bendvelope.h"
#include "VoltageMonitor.h"

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;
extern AudioEffectBendvelope    bendvelope1;    //xy=584,58
extern AudioEffectBendvelope    bendvelope2;    //xy=592,208
extern AudioEffectBendvelope    bendvelope3;    //xy=600,358
extern AudioEffectBendvelope    bendvelope4;    //xy=608,508

P8Interface::P8Interface( void )
{
	//Controls
	state = PInit;
	lastAttack = 10;
	lastAttackBend = 127;
	lastAttackHold = 10;
	lastDecay = 100;
	lastDecayBend = 127;
	lastSustain = 100;
	lastRelease = 100;
	lastReleaseBend = 127;
	
}

void P8Interface::reset( void )
{
	//Set explicit states
	//Set all LED off
	LEDs.clear();
	
}

//---------------------------------------------------------------------------//
//
//  To process the machine,
//    take the inputs from the system
//    process human interaction hard-codes
//    process the state machine
//    clean up and post output data
//
//---------------------------------------------------------------------------//
void P8Interface::processMachine( void )
{
	//switches.scan();
	//knobs.scan();
	update();

	//Do small machines
//	if( trackDownButton.serviceRisingEdge() )
//	{
//		if( viewingTrack > 1 )
//		{
//			viewingTrack--;
//		}
//	}
//	if( quantizeSelector.serviceChanged() )
//	{
	int8_t group1Service = 0;
	if( button1.serviceRisingEdge() )
	{
		group1Service = 1;
		group1Store = 1;
	}
	if( button2.serviceRisingEdge() )
	{
		group1Service = 2;
		group1Store = 2;
	}
	if( button3.serviceRisingEdge() )
	{
		group1Service = 3;
		group1Store = 3;
	}
	if( button4.serviceRisingEdge() )
	{
		group1Service = 4;
		group1Store = 4;
	}
	if( button5.serviceRisingEdge() )
	{
		group1Service = 5;
		group1Store = 5;
	}
	
	if( button6.serviceRisingEdge() )
	{
		led6.toggle();
	}
	if( button7.serviceRisingEdge() )
	{
		led7.toggle();
	}
	if( button8.serviceRisingEdge() )
	{
		led8.toggle();
	}
	if( button9.serviceRisingEdge() )
	{
		led9.toggle();
	}
	if( button10.serviceRisingEdge() )
	{
		led10.toggle();
	}
	if( button11.serviceRisingEdge() )
	{
		led11.toggle();
	}
	if( button12.serviceRisingEdge() )
	{
		led12.toggle();
	}
	if( button13.serviceRisingEdge() )
	{
		led13.toggle();
	}
	if( button14.serviceRisingEdge() )
	{
		led14.toggle();
	}
	int8_t group3Service = 0;
	if( button15.serviceRisingEdge() )
	{
		group3Service = 1;
	}
	if( button16.serviceRisingEdge() )
	{
		group3Service = 2;
	}
	if( group1Service )
	{
		group1Store = group1Service;
		led1.setState(LEDOFF);
		led2.setState(LEDOFF);
		led3.setState(LEDOFF);
		led4.setState(LEDOFF);
		led5.setState(LEDOFF);
		switch( group1Service )
		{
			case 1:
			led1.setState(LEDON);
			group3Service = -1;
			break;
			case 2:
			led2.setState(LEDON);
			group3Store = waveformShape1;
			group3Service = -1;
			break;
			case 3:
			led3.setState(LEDON);
			group3Store = waveformShape2;
			group3Service = -1;
			break;
			case 4:
			led4.setState(LEDON);
			group3Store = waveformShape3;
			group3Service = -1;
			break;
			case 5:
			led5.setState(LEDON);
			group3Store = waveformShape4;
			group3Service = -1;
			break;
			default:
			break;
		}
	}
	int8_t group2Service = 0;
	if( button1.serviceHoldRisingEdge() )
	{
		group2Service = 1;
	}
	if( button2.serviceHoldRisingEdge() )
	{
		group2Service = 2;
	}
	if( button3.serviceHoldRisingEdge() )
	{
		group2Service = 3;
	}
	if( button4.serviceHoldRisingEdge() )
	{
		group2Service = 4;
	}
	if( button5.serviceHoldRisingEdge() )
	{
		group2Service = 5;
	}
	if( group2Service )
	{
		switch( group2Service )
		{
			case 1:
			break;
			case 2:
			led2.setState(LEDFLASHING);
			break;
			case 3:
			led3.setState(LEDFLASHING);
			break;
			case 4:
			led4.setState(LEDFLASHING);
			break;
			case 5:
			led5.setState(LEDFLASHING);
			break;
			default:
			break;
		}
	}
	if( group3Service )
	{
		if( group3Service != -1)
		{
			group3Store = group3Service;
		}
		switch( group1Store )
		{
			case 1:
			group3Store = 0;
			break;
			case 2:
			waveformShape1 = group3Store;
			break;
			case 3:
			waveformShape2 = group3Store;
			break;
			case 4:
			waveformShape3 = group3Store;
			break;
			case 5:
			waveformShape4 = group3Store;
			break;
			default:
			break;
		}
		led15.setState(LEDOFF);
		led16.setState(LEDOFF);
		switch( group3Store )
		{
			case 1:
			led15.setState(LEDON);
			break;
			case 2:
			led16.setState(LEDON);
			break;
			default:
			break;
		}
		
	}	
	//Knobs
	uint8_t temp1;
	uint8_t temp2;
	
	temp1 = attackKnob.serviceChanged();
	if( temp1 ) debugTemp = attackKnob.getState();
	temp2 = attackBendKnob.serviceChanged();
	if( temp2 ) debugTemp = attackBendKnob.getState();
	if( temp1 || temp2 )
	{
		bendvelope1.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope2.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope3.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope4.attack( attackKnob.getState(), (int16_t)attackBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
	}
	if( holdKnob.serviceChanged() )
	{
		debugTemp = holdKnob.getState();
		bendvelope1.setAttackHold( holdKnob.getState() );
		bendvelope2.setAttackHold( holdKnob.getState() );
		bendvelope3.setAttackHold( holdKnob.getState() );
		bendvelope4.setAttackHold( holdKnob.getState() );
	}
	temp1 = decayKnob.serviceChanged();
	if( temp1 ) debugTemp = decayKnob.getState();
	temp2 = decayBendKnob.serviceChanged();
	if( temp2 ) debugTemp = decayBendKnob.getState();
	if( temp1 || temp2 )
	{
		bendvelope1.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
		bendvelope2.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
		bendvelope3.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
		bendvelope4.decay( decayKnob.getState(), ((int16_t)decayBendKnob.getState() - 127 ) * -1);// 0 to 255 for length, -128 to 127
	}
	if( sustainKnob.serviceChanged() )
	{
		debugTemp = sustainKnob.getState();
		bendvelope1.sustain( sustainKnob.getState() );// 0 to 255 for level
		bendvelope2.sustain( sustainKnob.getState() );// 0 to 255 for level
		bendvelope3.sustain( sustainKnob.getState() );// 0 to 255 for level
		bendvelope4.sustain( sustainKnob.getState() );// 0 to 255 for level
	}
	temp1 = releaseKnob.serviceChanged();
	if( temp1 ) debugTemp = releaseKnob.getState();
	temp2 = releaseBendKnob.serviceChanged();
	if( temp2 ) debugTemp = releaseBendKnob.getState();
	if( temp1 || temp2 )
	{
		bendvelope1.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope2.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope3.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
		bendvelope4.release( releaseKnob.getState(), (int16_t)releaseBendKnob.getState() - 128 );// 0 to 255 for length, -128 to 127
	}

	if( fixtureKnob.serviceChanged() )
	{
		debugTemp = fixtureKnob.getState();
	}
	LEDs.setNumber1( debugTemp );
	float tempVoltage = 0;
	float tempFactor = 0; // n * factor = 2.5
	tempFactor = 2.5 / refKnob.getState();
	tempVoltage = (float)rail18Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 0 );
	tempVoltage = (float)rail33Knob.getState() * tempFactor * 2;
	LEDs.setVoltage( tempVoltage, 3 );
	//'set' all the values
	//display1.update();
	//update();
	
	//Do main machine
	tickStateMachine();
	
	//Do pure LED operations first
	
	//System level LEDs
	//led10.setState(LEDON);
	update();
	//Panel level LEDs
	//LEDs.send();
}

void P8Interface::tickStateMachine()
{
	//***** PROCESS THE LOGIC *****//
    //Now do the states.
    PStates nextState = state;
    switch( state )
    {
    case PInit:
		nextState = PIdle;
		
		break;
	case PIdle:
		nextState = PIdle;
        break;
    default:
        nextState = PInit;
		//Serial.println("!!!DEFAULT STATE HIT!!!");
        break;
    }
	
    state = nextState;

}

void P8Interface::timersMIncrement( uint8_t inputValue )
{
	button1.buttonDebounceTimeKeeper.mIncrement(inputValue);
	button2.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button3.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button4.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button5.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button6.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button7.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button8.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button9.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button10.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button11.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button12.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button13.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button14.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button15.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	button16.buttonDebounceTimeKeeper.mIncrement(inputValue);	
	

}