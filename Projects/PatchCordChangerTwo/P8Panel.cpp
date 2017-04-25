//**********************************************************************//
//
//  Panel
//
//  Map pin locations to those on your panel.
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
#include "Arduino.h"
#include "P8Panel.h"
#include "panelComponents.h"
#include "proto-8PanelComponents.h"
#include "HardwareInterfaces.h"
#include "flagMessaging.h"

//Hardware for the suitcase panel
//#define BUTTON_1_PIN 5,1
//#define BUTTON_2_PIN 4,1
//#define LED_1_PIN 16
//#define LED_2_PIN 17
//#define LED_3_PIN 18
//#define LED_4_PIN 26
//#define LED_5_PIN 27
//#define KNOB_1_PIN 62

//Hardware for the test fixture
#define BUTTON_1_PIN 1,1
#define BUTTON_2_PIN 1,2
#define LED_1_PIN 16
#define LED_2_PIN 15
#define LED_3_PIN 14
#define LED_4_PIN 13
#define LED_5_PIN 12
#define KNOB_1_PIN 64

//This is where PanelComponents are joined to form the custom panel
P8Panel::P8Panel( void )
{
	filterSelectButton.setHardware(new Proto8DigitalIn( BUTTON_1_PIN ), 0);
	add( &filterSelectButton );
	channelSelectButton.setHardware(new Proto8DigitalIn( BUTTON_2_PIN ), 0);
	add( &channelSelectButton );
	
	lowPassLed.setHardware(new Proto8DigitalOut( LED_1_PIN ), 0);
	bandPassLed.setHardware(new Proto8DigitalOut( LED_2_PIN ), 0);
	highPassLed.setHardware(new Proto8DigitalOut( LED_3_PIN ), 0);
	add( &lowPassLed );
	add( &bandPassLed );
	add( &highPassLed );
	
	leftActiveLed.setHardware(new Proto8DigitalOut( LED_4_PIN ), 0);
	rightActiveLed.setHardware(new Proto8DigitalOut( LED_5_PIN ), 0);
	add( &leftActiveLed );
	add( &rightActiveLed );
	
	//Master
	masterVolume.setHardware(new Proto8AnalogIn( KNOB_1_PIN ));
	add( &masterVolume );
}