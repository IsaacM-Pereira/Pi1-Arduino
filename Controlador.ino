// Define os pinos para os sensores
const int sensorPin1 = A3; // sensor da esquerda
const int sensorPin2 = A4; // sensor do meio
const int sensorPin3 = A5; // sensor da direita

// Define os pinos para os motores
const int motorRightSpeed = 9; // pino de velocidade do motor da direita
const int motorRightDirection = 10; // pino de direção do motor da direita
const int motorLeftSpeed = 5; // pino de velocidade do motor da esquerda
const int motorLeftDirection = 6; // pino de direção do motor da esquerda

// Define a velocidade padrão e a velocidade reduzida
const int speed = 20;
const int reducedSpeed = 16; // metade da velocidade padrão

void setup()
{
  Serial.begin(9600);
  pinMode(motorRightSpeed, OUTPUT);
  pinMode(motorRightDirection, OUTPUT);
  pinMode(motorLeftSpeed, OUTPUT);
  pinMode(motorLeftDirection, OUTPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
}

void loop()
{
  // Lê o estado dos sensores
  int sensorState1 = digitalRead(sensorPin1);
  int sensorState2 = digitalRead(sensorPin2);
  int sensorState3 = digitalRead(sensorPin3);

  // Verifica o estado dos sensores e ajusta a velocidade dos motores de acordo
  if (sensorState1 == HIGH && sensorState3 == LOW) {
    // Se o sensor da esquerda estiver ativo, diminui a velocidade do motor da esquerda e aumenta a do motor da direita
    analogWrite(motorLeftSpeed, reducedSpeed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (sensorState3 == HIGH && sensorState1 == LOW) {
    // Se o sensor da direita estiver ativo, diminui a velocidade do motor da direita e aumenta a do motor da esquerda
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, reducedSpeed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (sensorState2 == HIGH) {
    // Se o sensor do meio estiver ativo, define a mesma velocidade para ambos os motores
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (sensorState1 == LOW && sensorState2 == LOW && sensorState3 == LOW) {
    // Se todos os sensores estiverem desativados por mais de 600 ms, desliga os motores
    delay(600);
    if (digitalRead(sensorPin1) == LOW && digitalRead(sensorPin2) == LOW && digitalRead(sensorPin3) == LOW) {
      analogWrite(motorLeftSpeed, 0);
      digitalWrite(motorLeftDirection, LOW); // Inverte a direção
      analogWrite(motorRightSpeed, 0);
      digitalWrite(motorRightDirection, LOW); // Inverte a direção
    }
  }
}
