#include <Servo.h>

// pin definitions
const int buzzerPin = 5;
const int heartInterruptPin = 2;
const int buttonInPin = 3;
const int servoPin = 6;

// other global constants
const int injectionDelay = 5000; // the time between the start of the warning and start of injection in milliseconds

// volatile vars for interrupts
volatile bool heartRateState = false;
volatile bool volButtonState = false;

// objects
Servo servo;

// global vars
int buttonState = 0;
int havingReaction = 0;
unsigned long timeReactionStarted = 0;

// heart rate tracking
const int beatsToTrack = 16;
const int beatsForShortAvg = 6;
int heartBeats[beatsToTrack]; // store the heart beats as time since the previous beat
unsigned long timeOfLastBeat = 0;
float longAvg = 0; // the long and short term average heart rates
float shortAvg = 0;

void setup() {
  // set pin modes
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);
  pinMode(buttonInPin, INPUT_PULLUP);
  // set interrupts
  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonInPin), flipVolButtonState, RISING);
  // activate serial TODO remove this
  Serial.begin (9600);
  // setup the servo
  servo.attach(servoPin);
  servo.write(0);
  havingReaction = 0;
}

void loop()
{
  
  // if a reaction is occuring
  if (havingReaction == true) {
    unsigned long currentTime = millis();
    Serial.println(String("HAVING REACTION = TRUE!?"));
    if ((currentTime - timeReactionStarted) >= injectionDelay) {
      Serial.println(String("INJECTION STARTED") + " Current Time: " + String(currentTime) + " Time Reaction Started: " + String(timeReactionStarted));
      inject();
      havingReaction = false;
      timeReactionStarted = 0;
    }
  }

  //  handle heart rate stuff
  if (heartRateState == true) {
    updateHeartData();
    audioBlip();
    calcNewAvgs();
    // check if a reaction is occuring
    if (longAvg >= shortAvg * 1.2) {
      havingReaction = true;
      timeReactionStarted = millis();
      Serial.println(String("REACTION STARTED") + "LONG: " + String(longAvg) + " SHORT: " + String(shortAvg));
      tone(buzzerPin, 1000, injectionDelay);
    }
    int i = 0;
    String toPrint = "";
    for ( i = 0; i < beatsToTrack; i++) {
      toPrint += String(heartBeats[i]) + " ";
    }
    // Serial.println(toPrint);
    // Serial.println("LONG: " + String(longAvg) + " SHORT: " + String(shortAvg));
    delay(25);
    heartRateState = false;
  }

  // WITH STATE and INTERRUPTs
  //  if (volButtonState == true) {
  //    volButtonState = false;
  //    audioBlip();
  //    inject();
  //  }
}

void audioBlip() {
  tone(buzzerPin, 2000, 10);
}

void flipHeartRateState() {
  //  heartRateState = !heartRateState;
  heartRateState = true;
}

void flipVolButtonState() {
  volButtonState = !volButtonState;
}

void updateHeartData() {
  int currentTime = millis();
  int newBeatDuration = currentTime - timeOfLastBeat;
  // this check is to prevent wild averages if the system is running and isn't connected for a while
  if (newBeatDuration < 10000) {
    rotateArray();
    heartBeats[beatsToTrack - 1] = newBeatDuration;
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

// Turn the servo to inject
void inject() {
  servo.write(90);
  breakItDown();
  delay(200);
  servo.write(0);
}

void breakItDown() {
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 587, 250); //D5
  delay(250);
  tone(buzzerPin, 440, 250); //A4
  delay(375);
  tone(buzzerPin, 415, 125); //Ab4
  delay(250);
  tone(buzzerPin, 392, 250); //G4
  delay(250);
  tone(buzzerPin, 349, 250); //F4
  delay(250);
  tone(buzzerPin, 294, 125); //D4
  delay(125);
  tone(buzzerPin, 349, 125); //F4
  delay(125);
  tone(buzzerPin, 392, 125); //G4
}
