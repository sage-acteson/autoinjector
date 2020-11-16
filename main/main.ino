#include <Servo.h>
// pin definitions
const int buzzerPin = 5;
const byte heartBeatPin = A4;
const int heartInterruptPin = 2;
const int buttonInPin = 3;
const int servoPin = 9;
// volatile vars for interrupts
volatile bool heartRateState = false;
volatile bool volButtonState = false;
// global vars
int buttonState = 0;
// objects
Servo servo;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);
  pinMode(buttonInPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonInPin), flipVolButtonState, RISING);
  Serial.begin (9600);
  servo.attach(servoPin);
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
//  if (heartRateState == true) {
//    heartRateState = false;
//    audioBlip();
//  }

//  BUZZER TEST
//  audioWarning();
//  delay(1000);

// BUTTON TEST
// BASIC
//  buttonState = digitalRead(buttonInPin);
//  if (buttonState == HIGH) {
//    audioBlip();
//  } else {
//    noTone(buzzerPin);
//  }
// WITH STATE and INTERRUPTs
//  if(volButtonState == true) {
//    volButtonState = false;
//    audioBlip();
//  }

// SERVO TEST
  servo.write(0);
  delay(500);
  delay(1000);
  servo.write(90);
  delay(500);
  delay(1000);
  servo.write(180);
  delay(500);
  delay(1000);
  servo.write(90);
  delay(500);
  delay(1000);
  servo.write(0);
  delay(500);
  delay(1000);
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

void flipHeartRateState() {
  heartRateState = !heartRateState;
}

void flipVolButtonState() {
  volButtonState = !volButtonState;
}
