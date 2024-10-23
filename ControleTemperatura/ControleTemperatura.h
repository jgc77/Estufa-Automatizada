#ifndef ControleTemperatura_h
#define ControleTemperatura_h

#include "Arduino.h"
#include "DHT.h"

class ControleTemperatura {
  public:
    ControleTemperatura(int pino_dht, int pino_saida1, int pino_saida2);
    void ajustarModo(String comando_serial);  // Função para ajustar o modo
    void atualizar();  // Função para atualizar e verificar a temperatura
  private:
    int _pino_dht;
    int _pino_saida1;
    int _pino_saida2;
    int _modo;  // 0 = Automático, 1 = Manual
    int _manual_motor;  // Estado manual do motor
    DHT* _dht;
};

#endif
