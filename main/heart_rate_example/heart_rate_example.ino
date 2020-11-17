const int buzzerPin = 5;
const int heartInterruptPin = 2;

volatile bool heartRateState = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, CHANGE);

  Serial.begin (9600);
}

void loop() {
  if (heartRateState == true) {
    heartRateState = false;
    Serial.println("HEARTBEAT DETECTED");
    tone(buzzerPin, 2000, 10);
    delay(150);
  }
}

void flipHeartRateState() {
  heartRateState = !heartRateState;
}
