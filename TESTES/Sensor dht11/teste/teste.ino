#include <DHT.h>

// Definição das portas
#define DHTPIN 4        // Pino do DHT11
#define DHTTYPE DHT11   // Define o tipo de sensor como DHT11
const int motor_n1 = 7; // Pino N1 do driver de motor
const int motor_n2 = 6; // Pino N2 do driver de motor
const int motor_pwm = 10; // Pino PWM do driver de motor

DHT dht(DHTPIN, DHTTYPE); // Inicializa o sensor DHT11

// Configurações da rampa
const int TEMPO_RAMPA = 50; // Tempo de incremento da rampa em milissegundos

void setup() {
  // Configuração das portas como saídas
  pinMode(motor_n1, OUTPUT);
  pinMode(motor_n2, OUTPUT);
  pinMode(motor_pwm, OUTPUT);

  // Inicializa o motor desligado
  digitalWrite(motor_n1, LOW);
  digitalWrite(motor_n2, LOW);
  analogWrite(motor_pwm, 0);

  // Inicializa o sensor DHT11
  dht.begin();

  // Inicia a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Faz a leitura da temperatura
  float temperatura = dht.readTemperature();

  // Verifica se a leitura da temperatura é válida
  if (isnan(temperatura)) {
    Serial.println("Falha ao ler a temperatura!");
    return;
  }

  // Exibe a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Verifica se a temperatura ultrapassa 50°C
  if (temperatura > 50) {
    // Liga o motor (N1 alto e N2 baixo)
    digitalWrite(motor_n1, HIGH);
    digitalWrite(motor_n2, LOW);
    Serial.println("Motor acelerando!");

    // Rampa de aceleração
    for (int i = 0; i < 256; i = i + 10) {
      analogWrite(motor_pwm, i);
      delay(TEMPO_RAMPA); // intervalo para incrementar a velocidade
    }

    // Mantém o motor ligado enquanto a temperatura estiver acima de 50°C
    while (temperatura > 50) {
      // Atualiza a leitura da temperatura
      temperatura = dht.readTemperature();

      // Verifica se a leitura da temperatura é válida
      if (isnan(temperatura)) {
        Serial.println("Falha ao ler a temperatura!");
        return;
      }

      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");

      delay(2000); // Atraso para próxima leitura
    }

    // Quando a temperatura cair abaixo de 50°C, inicia a desaceleração
    Serial.println("Motor desacelerando!");

    // Rampa de desaceleração
    for (int i = 255; i >= 0; i = i - 10) {
      analogWrite(motor_pwm, i);
      delay(TEMPO_RAMPA); // intervalo para diminuir a velocidade
    }

    // Desliga o motor
    digitalWrite(motor_n1, LOW);
    digitalWrite(motor_n2, LOW);
    Serial.println("Motor desligado.");
  }

  // Aguarda 2 segundos antes da próxima leitura
  delay(2000);
}
