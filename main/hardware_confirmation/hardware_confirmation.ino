// pin definitions
const int buzzerPin = 5;
const int heartInterruptPin = 2;
const int buttonInPin = 3;

// volatile vars for interrupts
volatile bool heartRateState = false;
volatile bool volButtonState = false;

void setup() {
  // set pin modes
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);
  pinMode(buttonInPin, INPUT_PULLUP);
  // set interrupts
  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonInPin), flipVolButtonState, RISING);
}

void loop() {
  heartRateTest();
  buttonTest();
  //buzzerTest();
}

void heartRateTest() {
  if (heartRateState == true) {
    heartRateState = false;
    audioBlip();
  }
}

void buttonTest() {
  if (volButtonState == true) {
    volButtonState = false;
    audioBlip();
  }
}

void buzzerTest() {
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 587, 250); //D5
  delay(250);
  tone(buzzerPin, 440, 100); //A4
  delay(1000);
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


//  POTENTIOMETER TEST
//  int sensorValue = analogRead(heartBeatPin); // 0 to 708
//  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//  float voltage = sensorValue * (5.0 / 1023.0);
//  // print out the value you read:
//  Serial.println(voltage);
