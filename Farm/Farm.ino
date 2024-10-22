#include <ControleLuminosidade.h>
#include <MenuLCD.h>

// Definir os pinos dos botões
const uint8_t botao1_pin = 2;
const uint8_t botao2_pin = 3;

// Definir os pinos do LDR e LED
const int pino_led = 9;
const int pino_ldr = A0;

// Criar instâncias das bibliotecas
MenuLCD menu(0x27, 16, 2, botao1_pin, botao2_pin);              // Menu para o LCD 16x2
ControleLuminosidade controleLuminosidade(pino_led, pino_ldr);  // Controle de luminosidade

void setup() {
  // Iniciar os módulos de menu e controle de luminosidade
  menu.iniciar();
  Serial.begin(9600);
  pinMode(5, OUTPUT);  //LED de Power
}

void loop() {

  //LED power
  digitalWrite(5, HIGH);

  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    controleLuminosidade.ajustarModo(comando);
  }
  controleLuminosidade.atualizar();

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
