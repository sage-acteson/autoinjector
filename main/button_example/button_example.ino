
const int buttonInPin = 3;
const int buzzerPin = 5;

int currentButtonState = 0;
int lastButtonState = 0;
bool currentlyWarning = false;

unsigned long injectionDelay = 2000;
unsigned long warningStartTime = 0;

void setup() {
  pinMode(buttonInPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
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
  tone(buzzerPin, 2000, 100);
}
