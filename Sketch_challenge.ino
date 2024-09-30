#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(10, 11); // RX, TX

const int in1 = 9; // IN1 do motor 1
const int in2 = 6; // IN2 do motor 1
const int in3 = 5; // IN1 do motor 2
const int in4 = 3;  // IN2 do motor 2

void setup() {
  Serial.begin(9600);      // Inicializa a comunicação serial com o Serial Monitor
  Bluetooth.begin(9600);   // Inicializa a comunicação serial com o módulo Bluetooth
  
  Serial.println("Módulo Bluetooth pronto. Aguarde comandos...");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Verifica se há dados disponíveis para o Serial
  if (Serial.available()) {
    char btCommand = Serial.read(); // Lê o caractere do Serial Monitor
    Serial.print("Comando recebido do Serial: ");
    Serial.println(btCommand); // Mostra no Serial Monitor

    // Envia o comando para o módulo Bluetooth
    Bluetooth.print("Comando recebido: ");
    Bluetooth.println(btCommand); 

    // Controle dos motores
    
  }

  // Verifica se há dados disponíveis do Bluetooth
  if (Bluetooth.available()) {
    char btCommand = Bluetooth.read(); // Lê o caractere recebido do Bluetooth
    Serial.print("Comando recebido do Bluetooth: ");
    Serial.println(btCommand); // Mostra no Serial Monitor

    // Opcional: responder ao Bluetooth
    Bluetooth.print("Recebido via Bluetooth: ");
    Bluetooth.println(btCommand);
    if (btCommand == 'F'){
      analogWrite(in2, 255);
      analogWrite(in4, 255);
      analogWrite(in1, 0);
      analogWrite(in3, 0);
    } else if (btCommand == 'B') {
      analogWrite(in1, 255);
      analogWrite(in3, 255);
      analogWrite(in2, 0);
      analogWrite(in4, 0);
    } else if (btCommand == 'R'){
      analogWrite(in1, 0);
      analogWrite(in2, 0);
      analogWrite(in3, 0);
      analogWrite(in4, 255);
    } else if (btCommand == 'L'){
      analogWrite(in1, 0);
      analogWrite(in2, 255);
      analogWrite(in3, 0);
      analogWrite(in4, 0);
    } else {
      analogWrite(in1, 0);
      analogWrite(in2, 0);
      analogWrite(in3, 0);
      analogWrite(in4, 0);
    }
  }
}
