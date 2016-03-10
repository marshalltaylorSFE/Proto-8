#include "Panel.h"

//This is where PanelComponents are joined to form the custom panel

#define rxLedPin 13


Panel::Panel( void )
{

	flasherState = 0;
	fastFlasherState = 0;
}

void Panel::init( void )
{
	rxLed.init(rxLedPin, 0, &flasherState, &fastFlasherState);

 	flasherState = 0;
	fastFlasherState = 0;
}

void Panel::update( void )
{
	rxLed.update();
}

void Panel::toggleFlasherState( void )
{
	flasherState ^= 0x01;
}

void Panel::toggleFastFlasherState( void )
{
	fastFlasherState ^= 0x01;
}