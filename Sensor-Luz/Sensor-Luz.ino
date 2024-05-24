#define TCRT5000 2 // Pin conectado ao output TCRT5000 (não necessariamente usaremos esse output)

const int motorPinDireita = 6;
const int motorPinEsquerda = 9;

void setup() {
  Serial.begin(9600); //Inicia comunicação entre o Arduino e o computador em 9600 bits por segundo.
  pinMode(TCRT5000, INPUT);
  pinMode(motorDireito, OUTPUT);
  pinMode(motorEsquerdo, OUTPUT);
}

void loop() { //Funcao principal
  sensoresRGB();
}

/*
* Dentre as opções possíveis para as detecções dos sensores, temos (8): 
* P, B, B
* P, P, B
* P, P, P
* B, P, P
* B, B, P
* B, P, B
* P, B, P
* B, B, B
* considero que não focaremos, apenas, na possibilidade 'P, P, P' e 'P, B, P'. Ou seja, temos 6 casos.
*/
void sensoresRGB(){ //Definindo HIGH == 'preto' e LOW == 'branco'.
  int sCentral = digitalRead(TCRT5000);
  int sEsquerda = digitalRead(TCRT5000);
  int sDireita = digitalRead(TCRT5000);
  // No caso, as variáveis recebem entrada do mesmo sensor (TCRT5000), mas devem ser sensores diferentes. As entradas dos sensores dependem do nosso projeto e devemos especificá-las.
  if(sEsquerda == LOW && sCentral == LOW && sDireita == LOW){ //Caso os sensores não vejam nada
    digitalWrite(motorDireito, LOW);
    digitalWrite(motorEsquerdo, LOW);
  }else if(sEsquerda == HIGH && sCentral == LOW && sDireita == LOW){ //P, B, B
    digitalWrite(motorDireito, 255); //100% no motor direito
    digitalWtite(motorEsquerdo, 128); //50% no motor esquerdo
  }else if(sEsquerda == HIGH && sCentral == HIGH && sDireita == LOW){ //P, P, B
    digitalWrite(motorDireito, 255);
    digitalWrite(motorEsquerdo, 128);
  }else if(sEsquerda == LOW && sCentral == HIGH && sDireita == HIGH){ //B, P, P
    digitalWrite(motorDireito, 128);
    digitalWrite(motorEsquerdo, 255);
  }else if(sEsquerda == LOW && sCentral == LOW && sDireita == HIGH){ //B, B, P
    digitalWrite(motorDireito, 128);
    digitalWrite(motorEsquerdo, 255);
  }else if(sEsquerda == LOW && sCentral == HIGH && sDireita == LOW){ //B, P, B
    digitalWrite(motorDireito, 255);
    digitalWtite(motorEsquerdo, 255);
  }else if(sEsquerda == LOW && sCentral == LOW && sDireita == LOW){ //B, B, B
    delay(1000); //Aqui os sensores não enxergam nada. O que faríamos mesmo? 
  }

  delay(1000);
}












































