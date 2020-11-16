#include <Servo.h>

// pin definitions
const int buzzerPin = 5;
const int heartInterruptPin = 2;
const int buttonInPin = 3;
const int servoPin = 9;

// other global constants
const int injectionDelay = 2000; // the time between the start of the warning and start of injection in milliseconds

// volatile vars for interrupts
volatile bool heartRateState = false;
volatile bool volButtonState = false;

// objects
Servo servo;

// global vars
int buttonState = 0;
bool havingReaction = false;
unsigned long timeReactionStarted = 0;

// heart rate tracking
const int beatsToTrack = 5;
const int beatsForShortAvg = 2;
int heartBeats[beatsToTrack]; // store the heart beats as time since the previous beat
int timeOfLastBeat = 0;
float longAvg = 0; // the long and short term average heart rates
float shortAvg = 0;

void setup() {
  // set pin modes
  pinMode(buzzerPin, OUTPUT);
  pinMode(heartInterruptPin, INPUT_PULLUP);
  pinMode(buttonInPin, INPUT_PULLUP);
  // set interrupts
  attachInterrupt(digitalPinToInterrupt(heartInterruptPin), flipHeartRateState, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonInPin), flipVolButtonState, RISING);
  // activate serial TODO remove this
  Serial.begin (9600);
  // setup the servo
  servo.attach(servoPin);
  servo.write(0);
}

void loop()
{
  //  STATE TEST w/ interrupt
//    if (heartRateState == true) {
//      heartRateState = false;
//      updateHeartData();
//      audioBlip();
//      int i = 0;
//      String toPrint = "";
//      for( i = 0; i < beatsToTrack; i++) {
//        toPrint += String(heartBeats[i]) + " ";
//      }
//      Serial.println(toPrint);
//    }

  // WITH STATE and INTERRUPTs
  if (volButtonState == true) {
    volButtonState = false;
    audioBlip();
    inject();
  }
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

void updateHeartData() {
  int currentTime = millis();
  int newBeatDuration = currentTime - timeOfLastBeat;
  // this check is to prevent wild averages if the system is running and isn't connected for a while
  if(newBeatDuration < 10000) {
    rotateArray();
    heartBeats[beatsToTrack-1] = newBeatDuration;
  }
  // TODO (if testing supports it) wipe the array if it has been too long since a heartbeat?
  timeOfLastBeat = currentTime;
}

void rotateArray() {
  int i = 0;
  for( i = 0; i < beatsToTrack -1; i++ ) {
    heartBeats[i] = heartBeats[i+1];
  }
}

// Turn the servo to inject
void inject() {
  servo.write(90);
  breakItDown();
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
  delay(10000);
}
