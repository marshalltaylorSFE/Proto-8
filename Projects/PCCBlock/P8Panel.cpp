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
	
	//Master
	masterCoarseTune.init(62);
	masterFineTune.init(63);
	masterVolume.init(64);
	
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

	
	//General
	Select.init(43);

 	flasherState = 0;
	fastFlasherState = 0;
}

void P8Panel::update( void )
{
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