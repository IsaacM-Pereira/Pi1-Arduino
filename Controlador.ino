// Define os pinos para os botões
const int buttonPin1 = A3; // botão da esquerda
const int buttonPin2 = A4; // botão do meio
const int buttonPin3 = A5; // botão da direita

// Define os pinos para os motores
const int motorRightSpeed = 9; // pino de velocidade do motor da direita
const int motorRightDirection = 10; // pino de direção do motor da direita
const int motorLeftSpeed = 5; // pino de velocidade do motor da esquerda
const int motorLeftDirection = 6; // pino de direção do motor da esquerda

// Define a velocidade padrão e a velocidade reduzida
const int speed = 20;
const int reducedSpeed = 16; // metade da velocidade padrão

const int volt = 912;

void setup()
{
  Serial.begin(9600);
  pinMode(motorRightSpeed, OUTPUT);
  pinMode(motorRightDirection, OUTPUT);
  pinMode(motorLeftSpeed, OUTPUT);
  pinMode(motorLeftDirection, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop()
{
  // Lê o estado dos botões
  int buttonState1 = analogRead(buttonPin1);
  int buttonState2 = analogRead(buttonPin2);
  int buttonState3 = analogRead(buttonPin3);


  // Verifica o estado dos botões e ajusta a velocidade dos motores de acordo
  if (buttonState1 > volt && buttonState3 <= volt) {
    // Se o botão da esquerda estiver pressionado, diminui a velocidade do motor da esquerda e aumenta a do motor da direita
    analogWrite(motorLeftSpeed, reducedSpeed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (buttonState3 > volt && buttonState1 <= volt) {
    // Se o botão da direita estiver pressionado, diminui a velocidade do motor da direita e aumenta a do motor da esquerda
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, reducedSpeed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (buttonState2 > volt) {
    // Se o botão do meio estiver pressionado, define a mesma velocidade para ambos os motores
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (buttonState1 <= volt && buttonState2 <= volt && buttonState3 <= volt) {
    // Se todos os botões estiverem desligados por mais de 600 ms, desliga os motores
    delay(600);
    if (analogRead(buttonPin1) <= volt && analogRead(buttonPin2) <= volt && analogRead(buttonPin3) <= volt) {
      analogWrite(motorLeftSpeed, 0);
      digitalWrite(motorLeftDirection, LOW); // Inverte a direção
      analogWrite(motorRightSpeed, 0);
      digitalWrite(motorRightDirection, LOW); // Inverte a direção
    }
  }
}
