#ifndef MenuLCD_h
#define MenuLCD_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class MenuLCD {
  public:
    MenuLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t btn1_pin, uint8_t btn2_pin);
    void iniciar();
    void atualizar();
    void atualizarLuminosidade();
    void atualizarTemperatura();
    void atualizarUmidade();
    void atualizarUmisolo();
    void setTemperatura(float temp);
    void setUmidade(float umid);
    void setLuminosidade(float lumi);
    void setUmisolo(float umidso);

  private:
    LiquidCrystal_I2C lcd;
    uint8_t botao_1;
    uint8_t botao_2;
    int menu_atual;
    bool dentro_submenu;
    int estado_anterior_botao_1;
    int estado_anterior_botao_2;
    float temperatura;
    float umidade;
    float luminosidade;
    float umisolo;
    void mostrarMenu();
    void mostrarSubmenu();
};

#endif
