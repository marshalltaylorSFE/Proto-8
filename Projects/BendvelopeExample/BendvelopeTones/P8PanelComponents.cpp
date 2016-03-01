//**********************************************************************//
//
//  MIT License: http://opensource.org/licenses/MIT
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2015/10/08: Beta Release
//    2016/2/24: Forked to 'P8' set
//    2016/2/29: LEDs wrapped by VoltageMonitor + hysteresis fix
//
//**********************************************************************//
#include "P8PanelComponents.h"
//#include "timeKeeper.h"
#include "Arduino.h"
#include "proto-8Hardware.h"
#include "VoltageMonitor.h"

extern VoltageMonitor LEDs;
extern AnalogMuxTree knobs;
extern SwitchMatrix switches;

//---Switch------------------------------------------------------
P8PanelSwitch::P8PanelSwitch( void )
{

}

void P8PanelSwitch::init( uint8_t posColInput, uint8_t posRowInput )
{
	posColNumber = posColInput;
	posRowNumber = posRowInput - 1; // range: 0-3

}

void P8PanelSwitch::update( void )
{
	uint16_t numTemp = 0;
	numTemp = (posRowNumber * 16) + posColNumber;
	uint8_t tempState = switches.fetch( numTemp );
	tempState ^= invert;
	if(( state.getFlag() != tempState ) && ( SwitchDebounceTimeKeeper.mGet() > 200 ))
	{
		if( tempState == 1 )
		{
			state.setFlag();
		}
		else
		{
			state.clearFlag();
		}
		SwitchDebounceTimeKeeper.mClear();
	}
}

//---Knob--------------------------------------------------------
P8PanelKnob8Bit::P8PanelKnob8Bit( void )
{
	lastState = 0;
}

void P8PanelKnob8Bit::init( uint8_t posInput )
{
  posNumber = posInput;
  update();
  //force newData high in case knob starts on last value
  newData = 1;
}

void P8PanelKnob8Bit::update( void )
{
	uint16_t tempState = knobs.fetch( posNumber ) >> 2;
	int8_t tempSlope = 0;
	state = tempState;
	int8_t histDirTemp = 0;
	if( state > lastState )
	{
		tempSlope = 1;
		if( lastSlope == 1 ) histDirTemp = 1;
	}
	else if( state < lastState )
	{
		tempSlope = -1;
		if( lastSlope == -1 ) histDirTemp = -1;
	}
	if( tempSlope != 0 )
	{
		if( state > lastState + hysteresis || histDirTemp == 1)
		{
			newData = 1;
			lastState = state;
			lastSlope = tempSlope;
		}
		if( state < lastState - hysteresis || histDirTemp == -1 )
		{
			newData = 1;
			lastState = state;
			lastSlope = tempSlope;
		}

	}
}

uint8_t P8PanelKnob8Bit::getState( void )
{
  newData = 0;

  return state;
}

uint8_t P8PanelKnob8Bit::serviceChanged( void )
{
	return newData;
}
//---Button------------------------------------------------------
P8PanelButton::P8PanelButton( void )
{
	beingHeld = 0;
	risingEdgeFlag = 0;
	fallingEdgeFlag = 0;
	holdRisingEdgeFlag = 0;
	holdFallingEdgeFlag = 0; 
	
}

void P8PanelButton::init( uint8_t posColInput, uint8_t posRowInput )
{
	posColNumber = posColInput;
	posRowNumber = posRowInput - 1; // range: 0-3

}

//This is the intended operation:
// Button is pressed. If it has been long enough since last movement:
//   update newData
//   clear timer
// If This has already been done, check for button held.  If so,
//   update newData
//   clear timer
void P8PanelButton::update( void )
{
	uint8_t freshData;
	uint16_t numTemp = 0;
	numTemp = (posRowNumber << 4) + posColNumber;
	freshData = switches.fetch( numTemp );

	buttonState_t nextState = state;
	switch( state )
	{
	case BUTTONOFF: //Last state was BUTTONOFF
		if(( freshData == 1 ) && ( buttonDebounceTimeKeeper.mGet() > 150 ))
		{
			//Start the timer
			buttonDebounceTimeKeeper.mClear();
			nextState = BUTTONON;
			risingEdgeFlag = 1;
		}
		else
		{
			nextState = BUTTONOFF;
		}
		break;
	case BUTTONON: //Last state was BUTTONON
		if( freshData == 1 )
		{
			if( buttonDebounceTimeKeeper.mGet() > 1000 )
			{
				nextState = BUTTONHOLD;
				holdRisingEdgeFlag = 1;
			}
		}
		//No break;, do buttonhold's state too
	case BUTTONHOLD: //In the process of holding
		if( freshData == 0 )
		{
			buttonDebounceTimeKeeper.mClear();
			nextState = BUTTONOFF;
		}
		break;
	default:
		break;
	}
	
	state = nextState;

}

