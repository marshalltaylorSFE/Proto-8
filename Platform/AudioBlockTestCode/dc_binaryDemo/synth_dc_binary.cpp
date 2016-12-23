/* This code came from the "synth_dc" block.
 * Changes made by Marshall Taylor.
 * March 29, 2016
 * Original copyright may apply.  Original header:
 *
 * Audio Library for Teensy 3.X
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

  
#include "synth_dc_binary.h"

void AudioSynthWaveformDcBinary::update(void)
{
	audio_block_t *glide, *block;
	uint32_t *p, *end, val;

	glide = receiveReadOnly(0);
	if (!glide)
	{
		//glide not connected, thats ok.
		noGlideInput = 1;
	}
	
	block = allocate();
	if (!block) return;
	p = (uint32_t *)(block->data);
	end = p + AUDIO_BLOCK_SAMPLES/2;

	
	//I don't know what I'm doing!!!
	
	//If the output doesn't equal the set point,
	//If the output is close to the set point snap, else
	//increment the output towards the set point
	int32_t magnitudeVar = 0;
	while (p < end)
	{
				magnitudeVar = floatMagnitude;
				floatMagnitude += floatIncrement + floatOffset;
				magnitudeVar = pack_16t_16t((int16_t)floatMagnitude, (int16_t)magnitudeVar);
				floatMagnitude += floatIncrement + floatOffset;
				*p++ = magnitudeVar;		
	}
	// steady DC output, simply fill the buffer with fixed value
	//val = pack_16b_16b(magnitude, magnitude);
	//do {
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//	*p++ = val;
	//} while (p < end);
	
	if( noGlideInput == 0 )	release(glide); //glide block was used.
	
	transmit(block);
	release(block);
}

void AudioSynthWaveformDcBinary::amplitude_int( int16_t n )
{
	__disable_irq();
	setPoint = n;
	__enable_irq();
}
	
void AudioSynthWaveformDcBinary::amplitude_midi_key( int16_t n )
{
	if( n < 0 ) n = 0;
	if( n > 127) n = 127;
	
	__disable_irq();
    uint16_t wholePart = (uint16_t)note2bpo[n];
    uint16_t fractionalPart = (uint16_t)((note2bpo[n] - wholePart)*4096);
	if( wholePart > 15 ) wholePart = 15;
    uint16_t tempAudioBlockData = wholePart << 12 | fractionalPart;
	setPoint = tempAudioBlockData;
	__enable_irq();
	
}

void AudioSynthWaveformDcBinary::amplitude_3_12( float floatVar )
{
	__disable_irq();
    uint16_t wholePart = (uint16_t)floatVar;
    uint16_t fractionalPart = (uint16_t)((floatVar - wholePart)*4096);
	if( wholePart > 15 ) wholePart = 15;
    uint16_t tempAudioBlockData = wholePart << 12 | fractionalPart;
	setPoint = tempAudioBlockData;
	__enable_irq();
	
}