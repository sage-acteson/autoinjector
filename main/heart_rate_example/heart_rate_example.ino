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
    notifyHeartBeat();
    delay(150);
    heartRateState = false;
  }
}

void notifyHeartBeat() {
  Serial.println("HEARTBEAT DETECTED");
  tone(buzzerPin, 2000, 10);
}

void flipHeartRateState() {
  heartRateState = !heartRateState;
}
