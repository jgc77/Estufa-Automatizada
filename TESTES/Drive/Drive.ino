#include "ControleTemperatura.h"

// Definir os pinos utilizados
#define PINO_DHT 4
#define PINO_SAIDA1 6
#define PINO_SAIDA2 7

// Criar uma instância da classe ControleTemperatura
ControleTemperatura controle(PINO_DHT, PINO_SAIDA1, PINO_SAIDA2);

void setup() {
  // Inicializa a comunicação serial para o monitoramento
  Serial.begin(9600);
  Serial.println("Sistema de Controle de Temperatura iniciado.");
  Serial.println("Comandos disponíveis:");
  Serial.println("'automatico' - Ativa o modo automático.");
  Serial.println("'manual' - Ativa o modo manual.");
  Serial.println("'motor on' - Liga o motor manualmente (modo manual).");
  Serial.println("'motor off' - Desliga o motor manualmente (modo manual).");
}

void loop() {
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {
    // Lê o comando da serial
    String comando = Serial.readString();
    // Ajusta o modo ou controla o motor com base no comando recebido
    controle.ajustarModo(comando);
  }

  // Atualiza o controle (verifica temperatura ou estado manual)
  controle.atualizar();

  // Pequeno atraso para evitar leitura excessiva
  delay(500);
}
