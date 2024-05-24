const int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  analogWrite(motorPin, 255); // Motor a plena velocidade
  delay(2000);
  analogWrite(motorPin, 128); // Motor a meia velocidade
  delay(2000);
  analogWrite(motorPin, 0);   // Motor desligado
  delay(2000);
}

