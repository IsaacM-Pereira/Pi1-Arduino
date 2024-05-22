volatile int cont = 0;//Por ser uma funcao de interrupcao externa, o tipo 'volatil' e necessario para ser manipulado
int voltas = 0;

void setup() {
  pinMode(3, INPUT); //Definindo pin do Arduino
  attachInterrupt(digitalPinToInterrupt(3), interrupcao, RISING);//Configirando interrupcao externa de LOW para HIGH (RISING)
  Serial.begin(9600);//Configurando serial
  Serial.println(" - Inicio - ");
}

void loop() {
  delay(1000);i
  detachInterrupt(digitalPinToInterrupt(3));//Desativando a interrupcao
  //voltas = (cont/20)*60;//Mostrando a cada segundo
  voltas = (cont*3);//Mostra resultados de velocidade com mais precisao
  Serial.println(voltas);
  cont = 0;
  attachInterrupt(digitalPinToInterrupt(3), interrupcao, RISING);
}

void interrupcao(){
  cont++;
}
