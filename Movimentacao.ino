// Sensores
const int sensorLeft = 11;   // sensor da esquerda
const int sensorCenter = 12; // sensor do meio
const int sensorRight = 13;  // sensor da direita

// Motores
const int motorLeftSpeed = 5;       // pino de velocidade do motor da esquerda
const int motorLeftDirection = 6;   // pino de direção do motor da esquerda
const int motorRightSpeed = 10;      // pino de velocidade do motor da direita
const int motorRightDirection = 9; // pino de direção do motor da direita

// Constates de controle
const int numReadings = 10;
const int speed = 70;
const int reducedSpeed = 0;

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
}

void loop()
{
  controlador();
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

  if (sensorStateLeft == 0 && sensorStateRight == 1)
  {
    analogWrite(motorLeftSpeed, reducedSpeed);
    analogWrite(motorRightSpeed, speed);
  }
  else if (sensorStateLeft == 1 && sensorStateRight == 0)
  {
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, reducedSpeed);
  }
  else if (sensorStateLeft == 1 && sensorStateCenter == 0 && sensorStateRight == 1)
  {
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, speed);
  }
  else if (sensorStateLeft == 1 && sensorStateCenter == 1 && sensorStateRight == 1)
  {
    delay(500);
    if (digitalRead(sensorLeft) == 1 && digitalRead(sensorCenter) == 1 && digitalRead(sensorRight) == 1)
    {
      analogWrite(motorLeftSpeed, reducedSpeed);
      analogWrite(motorRightSpeed, reducedSpeed);
    }
  }
}