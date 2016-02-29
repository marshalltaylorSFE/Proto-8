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
//
//**********************************************************************//
#include "P8Interface.h"
#include "P8PanelComponents.h"
#include "P8Panel.h"
#include "Arduino.h"
#include "flagMessaging.h"
#include "proto-8Hardware.h"
#include "effect_bendvelope.h"

extern LEDShiftRegister LEDs;
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
	if( button1.serviceRisingEdge() )
	{
		led1.toggle();
	}
	if( button2.serviceRisingEdge() )
	{
		led2.toggle();
	}
	if( button3.serviceRisingEdge() )
	{
		led3.toggle();
	}
	if( button4.serviceRisingEdge() )
	{
		led4.toggle();
	}
	if( button5.serviceRisingEdge() )
	{
		led5.toggle();
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
	if( button15.serviceRisingEdge() )
	{
		led15.toggle();
	}
	if( button16.serviceRisingEdge() )
	{
		led16.toggle();
	}
	if( fixtureKnob.serviceChanged() )
	{
		//LEDs.store( fixtureKnob.getState() + 1, 1 );
		//LEDs.store( attackBendKnob.getState() + 1, 0 );
		display1.setNumber1( fixtureKnob.getState() );
		//Serial.println( fixtureKnob.getState() );
	}
	//if( attackKnob.serviceChanged() || attackBendKnob.serviceChanged()  )
	//{
	//	bendvelope1.attack( attackKnob.getState(), attackBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope2.attack( attackKnob.getState(), attackBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope3.attack( attackKnob.getState(), attackBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope4.attack( attackKnob.getState(), attackBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//}
	//if( holdKnob.serviceChanged() )
	//{
	//	bendvelope1.setAttackHold( holdKnob.getState() );
	//	bendvelope2.setAttackHold( holdKnob.getState() );
	//	bendvelope3.setAttackHold( holdKnob.getState() );
	//	bendvelope4.setAttackHold( holdKnob.getState() );
	//}
	//if( decayKnob.serviceChanged() || decayBendKnob.serviceChanged() )
	//{
	//	bendvelope1.decay( decayKnob.getState(), decayBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope2.decay( decayKnob.getState(), decayBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope3.decay( decayKnob.getState(), decayBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope4.decay( decayKnob.getState(), decayBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//}
	//if( sustainKnob.serviceChanged() )
	//{
	//	bendvelope1.sustain( sustainKnob.getState() );// 0 to 255 for level
	//	bendvelope2.sustain( sustainKnob.getState() );// 0 to 255 for level
	//	bendvelope3.sustain( sustainKnob.getState() );// 0 to 255 for level
	//	bendvelope4.sustain( sustainKnob.getState() );// 0 to 255 for level
	//}
	//if( releaseKnob.serviceChanged() || releaseBendKnob.serviceChanged() )
	//{
	//	bendvelope1.release( releaseKnob.getState(), releaseBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope2.release( releaseKnob.getState(), releaseBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope3.release( releaseKnob.getState(), releaseBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//	bendvelope4.release( releaseKnob.getState(), releaseBendKnob.getState() );// 0 to 255 for length, -128 to 127
	//}

	//'set' all the values
	display1.update();
	
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

extern P8Interface p8hid;

HpSeg::HpSeg( void )
{
	scanDigit = 1;
	number1 = 0;
	
}

void HpSeg::update( void )
{
	scanDigit++;
	if( scanDigit > 9 )
	{
		scanDigit = 1;
	}
	p8hid.hpD1.setState( LEDON );
	p8hid.hpD2.setState( LEDON );
	p8hid.hpD3.setState( LEDON );
	p8hid.hpD4.setState( LEDON );
	p8hid.hpD5.setState( LEDON );
	p8hid.hpD6.setState( LEDON );
	p8hid.hpD7.setState( LEDON );
	p8hid.hpD8.setState( LEDON );
	p8hid.hpD9.setState( LEDON );
	p8hid.hpA.setState( LEDOFF );
	p8hid.hpB.setState( LEDOFF );
	p8hid.hpC.setState( LEDOFF );
	p8hid.hpD.setState( LEDOFF );
	p8hid.hpE.setState( LEDOFF );
	p8hid.hpF.setState( LEDOFF );
	p8hid.hpG.setState( LEDOFF );
	p8hid.hpDP.setState( LEDOFF );
	switch( scanDigit )
	{
		case 1:
		p8hid.hpD1.setState( LEDOFF );
		break;
		case 2:
		p8hid.hpD2.setState( LEDOFF );
		break;
		case 3:
		p8hid.hpD3.setState( LEDOFF );
		break;
		case 4:
		p8hid.hpD4.setState( LEDOFF );
		break;
		case 5:
		p8hid.hpD5.setState( LEDOFF );
		break;
		case 6:
		p8hid.hpD6.setState( LEDOFF );
		break;
		case 7:
		p8hid.hpD7.setState( LEDOFF );
		break;
		case 8:
		p8hid.hpD8.setState( LEDOFF );
		break;
		case 9:
		p8hid.hpD9.setState( LEDOFF );
		break;
		default:
		break;
	}
	if( dispBuffer[scanDigit - 1] & 0x01 ) p8hid.hpA.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x02 ) p8hid.hpF.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x04 ) p8hid.hpG.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x08 ) p8hid.hpE.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x10 ) p8hid.hpD.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x20 ) p8hid.hpC.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x40 ) p8hid.hpB.setState( LEDON );
	if( dispBuffer[scanDigit - 1] & 0x80 ) p8hid.hpDP.setState( LEDON );
}

void HpSeg::setNumber1( uint16_t inputVal )
{
	uint16_t inputTemp = inputVal;
	uint16_t mathTemp = 0;
	for( int i = 0; i < 9; i++ )
	{
		mathTemp = inputTemp%10;
		if(( inputTemp > 0 )||( i == 0 ))
		{
			dispBuffer[8 - i] = digitsLUT[mathTemp];
		}
		else
		{
			dispBuffer[8 - i] = digitsLUT[10];
		}
		inputTemp /= 10;
	}
}
