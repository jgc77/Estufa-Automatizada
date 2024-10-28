#include "Arduino.h"
#include "ControleIrrigacao.h"
//#include "Servo.h"


ControleIrrigacao::ControleIrrigacao(int pino_sens) {
 // _pino_servo = pino_servo;
  _pino_sens = pino_sens;
  _modo = 0; // Modo automático por padrão
  //umidade_limite = limite;
  //_valor_led_manual = 0; 
  //servo_motor.attach(_pino_servo);
  //servo_motor.write(0); // Inicialmente em 0 graus
  ultimoTempoAtualizacao = 0; // Inicializa a última atualização
  umidadeAtual = 0; // Valor inicial da umidade
}

void ControleIrrigacao::ajustarModo(String comando_serial) {
  comando_serial.trim(); // Remove espaços em branco ou novas linhas
  if (comando_serial == "automatico") {
    _modo = 0;
  } 
  else if (comando_serial == "manual") {
    _modo = 1;
  }
  //else if (_modo == 1) {
   // if (comando_serial == "servo on") {
    //  servo_motor.write(90);
    //  Serial.println("Servo ligado manualmente.");
   // } else if (comando_serial == "servo off") {
   //   servo_motor.write(0);
    //  Serial.println("Servo desligado manualmente.");
    //}
 // }
}

//void ControleIrrigacao::atualizar() {
//  if (_modo == 0) {
  //  int valorumidade = analogRead(_pino_sens); // Lê o sensor (0 a 1023)
    //Serial.print("Valor do sensor de umidade: ");
    //Serial.println(valorumidade);
    //if (valorumidade < umidade_limite) {
    //  servo_motor.write(90); // Ativa o servo
    //} else {
    //  servo_motor.write(0); // desativa servo
    ///}
  //}
//}

int ControleIrrigacao::lersolo() {
  if (millis() - ultimoTempoAtualizacao >= intervaloAtualizacao) {
    ultimoTempoAtualizacao = millis();
    int leituraAnalogica = analogRead(_pino_sens); // Atualiza a leitura
    umidadeAtual = map(leituraAnalogica, 1023, 0, 0, 100); // Converte para porcentagem
  }
  return umidadeAtual; // Retorna o valor em porcentagem
}