// Licenced as BeerWare
//  Written by Marshall Taylor
//  2016
//
//  You are free to do what you want with this file as long as you retain this header,
//  and in the event that we meet you buy me a beer at your discretion.
//
//--------------------------------------------------------------------------------------
  
#include "synth_dc_binary_glide.h"

extern const float note2bpo[129];

void AudioSynthWaveformDcBinaryGlide::update(void)
{
	audio_block_t *glide, *block;
	uint32_t *p, *end, *input_p, *input_end, val;
	int printstuf = 0;
	if(debugFlag)
	{
		debugFlag = 0;
		printstuf = 1;
	}
	
	glide = receiveReadOnly(0);
	if (!glide)
	{
		//glide not connected, thats ok.
		glideInputActive = 0;
	}
	else
	{
		glideInputActive = 1;
		//generate pointer
		input_p = (uint32_t *)(glide->data);
		input_end = input_p + AUDIO_BLOCK_SAMPLES/2;
	}
	
	block = allocate();
	if (!block) //It appears this is often called but no block is available?  This is weird.
	{
		//dump a potential glide block
		if( glideInputActive == 1 )	release(glide);
		return;
	}
	else //output block does exist
	{
		p = (uint32_t *)(block->data);
		end = p + AUDIO_BLOCK_SAMPLES/2;

		int32_t offsetIncrement = 0;
		int32_t accumulator1 = 0;
		while (p < end)
		{
			//for( int i = 0; i < 4; i++ )
			//{
				//Add offset to input and protect
				if( glideInputActive == 1 )
				{
					offsetIncrement = (int32_t)(int16_t)*input_p + (int32_t)offsetValue;
				}
				else
				{
					offsetIncrement = (int32_t)0 + (int32_t)offsetValue;
				}
				if( printstuf ) debugSave1 = offsetIncrement;
				if( offsetIncrement < 0 ) offsetIncrement = 0;
				if( offsetIncrement > 0x0000FFFF ) offsetIncrement = 0x0000FFFF; //Limit to uint15_t;
				if( printstuf ) debugSave2 = offsetIncrement;
				//Calculate new offsetIncrement
				offsetIncrement = offsetIncrement;
				//  ...now we have a Q8.24 to use to add
				//Increment accumulator
				if( accumulator < target )
				{
					accumulator += offsetIncrement;
					if( accumulator > target ) accumulator = target;
				}
				if( accumulator > target )
				{
					accumulator -= offsetIncrement;
					if( accumulator < target ) accumulator = target;
				}
				accumulator1 = accumulator;
	
				//Add offset to input and protect
				if( glideInputActive == 1 )
				{
					offsetIncrement = (int32_t)(int16_t)(*input_p >> 16) + (int32_t)offsetValue;
					input_p++;
				}
				else
				{
					offsetIncrement = (int32_t)0 + (int32_t)offsetValue;
				}
				if( offsetIncrement < 0 ) offsetIncrement = 0;
				if( offsetIncrement > 0x0000FFFF ) offsetIncrement = 0x0000FFFF; //Limit to uint15_t;

				//Calculate new offsetIncrement
				offsetIncrement = offsetIncrement;
				//  ...now we have a Q8.24 to use to add
				//Increment accumulator
				if( accumulator < target )
				{
					accumulator += offsetIncrement;
					if( accumulator > target ) accumulator = target;
				}
				if( accumulator > target )
				{
					accumulator -= offsetIncrement;
					if( accumulator < target ) accumulator = target;
				}			
				
				//apply to output audio stream
				uint32_t val = pack_16b_16b(( accumulator1 >> 12 ), ( accumulator >> 12 ));
				*p++ = val;
				//*p++ = 0x40004000;
			//}
			//
			//
			//
			//
			//if(
			//		offsetIncrement = floatMagnitude;
			//		floatMagnitude += floatIncrement + floatOffset;
			//		offsetIncrement = pack_16t_16t((int16_t)floatMagnitude, (int16_t)offsetIncrement);
			//		floatMagnitude += floatIncrement + floatOffset;
			//		*p++ = offsetIncrement;		
		}
		
		// steady DC output, simply fill the buffer with fixed value
		//int16_t packValue = target >> 16;
		//val = pack_16b_16b(packValue, packValue);
		//do {
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//	*p++ = val;
		//} while (p < end);
		
		if( glideInputActive == 1 )	release(glide); //glide block was used, release it.
		
		transmit(block);
		release(block);
	}
}

void AudioSynthWaveformDcBinaryGlide::amplitude_int( int16_t n )
{
	__disable_irq();
	//setPoint = n;
	target = ( uint32_t ) n << 12; //This puts it in 4.28 format uint32_t val = pack_16b_16b(( accumulator1 >> 12 ), ( accumulator >> 12 ));
	target &= 0x0FFFFFFF; //force positive int
	__enable_irq();
}
	
void AudioSynthWaveformDcBinaryGlide::amplitude_midi_key( int16_t n )
{
	if( n < 0 ) n = 0;
	if( n > 127) n = 127;
	
	__disable_irq();
    uint16_t wholePart = (uint16_t)note2bpo[n];
    uint16_t fractionalPart = (uint16_t)((note2bpo[n] - wholePart)*4096);
	if( wholePart > 15 ) wholePart = 15;
    uint16_t tempAudioBlockData = wholePart << 12 | fractionalPart;
	//setPoint = tempAudioBlockData;
	target = ( uint32_t ) tempAudioBlockData << 12;
	__enable_irq();
	
}

void AudioSynthWaveformDcBinaryGlide::amplitude_4_12( float floatVar )
{
	__disable_irq();
    uint16_t wholePart = (uint16_t)floatVar;
    uint16_t fractionalPart = (uint16_t)((floatVar - wholePart)*4096);
	if( wholePart > 15 ) wholePart = 15;
    uint16_t tempAudioBlockData = wholePart << 12 | fractionalPart;
	//setPoint = tempAudioBlockData;
	target = ( uint32_t ) tempAudioBlockData << 12;
	__enable_irq();
	
}