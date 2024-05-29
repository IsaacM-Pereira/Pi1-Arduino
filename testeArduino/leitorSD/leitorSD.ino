#include <SPI.h>
#include <SD.h>

const int pino = 10; //Exemplo de pino onde está conectado o leitor de SD no Arduino

void setup(){
  Serial.begin(9600);

  escreverSD();
  lerSD();
}

void loop(){

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
    Serial.println("O seguinte sera escrito no arquivo:");
    arquivo.prinln("Hello world!");
  }else{
    Serial.println("Erro ao abrir arquivo e escrever!");
  }
}

void lerSD(){
  Serial.begin(9600);

  Serial.println("Inicializando o SD");
  if(!SD.begin(pino)){
    Serial.println("Falha ao inicializar o SD");
    return;
  }
  Serial.println("Cartao SD inicializado - Funcao: lerSD");

  Serial.println("Lista de arquivos do cartao:\n\n");
  listaSD(SD.open("/", 0));

  // Abrir um arquivo e ler seu conteúdo
  File arquivo = SD.open("arquivo.txt");
  if (arquivo) {
    Serial.println("arquivo.txt:");
    while (arquivo.available()) {
      Serial.write(arquivo.read());
    }
    arquivo.close();
  } else {
    Serial.println("Erro ao abrir o arquivo example.txt");
  }
}

void listaSD(File dir, int numTabs){
    while (true) {
    File entrada = dir.openNextFile();
    if (!entrada) {
      // Sem mais arquivos
      break;
    }
    for (int i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entrada.isDirectory()) {
      Serial.println("/");
      printDirectory(entrada, numTabs + 1);
    } else {
      // Arquivo, imprime o tamanho
      Serial.print("\t\t");
      Serial.println(entrada.size(), DEC);
    }
    entrada.close();
  }
}