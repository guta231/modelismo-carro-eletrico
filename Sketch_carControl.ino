#include <SoftwareSerial.h>
#include <IRremote.h> // Biblioteca para o receptor infravermelho

SoftwareSerial Bluetooth(2, 8); // RX, TX do Bluetooth

const int in1 = 9; // IN1 do motor 1
const int in2 = 6; // IN2 do motor 1
const int in3 = 5; // IN1 do motor 2
const int in4 = 3; // IN2 do motor 2

const int irReceiverPin = 7; // Pino de entrada do receptor IR
IRrecv irrecv(irReceiverPin); // Inicializa o receptor IR
decode_results results; // Armazena o código decodificado

void setup() {
  Serial.begin(9600);      // Inicializa a comunicação serial com o Serial Monitor
  Bluetooth.begin(9600);   // Inicializa a comunicação serial com o módulo Bluetooth
  
  Serial.println("Módulo Bluetooth pronto. Aguarde comandos...");
  
  // Configura os pinos dos motores como saída
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Inicializa o receptor IR
  irrecv.enableIRIn(); // Inicia o receptor IR
}

void loop() {
  // Verifica se um código infravermelho foi recebido
  if (irrecv.decode(&results)) {
    Serial.print("Código IR recebido: ");
    Serial.println(results.value, HEX); // Mostra o código IR recebido no Serial Monitor

    // Envia o código IR via Bluetooth
    Bluetooth.print("Código IR: ");
    Bluetooth.println(results.value, HEX);

    irrecv.resume(); // Prepara o receptor para receber o próximo código
  }

  // Controle dos motores com comandos via Serial Monitor
  if (Serial.available()) {
    char btCommand = Serial.read(); // Lê o caractere do Serial Monitor
    Serial.print("Comando recebido do Serial: ");
    Serial.println(btCommand); // Mostra no Serial Monitor

    // Envia o comando para o módulo Bluetooth
    Bluetooth.print("Comando recebido: ");
    Bluetooth.println(btCommand); 

    // Controle dos motores
    controleMotores(btCommand);
  }

  // Controle dos motores com comandos via Bluetooth
  if (Bluetooth.available()) {
    char btCommand = Bluetooth.read(); // Lê o caractere recebido do Bluetooth
    Serial.print("Comando recebido do Bluetooth: ");
    Serial.println(btCommand); // Mostra no Serial Monitor

    // Opcional: responder ao Bluetooth
    Bluetooth.print("Recebido via Bluetooth: ");
    Bluetooth.println(btCommand);
    
    // Controle dos motores
    controleMotores(btCommand);
  }
}

void controleMotores(char command) {
  if (command == 'F') {       // Frente
    analogWrite(in2, 255);
    analogWrite(in4, 255);
    analogWrite(in1, 0);
    analogWrite(in3, 0);
  } else if (command == 'B') { // Ré
    analogWrite(in1, 255);
    analogWrite(in3, 255);
    analogWrite(in2, 0);
    analogWrite(in4, 0);
  } else if (command == 'R') { // Direita
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 255);
  } else if (command == 'L') { // Esquerda
    analogWrite(in1, 0);
    analogWrite(in2, 255);
    analogWrite(in3, 0);
    analogWrite(in4, 0);
  } else {                      // Parado
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 0);
  }
}
