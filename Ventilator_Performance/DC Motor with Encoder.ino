#include <Encoder.h>
#include <math.h>

int en3and4 = 2;
int in3 = 3;
int in4 = 4;

int encA = 5;
int encB = 6;

Encoder myEnc(encA, encB);
long oldPosition = -999;
long newPosition = -999;

int THRESHOLD = 100;

void setup()
{
  	Serial.begin(9600);
 	Serial.println("Beginning program...");
   	Serial.println("Set motor control pins...");
	// Set all the motor control pins to outputs
	pinMode(en3and4, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  
  	Serial.println("Turn motor off...");
  	// Turn off motors - Initial state
 	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void loop() {
   	Serial.println("Beginning loop()...");
  
	// Compress bag 
	analogWrite(en3and4, 255);
    digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	
  	// Stop when theshold is hit
    do {
          newPosition = myEnc.read();
          if (newPosition != oldPosition) {
              oldPosition = newPosition;
              Serial.print("New Position: ");
              Serial.println(newPosition);
          }
    } while (newPosition < abs(THRESHOLD));
  
  	// Stop motor
    digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
	// Wait two seconds
	delay(2000);
  
  	// Decompress bag 
	analogWrite(en3and4, 255);
    digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  
   	// Stop when theshold is hit
    do {
          newPosition = myEnc.read();
          if (newPosition != oldPosition) {
              oldPosition = newPosition;
              Serial.print("New Position: ");
              Serial.println(newPosition);
          }
    } while (newPosition == 0);
  
   	// Stop motor
    digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
	// Wait two seconds
	delay(2000);
  
  	
}