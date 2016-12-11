#ifndef WAVEGEN_H
#define WAVEGEN_H
#include "stdint.h"

#define SINESHAPE 0
#define PULSESHAPE 1
#define RAMPSHAPE 2
#define DCSHAPE 3

class WaveGenerator
{
    uint8_t masterAmp;

    uint8_t rampAmp;
    uint8_t sineAmp;
    uint8_t pulseAmp;
    uint8_t pulseDuty;
    uint8_t sampleNumber;

public:
    WaveGenerator( void );
    int16_t getSample( void );
    void resetOffset( void );
    void setParameters( uint8_t masterAmp, uint8_t rampAmp, uint8_t sineAmp, uint8_t pulseAmp, uint8_t pulseDuty );
	void writeWaveU16_257( int16_t * );
	int16_t * allocateU16_257( void );

};

#endif // WAVEGEN_H

