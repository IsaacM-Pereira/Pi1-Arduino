#include <SPI.h>
#include <SD.h>

//Funcao controlador()
const int pinMotorEsquerda = 4;
const int pinMotorMeio = 3; 
const int pinMotorDireita = 2; 
const int motorRightSpeed = 9; 
const int motorRightDirection = 10; 
const int motorLeftSpeed = 5; 
const int motorLeftDirection = 6; 
const int speed = 20;
const int reducedSpeed = 16; // metade da velocidade padrão

//Funcao leitorRpm()
volatile int cont = 0; 
int voltas = 0;

//Funcao lerConteudoSD()
const int pinoSD = 10; //Exemplo de pino. Precisa ser mudado!!

void setup(){
  //Setup para funcao controlador()
  Serial.begin(9600);
  pinMode(motorRightSpeed, OUTPUT);
  pinMode(motorRightDirection, OUTPUT);
  pinMode(motorLeftSpeed, OUTPUT);
  pinMode(motorLeftDirection, OUTPUT);
  pinMode(pinMotorEsquerda, INPUT);
  pinMode(pinMotorMeio, INPUT);
  pinMode(pinMotorDireita, INPUT);

  //Setup para a funcao leitorRpm()
  pinMode(3, INPUT); //Definindo pin do Arduino - CONFLITO AQUI!!!
  attachInterrupt(digitalPinToInterrupt(3), interrupcao(), RISING);//Configirando interrupcao externa de LOW para HIGH (RISING)
  Serial.begin(9600);//Configurando serial

  //Setup para funcoes escreverSD() e lerSD()
  escreverSD();
  lerConteudoSD();
}

void loop(){
  controlador();
  leitorRpm();
}

void leitorRpm(){
  delay(1000);
  detachInterrupt(digitalPinToInterrupt(3));//Desativando a interrupcao
  //voltas = (cont/20)*60;//Mostrando a cada segundo
  voltas = (cont*3);//Mostra resultados de velocidade com mais precisao
  Serial.println(voltas);
  cont = 0;
  attachInterrupt(digitalPinToInterrupt(3), interrupcao(), RISING);
}
void interrupcao(){
  cont++;
}

void controlador(){
  // Lê o estado dos botões
  int pinEstateEsquerda = digitalRead(pinMotorEsquerda);
  int pinEstateMeio = digitalRead(pinMotorMeio);
  int pinEstateDireita = digitalRead(pinMotorDireita);

  if (pinEstateEsquerda == HIGH && pinEstateDireita == LOW) {
    // Se o botão da esquerda estiver pressionado, diminui a velocidade do motor da esquerda e aumenta a do motor da direita
    analogWrite(motorLeftSpeed, reducedSpeed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (pinEstateDireita == HIGH && pinEstateEsquerda == LOW) {
    // Se o botão da direita estiver pressionado, diminui a velocidade do motor da direita e aumenta a do motor da esquerda
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, reducedSpeed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (pinEstateMeio == HIGH) {
    // Se o botão do meio estiver pressionado, define a mesma velocidade para ambos os motores
    analogWrite(motorLeftSpeed, speed);
    digitalWrite(motorLeftDirection, LOW); // Inverte a direção
    analogWrite(motorRightSpeed, speed);
    digitalWrite(motorRightDirection, LOW); // Inverte a direção
  } else if (pinStateEsquerda == LOW && pinEstateMeio == LOW && pinEstateDireita == LOW) {
    // Se todos os botões estiverem desligados por mais de 600 ms, desliga os motores
    delay(600);
    if (digitalRead(buttonPin1) == LOW && digitalRead(buttonPin2) == LOW && digitalRead(buttonPin3) == LOW) {
      analogWrite(motorLeftSpeed, 0);
      digitalWrite(motorLeftDirection, LOW); // Inverte a direção
      analogWrite(motorRightSpeed, 0);
      digitalWrite(motorRightDirection, LOW); // Inverte a direção
    }
  }
}

void escreverSD(){
  Serial.print("Inicializando SD");
  if(!SD.begin(pino)){
    Serial.println("Falha na comunicacao com SD");
    return;
  }
  Serial.println("Cartao SD inicializado - Funcao: escreverSD");

  File arquivo = SD.open("arquivo.txt", FILE_WRITE);

  if(arquivo){
    Serial.println("O seguinte sera escrito no arquivo: 'Hello world!'");
    arquivo.prinln("Hello world!");
  }else{
    Serial.println("Erro ao abrir arquivo e escrever!");
  }
}

void lerConteudoSD(){
  Serial.begin(9600);
  while (!Serial) {
    ; // Aguarde até que a porta serial esteja pronta
  }

  Serial.print("Inicializando o cartão SD...");
  if (!SD.begin(pinoSD)) {
    Serial.println("Falha na inicialização do cartão SD!");
    return;
  }
  Serial.println("Cartão SD inicializado.");

  File arquivoAGV = SD.open("dadosAGV.txt");
  if (arquivoAGV) {
    Serial.println("dadosAGV.txt:");
    
    while (arquivoAGV.available()) {
      char c = arquivoAGV.read();
      Serial.print(c);
    }
    arquivoAGV.close();
  } else {
    Serial.println("Erro ao abrir dadosAGV.txt");
  }
}
