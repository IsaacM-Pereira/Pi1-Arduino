# Projeto Integrador Arduino

Este projeto é um guia básico para programar um Arduino e criar um AGV (Automated Guided Vehicle).

## Programando no Arduino

Programar no Arduino é uma tarefa simples e intuitiva, especialmente para aqueles que já têm alguma experiência com C/C++. Se você é novo na programação, não se preocupe, a [documentação oficial do Arduino](https://www.arduino.cc/reference/en/) é um excelente ponto de partida.

## Simulando no Tinkercad

O [Tinkercad](https://www.tinkercad.com/) é uma plataforma online que permite simular circuitos eletrônicos, incluindo Arduino. É uma ferramenta útil para testar seu código antes de transferi-lo para o hardware físico. Confira a [documentação do Tinkercad](https://www.tinkercad.com/learn/) para aprender mais.

## AGV (Automated Guided Vehicle)

Um AGV é um veículo autônomo que segue uma rota definida, geralmente através de linhas traçadas no chão ou sinais de rádio, luzes, ou magnetismo. Ele usa sensores para detectar a rota e um algoritmo para ajustar a direção do veículo com base na posição da rota detectada.

O AGV é geralmente equipado com dois motores que controlam as rodas esquerda e direita. O algoritmo ajusta a velocidade de cada motor para fazer o veículo virar à esquerda ou à direita, conforme necessário, para seguir a rota.

## Módulos do AGV

### Sensor de Luz

O sensor de luz utiliza um sensor infravermelho para avaliar quando fazer ou não a curva. Ele diminui a tensão quando necessário para fazer a curva e desliga após 1 segundo com os três sensores em branco.

### Sensor de RPM

O sensor de RPM é usado para salvar o RPM das rodas durante o percurso. Esses dados são armazenados em um arquivo CSV para realizar o cálculo da velocidade em relação ao tempo posteriormente.
