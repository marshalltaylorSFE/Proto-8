// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------

#ifndef synth_dc_binary_glide_h_
#define synth_dc_binary_glide_h_
#include "AudioStream.h"
#include "utility/dspinst.h"
//#include "bitPerOctaveLUTs.h"

class AudioSynthWaveformDcBinaryGlide : public AudioStream
{
public:
	AudioSynthWaveformDcBinaryGlide() : AudioStream(1, inputQueueArray), target(0), accumulator(0), offsetValue(0), glideInputActive(0) {}
	// Set a new target point
	void amplitude_int( int16_t );
	void amplitude_midi_key( int16_t );
	void amplitude_4_12( float );
	void glideOffset( int16_t input )
	{//this stuff is no longer true:
		// range is from 1 to 1000 notes/second in Q4.12 format
		//offsetIncrement = ( 0.083333333333333 / 44100 ) * (input / 2^15) * 1000 //This is math not code
		// so 1 notes worth / samples / sec = number added per sample
		// Multiply this by up to 1000 to get 1000 notes / sample
		// IIII,PPPP,PPPP,PPPP,PPPP,PPPP,PPPP,PPPP b  (I = int, P = partial)
		// 0.0833333/44100 in Q4.24 = 0x00001FB
		// 0.0833333/44100 * 1000 = 0x7BD70  -- This cannot be multiplied by 2^15 (will overflow)
		//     ...for now shift right first (but accuracy will be lost
		// 0x7BD70 >> 15 = 0xF (coincidence).  Just multiply this by the properly ranged input value
		
		//..but we don't need to do this here, just save the value
		//
		//if( input < 0 ) input = 0;
		//offsetIncrement = 0xF * input; //This could be accomplished quicker by nudging left 4 places (and losing 1/16 as % accuracy)
		offsetValue = input;
		
	}
	virtual void update( void );
	uint8_t debugFlag = 0;
	int64_t debugSave1 = 0;
	int64_t debugSave2 = 0;

private:
	audio_block_t *inputQueueArray[1];
	//uint8_t state;     // 0=steady output, 1=transitioning
	int32_t target;    // target is Q8.24.  The output is bits 27 downto 11 are the output
public:
	int32_t accumulator;
private:
	int16_t offsetValue;
	// adjustment per sample, as set by glideOffset function call
	uint8_t glideInputActive;
};

#endif
