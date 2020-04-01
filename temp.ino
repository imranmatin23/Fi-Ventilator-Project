// Declaring Pins
const int buzzerPin = 5;

// Setting Buzzer mode to False
bool buzzer_mode = false;


void setup()
{
  pinMode(buzzerPin,OUTPUT);
  // Wait before starting the alarm
  delay(5000);
}

void loop()
{
  // To chech whether the motion is detected or not
  if (digitalRead(motionPin)) {
    buzzer_mode = true; 
  }

  // If alarm mode is on,blink our LED
  if (buzzer_mode){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;   
      if (ledState == LOW)
        ledState = HIGH;
      else
        ledState = LOW;
    // Switch the LED
    digitalWrite(ledPin, ledState);
    }
    tone(buzzerPin,1000);
  }

  // If alarm is off
  if (buzzer_mode == false) {
  
    // No tone & LED off
    noTone(buzzerPin);  
    digitalWrite(ledPin, LOW);
  }

  // If our button is pressed Switch off ringing and Setup
  int button_state = digitalRead(buttonPin);
  if (button_state) {buzzer_mode = false;}
}