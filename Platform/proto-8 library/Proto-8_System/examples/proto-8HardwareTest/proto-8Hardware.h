// proto-8Hardware.h
//
//  Change log;
//    2/24/2016 -- Created
//    2/25/2016 -- Branched to demo for deployment
//    2/28/2016 -- Moved to Proto-8 repo

#if !defined(PROTO8_HARDWARE_H)
#define PROTO8_HARDWARE_H

static const int nOEPin = 33;
static const int LCLKPin = 32;
static const int nRSTPin = 26;
static const int SPI_CLK = 14;
static const int SPI_MOSI = 7;

static const int ROW1Pin = 2;
static const int ROW2Pin = 3;
static const int ROW3Pin = 4;
static const int ROW4Pin = 5;
static const int BSERPin = 17;
static const int BCLKPin = 16;
static const int BLATCHPin = 24;
static const int BOEpin = 25;

static const int MUXAPin = 27;
static const int MUXBPin = 28;
static const int MUXCPin = 29;
static const int MUXDPin = 20;
static const int AnENPin = 21;
static const int A10Pin = A10;//44;
static const int A11Pin = A11;//45;
static const int A12Pin = A12;//46;
static const int A13Pin = A13;//47;


class LEDShiftRegister
{
public:
	LEDShiftRegister();
	void begin();
	void send( uint8_t, uint8_t );
	void send();
	void store( uint8_t, uint8_t );
	void clear();
//private:
	uint8_t LEDData[8];
};

class AnalogMuxTree
{
public:
	AnalogMuxTree();
	void begin();
	void scan();
	uint16_t fetch( uint8_t );

private:
	uint16_t KnobData[64];
};

class SwitchMatrix
{
public:
	SwitchMatrix();
	void begin();
	void scan();
	uint8_t fetch( uint8_t );
	void send( uint16_t );

private:
	uint16_t rowData[4];
};

#endif