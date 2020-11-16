const int buzzerPin = 3;
const byte heartBeatPin = A4;
const int heartInterruptPin = 2; // looks like this will work on the nano and feather?
const int buttonInPin = 5;
volatile bool state = false;
int buttonState = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);
  pinMode(buttonInPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flip, RISING);
  Serial.begin (9600);
}

void loop()
{
//    POTENTIOMETER TEST
//    int sensorValue = analogRead(heartBeatPin); // 0 to 708
//    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//    float voltage = sensorValue * (5.0 / 1023.0);
//    // print out the value you read:
//    Serial.println(voltage);

//  STATE TEST w/ interrupt
//  if (state == true) {
//    state = false;
//    audioBlip();
//  }

//  BUZZER TEST
//  audioWarning();
//  delay(1000);

// BUTTON TEST
  buttonState = digitalRead(buttonInPin);
  if (buttonState == HIGH) {
    audioBlip();
  } else {
    noTone(buzzerPin);
  }
}

void audioWarning() {
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 587, 250); //D5
  delay(250);
  tone(buzzerPin, 440, 1000); //A4
}

void audioBlip() {
  tone(buzzerPin, 2000, 10);
}

void flip() {
  state = !state;
}
