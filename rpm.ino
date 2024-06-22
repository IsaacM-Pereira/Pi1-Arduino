#define D_Sensor_2 2
 
volatile double velocity_i_2 = 0;
volatile long prevT_i_2 = 0;
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 100; // Intervalo de tempo para plotar (em milissegundos)

const unsigned long lastPrintTime = 500;

void setup() {
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(D_Sensor_2), readEncoder2, RISING);
}
 
void readEncoder2() {
    // Esta função captura o intervalo de tempo entre os pulsos do sensor de velocidade 2
    // e transforma o tempo em velocidade a partir de pulso por segundos
 
    long currT2 = micros();
    double deltaT2 = ((double)(currT2 - prevT_i_2)) / 1.0e6;
 
    // Caso o tempo entre medições seja muito pequeno, o valor da velocidade
    // tende a infinito, o que não é desejável, por isso são ignoradas medições
    // que ocorram em menos de 0.015 segundo
  


    if (deltaT2 >= 0.015) {
        velocity_i_2 = 1 / deltaT2;
 
        // Salva o momento da última medição
        prevT_i_2 = currT2;
    }
}
 
void loop() {
    // Verifica se é hora de enviar os dados para o Serial Plotter
    unsigned long currentMillis = millis();
    if (currentMillis - lastPrintTime >= printInterval) {
        lastPrintTime = currentMillis;
    
      if (currentMillis - (prevT_i_2 / 1000) > timeoutInterval) {             
        velocity_i_2 = 0; }
        // Calcula a velocidade em RPM e envia para o Serial Plotter
        double velocityRPM = velocity_i_2 / 20.0 * 60.0;
        Serial.println(velocityRPM);
    }
 
    // O loop principal pode executar outras tarefas enquanto a interrupção cuida das leituras do encoder
}