//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  May 26, 2015
//
//**********************************************************************//
#ifndef P8_CIRCULARBUFFER_H_INCLUDED
#define P8_CIRCULARBUFFER_H_INCLUDED

#include "stdint.h"

//Classes
class CircularBuffer
{
public:
    CircularBuffer( uint8_t inputDepth );
	//~CircularBuffer( void )
	uint32_t read( uint8_t );
	void write( uint32_t inputData );
	void clear( void );
	uint8_t debugVariable = 0;
	
	private:
	uint8_t topPointer;
	uint8_t bytesUsed;
	uint8_t bufferDepth;
	uint32_t * buffer;
	
};


#endif
