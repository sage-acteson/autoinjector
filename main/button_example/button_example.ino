
const int buttonInPin = 3;
const int buzzerPin = 5;

int currentButtonState = 0;
int lastButtonState = 0;
bool currentlyWarning = false;

void setup() {
  pinMode(buttonInPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
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
  tone(buzzerPin, 1000, 2000);
}

void cancelInjection() {
  currentlyWarning = false;
  noTone(buzzerPin);
}

void inject() {
  
}
