#include <Servo.h>

const int heartInterruptPin = 2;
const int buzzerPin = 5;
const int servoPin = 6;

volatile bool heartRateState = false;

// heart rate tracking
const int beatsToTrack = 16;
const int beatsForShortAvg = 6;
int heartBeats[beatsToTrack]; // store the heart beats as time since the previous beat
unsigned long timeOfLastBeat = 0;
float longAvg = 0; // the long and short term average heart rates
float shortAvg = 0;

unsigned long injectionDelay = 2000;

Servo servo;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, CHANGE);

  Serial.begin (9600);

  servo.attach(servoPin);
  servo.write(0);
}

void loop() {
  if (heartRateState == true) {
    notifyHeartBeat();
    updateHeartData();
    calcNewAvgs();
    Serial.println("LONG: " + String(longAvg) + " SHORT: " + String(shortAvg));
    if (longAvg >= shortAvg * 1.2) {
      Serial.println(String("***REACTION STARTED***") + " Injection in " + String(injectionDelay) + " milliseconds");
      buzzThenInject();
    }
    delay(150);
    heartRateState = false;
  }
}

void notifyHeartBeat() {
  Serial.println("HEARTBEAT DETECTED");
  tone(buzzerPin, 2000, 10);
}

void updateHeartData() {
  unsigned long currentTime = millis();
  unsigned long newBeatDuration = currentTime - timeOfLastBeat;
  // this check is to prevent wild averages if the system is running and isn't connected for a while
  if (newBeatDuration < 10000) {
    rotateArray();
    heartBeats[beatsToTrack - 1] = int(newBeatDuration);
  }
  // TODO (if testing supports it) wipe the array if it has been too long since a heartbeat?
  timeOfLastBeat = currentTime;
}

void rotateArray() {
  int i = 0;
  for ( i = 0; i < beatsToTrack - 1; i++ ) {
    heartBeats[i] = heartBeats[i + 1];
  }
}

void calcNewAvgs() {
  longAvg = calcArrayAvg(0, beatsToTrack - beatsForShortAvg - 1);
  shortAvg = calcArrayAvg(beatsToTrack - beatsForShortAvg, beatsToTrack - 1);
}

float calcArrayAvg(int startIndex, int endIndex) {
  int i = 0;
  int totalTime = 0;
  int numIndexes = 0;
  for (i = startIndex; i <= endIndex; i++) {
    totalTime += heartBeats[i];
    numIndexes++;
  }
  return (totalTime / numIndexes);
}

void buzzThenInject() {
  tone(buzzerPin, 1000, injectionDelay);
  delay(injectionDelay);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(20000);
}

void flipHeartRateState() {
  heartRateState = !heartRateState;
}
