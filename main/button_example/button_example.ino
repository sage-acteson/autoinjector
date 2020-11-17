#include <Servo.h>

const int buttonInPin = 3;
const int buzzerPin = 5;
const int servoPin = 6;

int currentButtonState = 0;
int lastButtonState = 0;
bool currentlyWarning = false;

unsigned long injectionDelay = 2000;
unsigned long warningStartTime = 0;

Servo servo;

void setup() {
  pinMode(buttonInPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  servo.attach(servoPin);
  servo.write(0);
}

void loop() {
  // BUTTON
  currentButtonState = digitalRead(buttonInPin);
  // execute logice if the button state has changed
  if(currentButtonState != lastButtonState) {
    // but only if it was pressed (no need to do it for unpressing too)
    if (currentButtonState == HIGH) {
      handleButtonPress();
    }
    delay(30);
  }
  lastButtonState = currentButtonState;

  // TIME
  if(currentlyWarning && ((millis() - warningStartTime) > injectionDelay)) {
    inject(); 
  }
}

void handleButtonPress() {
  if(currentlyWarning == false) {
    warnUser();
  } else {
    cancelInjection();
  }
}

void warnUser() {
  currentlyWarning = true;
  warningStartTime = millis();
  tone(buzzerPin, 1000, int(injectionDelay));
}

void cancelInjection() {
  currentlyWarning = false;
  noTone(buzzerPin);
}

void inject() {
  currentlyWarning = false;
  servo.write(90);
  delay(1000);
  servo.write(0);
}
