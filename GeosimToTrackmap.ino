/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/




#define Led_Indicator 13
#define FADE_STEP  1
#define GeoSim_Serial Serial
#define TrackMap_Serial Serial1

int brightness = 0;    // how bright the LED is
int fadeAmount = FADE_STEP;    // how many points to fade the LED by

void setup() {
	GeoSim_Serial.begin(4800);
	TrackMap_Serial.begin(9600);
	pinMode(Led_Indicator, OUTPUT);

  brightness = 0;


}

void loop() {
  
	if (GeoSim_Serial.available()) {      // If anything comes in Serial (USB),

    char aSerialLetter = GeoSim_Serial.read();
		TrackMap_Serial.write(aSerialLetter); 
    
	  brightness = brightness + fadeAmount;
    if (brightness > 255) brightness = 0;
    analogWrite(Led_Indicator, brightness);
    
	}


	if (TrackMap_Serial.available()) {     // If anything comes in Serial1 (pins 0 & 1)
		
		char aSerialLetter = TrackMap_Serial.read();
    GeoSim_Serial.write(aSerialLetter);   // read it and send it out Serial (USB)
		
	}
}
