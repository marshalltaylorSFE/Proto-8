#ifndef synth_multiosc_h_
#define synth_multiosc_h_

#include "AudioStream.h"
#include "arm_math.h"

// TODO: investigate making a high resolution sine wave
// using Taylor series expansion.
// http://www.musicdsp.org/showone.php?id=13

class AudioSynthMultiOsc : public AudioStream
{
public:
	AudioSynthMultiOsc() : AudioStream(2, inputQueueArray), magnitude(16384){};
	void begin( void );
	int16_t * getPointer( uint8_t );
	void setPointer( uint8_t, int16_t * );
private:
	audio_block_t *inputQueueArray[2];
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
		phase_accumulator = angle * (4294967296.0 / 360.0);
	}
	void amplitude(float n) {
		if (n < 0) n = 0;
		else if (n > 1.0) n = 1.0;
		magnitude = n * 65536.0;
	}
	virtual void update(void);
private:
	uint32_t phase_accumulator;
	uint32_t phase_increment;
	int32_t magnitude;
};



#endif
