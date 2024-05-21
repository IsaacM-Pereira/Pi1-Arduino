volatile long pulseCount = 0;
long lastMillis = 0;
float RPM = 0.0;
const int pulsesPerRevolution = 22;

#define encoder 3

void setup()
{
  Serial.begin(9600);
  pinMode(encoder, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder), countPulse, RISING);
}

void loop()
{
  if (millis() - lastMillis >= 1000) { // 1 second has passed
    noInterrupts(); // disable interrupts to make the calculation and reset
    RPM = (pulseCount / (float)pulsesPerRevolution) * 60.0; // calculate RPM
    pulseCount = 0; // reset pulse count
    lastMillis = millis(); // reset lastMillis
    interrupts(); // re-enable interrupts
    Serial.println(RPM);
  }
}

void countPulse()
{
  pulseCount++;
}