// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------

#ifndef synth_dc_binary_h_
#define synth_dc_binary_h_
#include "AudioStream.h"
#include "utility/dspinst.h"
//#include "bitPerOctaveLUTs.h"

class AudioSynthWaveformDcBinary : public AudioStream
{
public:
	AudioSynthWaveformDcBinary() : AudioStream(0, NULL), state(0), magnitude(0) {}
	// immediately jump to the new DC level
	void amplitude_int( int16_t );
	void amplitude_midi_key( int16_t );
	void amplitude_4_12( float );

	virtual void update( void );
private:
	uint8_t  state;     // 0=steady output, 1=transitioning
	int32_t  magnitude; // current output
	int32_t  target;    // designed output (while transitiong)
	int32_t  increment; // adjustment per sample (while transitiong)
};

#endif
