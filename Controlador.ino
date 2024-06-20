// Define os pinos para os sensores
const int sensorLeft = 11; // sensor da esquerda
const int sensorCenter = 12; // sensor do meio
const int sensorRight = 13; // sensor da direita

// Define o numero de leituras para a média do sensor
const int numReadings = 10;


// Define os pinos para os motores
const int motorRightSpeed = 9; // pino de velocidade do motor da direita
const int motorRightDirection = 10; // pino de direção do motor da direita
const int motorLeftSpeed = 5; // pino de velocidade do motor da esquerda
const int motorLeftDirection = 6; // pino de direção do motor da esquerda

// Define a velocidade padrão e a velocidade reduzida
const int speed = 20;
const int reducedSpeed = 0; // metade da velocidade padrão

void setup()
{
  Serial.begin(9600);
  pinMode(motorRightSpeed, OUTPUT);
  pinMode(motorRightDirection, OUTPUT);
  pinMode(motorLeftSpeed, OUTPUT);
  pinMode(motorLeftDirection, OUTPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight, INPUT);

  digitalWrite(motorRightDirection, LOW);
  digitalWrite(motorLeftDirection, LOW);
}

void loop()
{
  controlador();
}

int readSensorAverage(int sensorPin) {
  int total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += digitalRead(sensorPin);
    delay(10); // delay between readings
  }
  return total / numReadings;
}


void controlador()
{
    // Lê o estado dos sensores
  int sensorStateLeft = readSensorAverage(sensorLeft);
  int sensorStateCenter = readSensorAverage(sensorCenter);
  int sensorStateRight = readSensorAverage(sensorRight);

  // Verifica o estado dos sensores e ajusta a velocidade dos motores de acordo
  if (sensorStateLeft == HIGH && sensorStateRight == LOW) {
    // Se o sensor da esquerda estiver ativo, diminui a velocidade do motor da esquerda
    analogWrite(motorLeftSpeed, reducedSpeed);
    analogWrite(motorRightSpeed, speed);
  } else if (sensorStateLeft == LOW && sensorStateRight == HIGH) {
    // Se o sensor da direita estiver ativo, diminui a velocidade do motor da direita
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, reducedSpeed);
  } else if (sensorStateLeft == LOW && sensorStateCenter == HIGH && sensorStateRight == LOW) {
    // Se o sensor do meio estiver ativo, define a mesma velocidade para ambos os motores
    analogWrite(motorLeftSpeed, speed);
    analogWrite(motorRightSpeed, speed);
  } else if (sensorStateLeft == LOW && sensorStateCenter == LOW && sensorStateRight == LOW) {
    // Se todos os sensores estiverem desativados por mais de 600 ms, desliga os motores
    delay(600);
    if (digitalRead(sensorLeft) == LOW && digitalRead(sensorCenter) == LOW && digitalRead(sensorRight) == LOW) {
      analogWrite(motorLeftSpeed, 0);
      analogWrite(motorRightSpeed, 0);
    }
  }
}