buttonState_t P8PanelButton::getState( void )
{
	return state;
}

uint8_t P8PanelButton::serviceRisingEdge( void )
{
	uint8_t returnVar = 0;
	if( risingEdgeFlag == 1 )
	{
		risingEdgeFlag = 0;
		returnVar = 1;

	}
	
	return returnVar;
}

uint8_t P8PanelButton::serviceFallingEdge( void )
{
	uint8_t returnVar = 0;
	if( fallingEdgeFlag == 1 )
	{
		fallingEdgeFlag = 0;
		returnVar = 1;
	}
	
	return returnVar;
}

uint8_t P8PanelButton::serviceHoldRisingEdge( void )
{
	uint8_t returnVar = 0;
	if( holdRisingEdgeFlag == 1 )
	{
		holdRisingEdgeFlag = 0;
		returnVar = 1;
	}
	
	return returnVar;
}

uint8_t P8PanelButton::serviceHoldFallingEdge( void )
{
	uint8_t returnVar = 0;
	if( holdFallingEdgeFlag == 1 )
	{
		holdFallingEdgeFlag = 0;
		returnVar = 1;
	}
	
	return returnVar;
}

//---Led---------------------------------------------------------
P8PanelLed::P8PanelLed( void )
{
	state = LEDOFF;
}

void P8PanelLed::init( uint8_t posInput )
{
	posNumber = posInput;
	update();
}

void P8PanelLed::init( uint8_t posInput, volatile uint8_t * volatile flasherAddress, volatile uint8_t * volatile fastFlasherAddress )
{
	flasherState = flasherAddress;
	fastFlasherState = fastFlasherAddress;

	init( posInput ); //Do regular init, plus:
	
}

void P8PanelLed::update( void )
{
	uint8_t outputValue = 0;
	switch(state)
	{
	case LEDON:
		outputValue = 1;
		break;
	case LEDFLASHING:
		outputValue = *flasherState;
		break;
	case LEDFLASHINGFAST:
		outputValue = *fastFlasherState;
		break;
	default:
	case LEDOFF:
		outputValue = 0;
		break;
	} 
	LEDs.store(posNumber, outputValue);

}

ledState_t P8PanelLed::getState( void )
{
	return state;

}

void P8PanelLed::setState( ledState_t inputValue )
{
	state = inputValue;

}

void P8PanelLed::toggle( void )
{
	switch(state)
	{
	case LEDON:
		state = LEDOFF;
		break;
	case LEDOFF:
		state = LEDON;
		break;
	default:
		break;
	}
}



//---Selector----------------------------------------------------
P8PanelSelector::P8PanelSelector( void )
{
	changedFlag = 0;
	points = 10;
}

P8PanelSelector::~P8PanelSelector( void )
{
	delete[] thresholds;
}
// 8 bit resolution on the ADC should be fine.  Right shift on analogRead
void P8PanelSelector::init( uint8_t posInput, uint8_t maxInput, uint8_t minInput, uint8_t pointsInput )
{
	if( pointsInput < 2 )
	{
		points = 2;
	}
	else
	{
		points = pointsInput - 1; //( by (n-1) not n )
	}
	thresholds = new uint8_t[points];

	posNumber = posInput;
	pinMode( posNumber, INPUT );
	//Set up the ranges
	uint8_t stepHeight = ( maxInput - minInput ) / points;
	thresholds[0] = minInput + ( stepHeight / 2 );
	int i;
	for( i = 1; i < points; i++ )
	{
		thresholds[i] = thresholds[i - 1] + stepHeight;
	
	}
	update();
	//force changedFlag high in case knob starts on last value
	//changedFlag = 1;
}

void P8PanelSelector::init( uint8_t posInput, uint8_t maxInput, uint8_t minInput )
{
	init( posInput, maxInput, minInput, 10 );
}

void P8PanelSelector::update( void )
{
	uint8_t freshData = (analogRead( posNumber )) >> 2;  //Now 8 bits
	uint8_t tempState = 0;
	//Seek the position
	int i;
	for( i = 0; i < points; i++ )
	{
		if( freshData > thresholds[i] )
		{
			tempState = i + 1; //It's this or higher
		}
	}
	//Check if new
	if( state != tempState )
	{
		state = tempState;
		changedFlag = 1;
	}
}

uint8_t P8PanelSelector::getState( void )
{
	return state;
}

uint8_t P8PanelSelector::serviceChanged( void )
{
	uint8_t returnVar = 0;
	if( changedFlag == 1 )
	{
		changedFlag = 0;
		returnVar = 1;
	}
	
	return returnVar;
}

