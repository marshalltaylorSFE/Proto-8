#ifndef synth_monoosc_h_
#define synth_monoosc_h_

#include "AudioStream.h"
#include "arm_math.h"

#define POLYCOUNT 1

// TODO: investigate making a high resolution sine wave
// using Taylor series expansion.
// http://www.musicdsp.org/showone.php?id=13

class AudioSynthMonoOsc : public AudioStream
{
public:
	AudioSynthMonoOsc() : AudioStream(1 + (POLYCOUNT * 2), inputQueueArray){
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
	void frequency(float freq) {
		if (freq < 0.0) freq = 0.0;
		else if (freq > AUDIO_SAMPLE_RATE_EXACT/2) freq = AUDIO_SAMPLE_RATE_EXACT/2;
		phase_increment = freq * (4294967296.0 / AUDIO_SAMPLE_RATE_EXACT);
	}
	void phase(float angle) {
		if (angle < 0.0) angle = 0.0;
		else if (angle > 360.0) {
			angle = angle - 360.0;
			if (angle >= 360.0) return;
		}
		
		phase_accumulator[0] = angle * (4294967296.0 / 360.0);
		phase_accumulator[1] = angle * (4294967296.0 / 360.0);
		phase_accumulator[2] = angle * (4294967296.0 / 360.0);
		phase_accumulator[3] = angle * (4294967296.0 / 360.0);
	}
	void amplitude(uint8_t osc, uint8_t level) {
		if(osc < POLYCOUNT) staticAmp[osc] = level;
	}
	virtual void update(void);
private:
	uint32_t phase_accumulator[POLYCOUNT];
	uint32_t phase_increment;
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
