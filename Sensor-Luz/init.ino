#define TCRT5000 2 // Pin connected to the output of the TCRT5000

void setup() {
  Serial.begin(9600);
  pinMode(TCRT5000, INPUT);
}

void loop() {
  int sensorValue = digitalRead(TCRT5000);
  if (sensorValue == HIGH) {
    Serial.println("White");
  } else {
    Serial.println("Black");
  }
  delay(100);
}