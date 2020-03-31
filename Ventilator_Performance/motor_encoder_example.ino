// Variables for encoder operation
int encoder_input_A_pin = 3;       // Digital input pin
int encoder_input_B_pin = 2;       // Digital input pin

// Motor variables
int direction_pin = 7;
int pwm_pin = 6;
int motor_value = 255; // 0 - 255
int motor_direction = 1;
long int c_1, c_2;
float t_1, t_2;
float rpm;

// Variables for detecting encoder pulse and counting
long int count = 0;


void setup() {
  Serial.begin(9600);              //serial output 
  pinMode(encoder_input_A_pin, INPUT);      // sets the digital pin as input
  pinMode(encoder_input_B_pin, INPUT);      // sets the digital pin as input

  pinMode(direction_pin, OUTPUT);       // Set the direction pin output
  pinMode(pwm_pin, OUTPUT);       // Set the pwm pin output
  digitalWrite(direction_pin, motor_direction);      // Set the motor in motion
  
  attachInterrupt(digitalPinToInterrupt(encoder_input_A_pin),encoderA,CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_input_B_pin),encoderB,CHANGE);
  
  analogWrite(pwm_pin, motor_value);      // Set the motor in motion
}
 
void loop() {
    while(1){
    t_1=millis();
    c_1=count;
    delay(10);
    t_2=millis();
    c_2=count;
    rpm=float(abs((c_2-c_1)/(t_2-t_1))*1250);//
    Serial.print(millis());
    Serial.print(", ");   
    Serial.print(rpm);
    Serial.print(", ");   
    Serial.println(count);
    
    }
}

// Interupt Function that Reads Encoder on Encoder Pulse
void encoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder_input_A_pin) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder_input_B_pin) == LOW) {
      count = count + 1;         // CW
    }
    else {
      count = count - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder_input_B_pin) == HIGH) {
      count = count + 1;          // CW
    }
    else {
      count = count - 1;          // CCW
    } 
  }
  // use for debugging - remember to comment out
}

void encoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder_input_B_pin) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder_input_A_pin) == HIGH) {
      count = count + 1;         // CW
    }
    else {
      count = count - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder_input_A_pin) == LOW) {
      count = count + 1;          // CW
    }
    else {
      count = count - 1;          // CCW
    }
  }
}
