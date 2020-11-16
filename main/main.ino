const int buzzerPin = 3;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  
}

void audioWarning() {
  tone(buzzerPin,294,125);//D4
  delay(125);
  tone(buzzerPin,294,125);//D4
  delay(125);
  tone(buzzerPin,587,250);//D5
  delay(250);
  tone(buzzerPin,440,1000);//A4
}
