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

//Includes
#include "CircularBuffer.h"

//**********************************************************************//
//
//  Circular buffer
//
//
//**********************************************************************//
CircularBuffer::CircularBuffer( uint8_t inputDepth )
{
	bufferDepth = inputDepth;
	buffer = new uint32_t[bufferDepth];
	buffer[0] = 0;
	//Create success logging here
}
//~CircularBuffer( void )
//{
//	delete []buffer;
//}
uint32_t CircularBuffer::read( uint8_t inputDepth )
{
	//Start the returnPtr as 0
	int8_t returnPtr = 0;
	
	//Only do a valid read if the depth is in range

	
	//If depth is too deep, clamp it.
	if( inputDepth >= bytesUsed )
	{
		inputDepth = bytesUsed - 1;
	}
	
	//Ok, add the offset
	returnPtr = topPointer + inputDepth;
	
	//If position exceeds max-depth, roll
	if( returnPtr > bufferDepth )
	{
		returnPtr = returnPtr - (bufferDepth + 1);
	}
	
	//If there is no data in the buffer
	float returnVal = 0;
	if( bytesUsed == 0 )
	{
		//Woah, move that pointer back to the zero cell
		returnVal = 0;
	}
	else
	{
		returnVal = buffer[returnPtr];
	}
	
	//Return
	return returnVal;
	
}

void CircularBuffer::write( uint32_t inputData )
{
	//Lift the top pointer, unless
	if( topPointer > 0 )
	{
		//ok, lift
		topPointer--;
	}
	else
	{
		//flip
		topPointer = bufferDepth; 
	}
    
	//Write the byte
	buffer[topPointer] = inputData;
	
	//Increment the bytesUsed if less than max
	if( bytesUsed <= bufferDepth )
	{
		bytesUsed++;
	}
	
}

void CircularBuffer::clear( void )
{
	topPointer = 0;
	bytesUsed = 0;
	buffer[0] = 0;
	
}
