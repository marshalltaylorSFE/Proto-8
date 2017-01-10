// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------

#include <Arduino.h>
#include "synth_lfo.h"
#include "utility/dspinst.h"
#include "wavegen.h"

extern "C" {
extern const uint16_t twoPowers12bit[4096];
extern const float note2bpo[129];
}

void AudioSynthLfo::update(void)
{
	audio_block_t *block, *ampModBlock, *bpoABlock, *centABlock;
	uint32_t i, ph[POLYCOUNT], inc, index, input[POLYCOUNT], ampInput;
	int32_t centInput[POLYCOUNT];
	int32_t val1, val2;
	uint32_t scale;
	uint16_t inputFractional;
	int16_t inputWhole;
	uint32_t baseFreq, powerResult, centResult;
	int32_t sampleAcumulator;

	int printstuf = 0;
	if(debugFlag)
	{
		debugFlag = 0;
		printstuf = 1;
	}
	
	if( beginHasRun == 0)
	{
		if( printstuf ) Serial.println("Boooo");
		return;
	}
//Try get all first	
	ampModBlock = receiveReadOnly(0);
	bpoABlock = receiveReadOnly(1);
	centABlock = receiveReadOnly(2);

	int8_t failedBlocks = 0;
	if (!ampModBlock) {
		release(ampModBlock);
		if( printstuf ) Serial.println("(0) failed");
		failedBlocks++;
	}
	if (!bpoABlock) {
		release(bpoABlock);
		if( printstuf ) Serial.println("(1) failed");
		failedBlocks++;
	}
	if (!centABlock) {
		release(centABlock);
		if( printstuf ) Serial.println("(2) failed");
		failedBlocks++;
	}
	
	if(failedBlocks)
	{
		//check for unreleased and return
		if(ampModBlock)release(ampModBlock);
		if(bpoABlock)release(bpoABlock);
		if(centABlock)release(centABlock);
		return;
	}
	//Need smore block handling for poly
	
	block = allocate();
	if (block) {
		for( int i = 0; i < POLYCOUNT; i++ )
		{
			ph[i] = phase_accumulator[i];
		}
		//Calculate inc sample by sample
		
		for (i=0; i < AUDIO_BLOCK_SAMPLES; i++)
		{
			sampleAcumulator = 0;
			//input and centInput needs poly handling
			input[0] = bpoABlock->data[i];  //Get incomming pitch data
			ampInput = ampModBlock->data[i] >> 2 ;
			centInput[0] = centABlock->data[i];
			
			//First
			index = ph[0] >> 24;
			val1 = waveFormPointerA[index];
			val2 = waveFormPointerA[index + 1] - val1; //delta between two samples
			scale = (ph[0] >> 16) & 0xFF; //get partial phase value as 8 bit
			val2 = (val2 * scale) >> 8; //scale val2 by scale
			val1 = (val1 + val2) * staticAmp[0] / 256; //add scaled delta to val1
			sampleAcumulator += multiply_32x32_rshift32(val1 << 16, ampInput);
			
			//Calculate the next increment value
			inputFractional = input[0] & 0x0FFF;  //Get only the RHS
			inputWhole = ( input[0] & 0xF000 ) >> 12;  //Get only the LHS (4 bits!)
			baseFreq = 0x76D;  //This is a 24 bit number ( was: 0x76D6A for normal operation
			//This number maybe should be recalculated?  What am I doing?
			baseFreq = baseFreq << (inputWhole + staticRoot[0]);
			if( printstuf ) debugSave = baseFreq;
			powerResult = ((uint64_t)baseFreq * twoPowers12bit[inputFractional]) >> 24;
			centResult = ((uint64_t)0xEDAD40 * (centInput[0] >> 0)) >> 24;
			//centResult = 0;
			baseFreq = powerResult + (baseFreq >> 8) + centResult;
			inc = baseFreq << 8;
			ph[0] += inc; //Store the new phase
			
			block->data[i] = sampleAcumulator;// >> 2; //Divide by four
		}
		if( printstuf ) Serial.println("bpoABlock->data[10] ");
		if( printstuf ) Serial.println(bpoABlock->data[10], HEX);
		for( int i = 0; i < POLYCOUNT; i++ )
		{
			phase_accumulator[i] = ph[i];
		}

		transmit(block);
		release(block);
		release(ampModBlock);
		release(bpoABlock);
		release(centABlock);
		return;
	}
	
}

void AudioSynthLfo::begin(void)
{
    WaveGenerator testWave;
	waveFormPointerA = testWave.allocateU16_257();
	waveFormPointerB = testWave.allocateU16_257();
	Serial.println("During multiOSC.begin(),");
	uint32_t address;
	Serial.print("WFPA = 0x");
	address = (uint32_t)&waveFormPointerA[0];
	Serial.println(address, HEX);
	Serial.print("WFPB = 0x");
	address = (uint32_t)&waveFormPointerB[0];
	Serial.println(address, HEX);	
    testWave.setParameters( 255, 255, 0, 0, 45 );
    testWave.writeWaveU16_257( waveFormPointerA );	
	beginHasRun = 1;
}

int16_t * AudioSynthLfo::getPointer( uint8_t oscNumber ) //Pass number 0 = OSC A, 1 = OSC B
{
	switch( oscNumber )
	{
		case 0:
		return waveFormPointerA;
		break;
		case 1:
		return waveFormPointerB;
		break;
		default:
		break;
	}
	return NULL;
}

void AudioSynthLfo::setPointer( uint8_t oscNumber, int16_t * pointerVar ) //Pass number 0 = OSC A, 1 = OSC B
{
	switch( oscNumber )
	{
		case 0:
		waveFormPointerA = pointerVar;
		break;
		case 1:
		waveFormPointerB = pointerVar;
		break;
		default:
		break;
	}
}