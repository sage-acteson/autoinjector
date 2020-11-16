const int buzzerPin = 3;
const byte heartBeatPin = A4;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin (9600);
}

void loop()
{
  int sensorValue = analogRead(A4); // 0 to 708
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(sensorValue);
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
