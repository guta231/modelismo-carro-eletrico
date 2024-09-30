#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Pinos do motor
const int in1 = 18; // IN1 do motor 1
const int in2 = 19; // IN2 do motor 1
const int in3 = 21; // IN1 do motor 2
const int in4 = 5;  // IN2 do motor 2

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car"); // Nome do dispositivo Bluetooth
  Serial.println("O dispositivo está pronto para emparelhar!");

  // Configura os pinos dos motores como saída
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read(); // Lê o comando enviado via Bluetooth

    if (command == 'F'){
      analogWrite(in2, 255);
      analogWrite(in4, 255);
      analogWrite(in1, 0);
      analogWrite(in3, 0);
    }else if (command == 'B') {
      analogWrite(in1, 255);
      analogWrite(in3, 255);
      analogWrite(in2, 0);
      analogWrite(in4, 0);
    }else if (command == 'R'){
      analogWrite(in1, 0);
      analogWrite(in2, 0);
      analogWrite(in3, 0);
      analogWrite(in4, 255);
    }else if (command == 'L'){
      analogWrite(in1, 0);
      analogWrite(in2, 255);
      analogWrite(in3, 0);
      analogWrite(in4, 0);
    }else{
      analogWrite(in1, 0);
      analogWrite(in2, 0);
      analogWrite(in3, 0);
      analogWrite(in4, 0);
    }
    // Comandos de controle
  }
}
