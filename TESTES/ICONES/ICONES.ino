#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define ícones personalizados (5x8 pixels)
byte confirm_icon[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte navigate_icon[8] = {
  B00000,
  B00100,
  B00110,
  B00111,
  B00110,
  B00100,
  B00000,
  B00000
};

void setup() {
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();

  // Cria os ícones personalizados
  lcd.createChar(0, confirm_icon); // Ícone de confirmação (OK)
  lcd.createChar(1, navigate_icon); // Ícone de navegação (Nav)

  // Exibe o texto na primeira linha
  lcd.setCursor(0, 0);  
  lcd.print("Teste");

  // Exibe os ícones e texto na segunda linha
  lcd.setCursor(8, 1);
  lcd.print("Ok");      // Exibe "OK"
  lcd.write(0);          // Exibe o ícone de confirmação

  lcd.setCursor(12, 1);   // Move o cursor para a posição 9
  lcd.print("Nav");     // Exibe "Nav"
  lcd.write(1);          // Exibe o ícone de navegação
}

void loop() {
  // O resto do código para navegação do menu com os botões
}
