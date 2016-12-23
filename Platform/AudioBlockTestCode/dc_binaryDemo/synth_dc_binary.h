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

#ifndef synth_dc_binary_h_
#define synth_dc_binary_h_
#include "AudioStream.h"
#include "utility/dspinst.h"
#include "bitPerOctaveLUTs.c"

class AudioSynthWaveformDcBinary : public AudioStream
{
public:
	AudioSynthWaveformDcBinary() : AudioStream(1, inputQueueArray), state(0), setPoint(0), noGlideInput(0) {}
	// immediately jump to the new DC level
	void amplitude_int( int16_t );
	void amplitude_midi_key( int16_t );
	void amplitude_3_12( float );
	void glideOffset( int16_t glideOffsetValue )
	{
		// something = glideOffsetValue;
		//Glide offset is applied to incomming blocks
		glideOffset
	}
	void glideScale( int16_t glideScaleValue )
	{
		// something = ;
	}
	virtual void update( void );
private:
	uint8_t noGlideInput;
	audio_block_t *inputQueueArray[1];
	uint8_t state;     // 0=steady output, 1=transitioning
	int32_t setPoint; // current output
	float floatMagnitude; // math output
	int32_t target;    // designed output (while transitiong)
	int32_t increment; // adjustment per sample (while transitiong)
};

#endif
