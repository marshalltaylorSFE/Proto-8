//**********************************************************************//
//
//  Panel
//
//  Contains the panelComponents memory elements
//
//  Written by:  Marshall Taylor
//  Changelog (YYYY/MM/DD):
//    2017/4/24: Converted to uCModules 2.0 interface
//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
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

	Button filterSelectButton;
	Button channelSelectButton;
	
	Led lowPassLed;
	Led bandPassLed;
	Led highPassLed;
	
	Led leftActiveLed;
	Led rightActiveLed;
	
	FastWindowed10BitKnob masterVolume;
	

};

#endif // P8PANEL_H



