#include <ControleTemperatura.h>
#include <ControleLuminosidade.h>
#include <MenuLCD.h>

// Definir os pinos dos botões
const uint8_t botao1 = 2;
const uint8_t botao2 = 3;

// Definir os pinos do LDR e LED
const int led_uv = 9;
const int ldr = A0;

// Definir os pinos de temperatura
const int dht11 = 4;
const uint8_t motor1 = 6;
const uint8_t motor2 = 7;

// Criar instâncias das bibliotecas
MenuLCD menu(0x27, 16, 2, botao1, botao2);               // Menu para o LCD 16x2
ControleLuminosidade controleLuminosidade(led_uv, ldr);  // Controle de luminosidade
ControleTemperatura controle(dht11, motor1, motor2);     // Controle de Temperatura

void setup() {
  // Iniciar os módulos de menu e controle serial
  menu.iniciar();
  Serial.begin(9600);
  pinMode(5, OUTPUT);  //LED de Power
  Serial.println("ESTUFA AUTOMATIZADA");
  Serial.println("Bem vindo, escolha entre o modo manual e automatico.");
}

void loop() {

  //LED power
  digitalWrite(5, HIGH);

  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    if (comando == "automatico") {
      Serial.println("Modo automatico ativado.");
    } else if (comando == "manual") {
      Serial.println("Modo manual ativado");
    } else {
      Serial.println("Modo invalido! Escolha entre manual e automatico.");
    }
    controleLuminosidade.ajustarModo(comando);  //luminosidade
    controle.ajustarModo(comando);              //temperatura
  }
  controleLuminosidade.atualizar();
  controle.atualizar();  //temperatura

  // Obter o valor da luminosidade lida pelo LDR
  int luminosidade = controleLuminosidade.lerLDR();

  // Atualizar o valor da luminosidade na biblioteca de menu
  menu.setLuminosidade(luminosidade);

  // Atualizar o menu (navegação e exibição)
  menu.atualizar();

  // Atualizar a luminosidade na tela
  menu.atualizarLuminosidade();

  // Adicionar um pequeno delay para aliviar o loop
  delay(100);
}
