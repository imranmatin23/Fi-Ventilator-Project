#include <Encoder.h>
#include <math.h>

int en3and4 = 2;
int in3 = 3;
int in4 = 4;

int encA = 5;
int encB = 6;

long oldPosition = -999;
long newPosition = -999;

int THRESHOLD = 100;
int count = 0;

void setup()
{
  	Serial.begin(9600);
 	Serial.println("Beginning program...");
   	Serial.println("Set motor control pins...");

  	pinMode(encA, INPUT);      // sets the digital pin as input
    pinMode(encB, INPUT);      // sets the digital pin as input

    attachInterrupt(digitalPinToInterrupt(encA),encoderA,CHANGE);
    attachInterrupt(digitalPinToInterrupt(encB),encoderB,CHANGE);
  
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
		Serial.print("Count: ");
      	Serial.println(count);
    } while (count < THRESHOLD);
  
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
		Serial.print("Count: ");
      	Serial.println(count);
    } while (newPosition == 0);
  
   	// Stop motor
    digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
	// Wait two seconds
	delay(2000);
}

// Interupt Function that Reads Encoder on Encoder Pulse
void encoderA() {
  Serial.println("In EncoderA()...");
  // look for a low-to-high on channel A
  if (digitalRead(encA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encB) == LOW) {
      count = count + 1;         // CW
    }
    else {
      count = count - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encB) == HIGH) {
      count = count + 1;          // CW
    }
    else {
      count = count - 1;          // CCW
    } 
  }
  // use for debugging - remember to comment out
}

void encoderB() {
  Serial.println("In EncoderB()...");
  // look for a low-to-high on channel B
  if (digitalRead(encB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encA) == HIGH) {
      count = count + 1;         // CW
    }
    else {
      count = count - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encA) == LOW) {
      count = count + 1;          // CW
    }
    else {
      count = count - 1;          // CCW
    }
  }
}
