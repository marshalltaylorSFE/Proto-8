// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
  
#include "synth_dc_binary.h"

extern const float note2bpo[129];

void AudioSynthWaveformDcBinary::update(void)
{
	audio_block_t *block;
	uint32_t *p, *end, val;

	block = allocate();
	if (!block) return;
	p = (uint32_t *)(block->data);
	end = p + AUDIO_BLOCK_SAMPLES/2;

	if(magnitude > 0x7FFF)
	{
		//magnitude = -32768 + (magnitude & 0x7FFF);
	}
	// steady DC output, simply fill the buffer with fixed value
	val = pack_16b_16b(magnitude, magnitude);
	do {
		*p++ = val;
		*p++ = val;
		*p++ = val;
		*p++ = val;
		*p++ = val;
		*p++ = val;
		*p++ = val;
		*p++ = val;
	} while (p < end);
	
	transmit(block);
	release(block);
}

void AudioSynthWaveformDcBinary::amplitude_int( int16_t n )
{
	__disable_irq();
	magnitude = n;
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
	magnitude = tempAudioBlockData;
	__enable_irq();
	
}

void AudioSynthWaveformDcBinary::amplitude_4_12( float floatVar )
{
	__disable_irq();
    uint16_t wholePart = (uint16_t)floatVar;
    uint16_t fractionalPart = (uint16_t)((floatVar - wholePart)*4096);
	if( wholePart > 15 ) wholePart = 15;
    uint16_t tempAudioBlockData = wholePart << 12 | fractionalPart;
	magnitude = tempAudioBlockData;
	__enable_irq();
	
}