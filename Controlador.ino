// Sensores
const int sensorLeft = 11;   // sensor da esquerda
const int sensorCenter = 12; // sensor do meio
const int sensorRight = 13;  // sensor da direita

// Motores
const int motorLeftSpeed = 5;       // pino de velocidade do motor da esquerda
const int motorLeftDirection = 6;   // pino de direção do motor da esquerda
const int motorRightSpeed = 9;      // pino de velocidade do motor da direita
const int motorRightDirection = 10; // pino de direção do motor da direita

// Constates de controle
const int numReadings = 10;
const int speed = 20;
const int reducedSpeed = 0;

// Rotação

#define D_Sensor_Left 3
#define D_Sensor_Right 2

volatile double velocity_Left = 0;
volatile double velocity_Right = 0;
volatile long prevT_Left = 0;
volatile long prevT_Right = 0;
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 100;
const unsigned long timeoutInterval = 500; // Ajuste conforme necessário

void setup()
{
  Serial.begin(115200);

  pinMode(motorLeftSpeed, OUTPUT);
  digitalWrite(motorLeftDirection, LOW);
  pinMode(motorRightSpeed, OUTPUT);
  digitalWrite(motorRightDirection, LOW);


  pinMode(sensorLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight, INPUT);

  attachInterrupt(digitalPinToInterrupt(D_Sensor_Left), readEncoderLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(D_Sensor_Right), readEncoderRight, RISING);
}

void loop()
{
  controlador();
  rpm();
}

int readSensorAverage(int sensorPin)
{
  int total = 0;
  for (int i = 0; i < numReadings; i++)
  {
    total += digitalRead(sensorPin);
    delay(10); // delay between readings
  }
  return total / numReadings;
}

void controlador()
{
  int sensorStateLeft = readSensorAverage(sensorLeft);
  int sensorStateCenter = readSensorAverage(sensorCenter);
  int sensorStateRight = readSensorAverage(sensorRight);

  if (sensorStateLeft == HIGH && sensorStateRight == LOW)
  {
    analogWrite(motorLeftSpeed, reducedSpeed);
    analogWrite(motorRightSpeed, speed);
  }
  else if (sensorStateLeft == LOW && sensorStateRight == HIGH)
  {
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, reducedSpeed);
  }
  else if (sensorStateLeft == LOW && sensorStateCenter == HIGH && sensorStateRight == LOW)
  {
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, speed);
  }
  else if (sensorStateLeft == LOW && sensorStateCenter == LOW && sensorStateRight == LOW)
  {
    delay(500);
    if (digitalRead(sensorLeft) == LOW && digitalRead(sensorCenter) == LOW && digitalRead(sensorRight) == LOW)
    {
      analogWrite(motorLeftSpeed, reducedSpeed);
      analogWrite(motorRightSpeed, reducedSpeed);
    }
  }
}

void readEncoderLeft()
{
  long currT = micros();
  double deltaT = ((double)(currT - prevT_Left)) / 1.0e6;
  if (deltaT >= 0.015)
  {
    velocity_Left = 1 / deltaT;
    prevT_Left = currT;
  }
}

void readEncoderRight()
{
  long currT = micros();
  double deltaT = ((double)(currT - prevT_Right)) / 1.0e6;
  if (deltaT >= 0.015)
  {
    velocity_Right = 1 / deltaT;
    prevT_Right = currT;
  }
}

void rpm()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastPrintTime >= printInterval)
  {
    lastPrintTime = currentMillis;
    if (currentMillis - (prevT_Left / 1000) > timeoutInterval)
    {
      velocity_Left = 0;
    }
    if (currentMillis - (prevT_Right / 1000) > timeoutInterval)
    {
      velocity_Right = 0;
    }
    double velocityRPM_Left = velocity_Left / 20.0 * 60.0;
    double velocityRPM_Right = velocity_Right / 20.0 * 60.0;
    Serial.print("Left RPM: ");
    Serial.print(velocityRPM_Left);
    Serial.print(", Right RPM: ");
    Serial.println(velocityRPM_Right);
  }
}