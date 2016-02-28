

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine3;          //xy=176.88888549804688,208
AudioSynthWaveformSine   sine1;          //xy=177.88888549804688,112
AudioSynthWaveformSine   sine2;          //xy=177.88888549804688,160
AudioSynthWaveformSine   sine4;          //xy=177.88888549804688,258
AudioOutputI2SQuad       i2s_quad1;      //xy=454.888916015625,147
AudioConnection          patchCord1(sine3, 0, i2s_quad1, 2);
AudioConnection          patchCord2(sine1, 0, i2s_quad1, 0);
AudioConnection          patchCord3(sine2, 0, i2s_quad1, 1);
AudioConnection          patchCord4(sine4, 0, i2s_quad1, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=429.888916015625,226
AudioControlSGTL5000     sgtl5000_2;     //xy=429.888916015625,271
// GUItool: end automatically generated code

//This sketch generates a scope loop on the button pins, led outputs, and the mux select pins.
//
//  Change log;
//    2/24/2016 -- Created

#include "proto-8Hardware.h"

int8_t loopCount = 0;
int8_t maxLoopCount = 20;
int8_t scriptRunOnce = 1;
int16_t poorTimer = 0;

LEDShiftRegister LEDs;
AnalogMuxTree knobs;
SwitchMatrix switches;
void setup()
{
	//**** Audio Section ****//
	AudioMemory(35);
	
	sgtl5000_1.setAddress(LOW);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);
	
	sgtl5000_2.setAddress(HIGH);
	sgtl5000_2.enable();
	sgtl5000_2.volume(0.5);
	
	sine1.amplitude(1);
	sine1.frequency(440);
	
	sine2.amplitude(1);
	sine2.frequency(220);
	
	sine3.amplitude(1);
	sine3.frequency(440);
	
	sine4.amplitude(1);
	sine4.frequency(350);
	
	Serial.begin(9600);
	LEDs.begin();
	knobs.begin();
	switches.begin();

}

void loop()
{
	//Uncomment to skip test and get straight to the data table loop
	//scriptRunOnce = 0;

	if(scriptRunOnce)
	{
		scriptRunOnce = 0;
		Serial.println("Program Started");
		Serial.println("Input characters to step through the tests");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		Serial.println("\nMUX SELECT PINS");
		Serial.println("  Walks through ABCD");
		
		//Countdown*********************************************//
		Serial.println("Push return to start countdown.");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		Serial.print("2.. ");
		delay(1000);
		Serial.print("1.. ");
		delay(1000);
		Serial.println("GO!");
		//End Countdown*****************************************//
		
		pinMode(MUXAPin, OUTPUT);
		pinMode(MUXBPin, OUTPUT);
		pinMode(MUXCPin, OUTPUT);
		pinMode(MUXDPin, OUTPUT);
		
		digitalWrite(MUXAPin, 1);
		delay(1000);
		
		digitalWrite(MUXAPin, 0);
		digitalWrite(MUXBPin, 1);
		delay(1000);
		
		digitalWrite(MUXBPin, 0);
		digitalWrite(MUXCPin, 1);
		delay(1000);
	
		digitalWrite(MUXCPin, 0);
		digitalWrite(MUXDPin, 1);
		delay(1000);
		digitalWrite(MUXDPin, 0);
	
		Serial.println("\nMUX SELECT PINS");
		Serial.println("  Push return to read all knobs");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		knobs.begin();
		knobs.scan();
		for(int i = 1; i < 65; i++)
		{
			Serial.print(i);
			Serial.print(", ");
			Serial.println(knobs.fetch(i));
		}
		Serial.println("Reading Knobs.");
		
		Serial.println("Test done.");
	
		Serial.println("\nLED PINS");
		LEDs.begin();
		Serial.println("  Test walks a 1 from LED 1 to 64, each 1/2 second.");
	
		//Countdown*********************************************//
		Serial.println("Push return to start countdown.");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		Serial.print("2.. ");
		delay(1000);
		Serial.print("1.. ");
		delay(1000);
		Serial.println("GO!");
		//End Countdown*****************************************//
	
	
		LEDs.clear();
		LEDs.send();
		for(int i = 0; i < 64; i++)
		{
			LEDs.store(i, 0);
			LEDs.store(i + 1, 1);
			LEDs.send();
			delay(500);
		}
		Serial.println("Test done.");

		Serial.println("\nLED PINS");
		LEDs.begin();
		
		//Matrix stuff
		Serial.println("  Switch Matrix Test Patterns");
	
		Serial.println("Push return for pattern 0xAAAA");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		switches.send(0xAAAA);
		
		Serial.println("Push return for pattern 0x5555");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}
		switches.send(0x5555);

		Serial.println("Test done!");
		Serial.println("Push return for post-test loop");
		while(Serial.available() == 0);
		while(Serial.available())
		{
			Serial.read();
		}

	}

	//while(1)
	{
		switches.scan();
		knobs.scan();
		if( poorTimer > 300 )
		{
			poorTimer = 0;
			Serial.println("Reading Knobs.");
			
			int temp;
			for(int j = 0; j < 8; j++)
			{
				for(int i = 0; i < 8; i++)
				{
					temp = (j * 8) + i + 1;
					Serial.print(knobs.fetch(temp));
					Serial.print(", ");
				}
				Serial.print("\n");
			}
			
			Serial.print("\nReading Switches.");
			for(int i = 1; i < 65; i++)
			{
				if((i == 1)||(i == 17)||(i == 33)||(i == 49))
				{
					Serial.println();
				}
				Serial.print(switches.fetch(i));
				//Serial.print(i);
				Serial.print(", ");
			}
			Serial.println();
			
			Serial.println("\nLED data");
			for(int i = 0; i < 8; i++)
			{
				uint8_t ledpack = LEDs.LEDData[i];
				if(ledpack < 0x80) Serial.print("0");
				if(ledpack < 0x40) Serial.print("0");
				if(ledpack < 0x20) Serial.print("0");
				if(ledpack < 0x10) Serial.print("0");
				if(ledpack < 0x08) Serial.print("0");
				if(ledpack < 0x04) Serial.print("0");
				if(ledpack < 0x02) Serial.print("0");
				Serial.println(ledpack, BIN);
				//Serial.print(i);
			}
			Serial.println();		
			Serial.println();
			
		}
		LEDs.clear();

		uint16_t temp;
		temp = knobs.fetch(64);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(49);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(50);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(51);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(52);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(53);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(54);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(55);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		temp = knobs.fetch(56);
		temp = temp >> 4;
		LEDs.store(temp + 1, 1);
		
		LEDs.send();
		
		delay(1);
		poorTimer++;
	}
	
}
