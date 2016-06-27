/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "synth_multiosc.h"
#include "utility/dspinst.h"
#include "wavegen.h"

// bitPerOctaveLUTs.c
extern "C" {
extern const uint16_t twoPowers12bit[4096];
extern const float note2bpo[129];
}
// data_waveforms.c
extern "C" {
extern const int16_t AudioWaveformSine[257];
}


void AudioSynthMultiOsc::update(void)
{
	audio_block_t *block, *ampModBlock, *bpoABlock, *bpoBBlock;
	uint32_t i, ph, inc, index, scale, input;
	int32_t val1, val2;
	uint16_t inputFractional, inputWhole;
	uint32_t baseFreq, powerResult;
	ampModBlock = receiveWritable(0);
	if (!ampModBlock) {
		release(ampModBlock);
		return;
	}
	bpoABlock = receiveWritable(1);
	if (!bpoABlock) {
		release(bpoABlock);
		return;
	}
	bpoBBlock = receiveWritable(2);
	if (!bpoBBlock) {
		release(bpoBBlock);
		return;
	}
	block = allocate();
	if (block) {
		ph = phase_accumulator;
		//inc = phase_increment;
		//Rather then this, calculate inc sample by sample
		for (i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
			index = ph >> 24;
			val1 = waveFormPointerA[index];
			val2 = waveFormPointerA[index+1];
			scale = (ph >> 8) & 0xFFFF;
			val2 *= scale;
			val1 *= 0x10000 - scale;
			
			block->data[i] = multiply_32x32_rshift32(val1 + val2, ampModBlock->data[i] >> 1);
			
			//put whole in 16t and partial in 16b
			//input = (uint32_t)(bpoABlock->data[i] & 0x7FFF) << 4;
			
			//do it the old way
			input = bpoABlock->data[i];
			inputFractional = input & 0x0FFF;
			inputWhole = ( input & 0x7000 ) >> 12;
			
			baseFreq = 0x76D6A;  //This is a 24 bit number

			baseFreq = baseFreq << inputWhole;
			
			//powerResult = (uint32_t)twoPowers12bit[input];
			
			//inc = basefreq * (power result + 1 (whole))
			//powerResult = signed_multiply_32x16b((baseFreq >> 8), twoPowers12bit[inputFractional]);
			powerResult = ((uint64_t)(baseFreq >> 8) * twoPowers12bit[inputFractional]) >> 16;
			//powerResult = ((uint64_t)(baseFreq >> 8) * (uint64_t)twoPowers12bit[(input & 0x0000FFFF) >> 4]) >> 16;
			
			baseFreq = powerResult + (baseFreq >> 8);
			
			//need to format for correct inc.
			inc = baseFreq << 8;
			
			//inc = 0x76D6A; //known test line
			
			//old way
			//block->data[i] = multiply_32x32_rshift32(val1 + val2, ampModBlock->data[i] >> 1);
			////inc = (uint32_t)bpoABlock->data[i] << 16;
			//input = (uint32_t)bpoABlock->data[i];
			//inputFractional = input & 0x0FFF;
			//inputWhole = ( input & 0x7000 ) >> 12;
			//baseFreq = 0x76D6A;
			//baseFreq = baseFreq	<< inputWhole;
			//inc = (baseFreq * ((((uint64_t)twoPowers12bit[inputFractional] + 0x10000 ) << 8))) >> 24;

			ph += inc;
		}
		phase_accumulator = ph;
		transmit(block);
		release(block);
		release(ampModBlock);
		release(bpoABlock);
		release(bpoBBlock);
		return;
	}
	
	phase_accumulator += phase_increment * AUDIO_BLOCK_SAMPLES;
}

void AudioSynthMultiOsc::begin(void)
{
    WaveGenerator testWave;
	waveFormPointerA = testWave.allocateU16_257();
	waveFormPointerB = testWave.allocateU16_257();
	
    testWave.setParameters( 255, 255, 0, 0, 45 );
    testWave.writeWaveU16_257( waveFormPointerA );	
}

int16_t * AudioSynthMultiOsc::getPointer( uint8_t oscNumber ) //Pass number 0 = OSC A, 1 = OSC B
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

void AudioSynthMultiOsc::setPointer( uint8_t oscNumber, int16_t * pointerVar ) //Pass number 0 = OSC A, 1 = OSC B
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