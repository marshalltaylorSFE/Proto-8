// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
#ifndef synth_monoosc_h_
#define synth_monoosc_h_

#include "AudioStream.h"
#include "arm_math.h"

#define POLYCOUNT 4

class AudioSynthMultiOsc : public AudioStream
{
public:
	AudioSynthMultiOsc() : AudioStream(1 + (POLYCOUNT * 2), inputQueueArray){
		beginHasRun = 0;
		for( int i = 0; i < POLYCOUNT; i++ )
		{
			staticAmp[i] = 255;
			staticRoot[i] = 1;
		}
	};
	void begin( void );
	int16_t * getPointer( uint8_t );
	void setPointer( uint8_t, int16_t * );
private:
	audio_block_t *inputQueueArray[1 + (POLYCOUNT * 2)];
	int16_t *waveFormPointerA;
	int16_t *waveFormPointerB;
	
public:
	void amplitude(uint8_t osc, uint8_t level) {
		if(osc < POLYCOUNT) staticAmp[osc] = level;
	}
	virtual void update(void);
private:
	uint32_t phase_accumulator[POLYCOUNT];
	int32_t magnitude;
	uint8_t beginHasRun;
public:
//Expand staticAmp and staticRoot to increase polyphony
	uint32_t staticAmp[POLYCOUNT];
	int8_t staticRoot[POLYCOUNT];
	//Debug variables to report inner update() information at a fixed rate.
	uint8_t debugFlag = 0;
	int64_t debugSave = 0;
};



#endif
