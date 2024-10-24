
#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "";
const char* password = "";
const char* IP_MQTT = "4.228.225.124";

const int pulsePin = 4;  // Pino conectado ao sensor de pulso
volatile int pulseCount = 0;  // Contador de pulsos

// Variáveis para cálculo de velocidade
const float wheelCircumference = 33.0;  // Circunferência da roda em centímetros
const int encoderFuros = 20;  // Quantidade de furos no encoder

// Tempo
unsigned long previousTime = 0;
const unsigned long interval = 1000;  // Intervalo de 1 segundo para cálculo da velocidade

WiFiClient espClient;
PubSubClient client(espClient);

float velocidade_max;

void connectWifi(){

  if (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);

    if (WiFi.status() == WL_CONNECTED){
      Serial.println("Conectado a Rede WIFI");
    }
  }


}

// Função de interrupção para contar os pulsos
void IRAM_ATTR pulseISR() {
  pulseCount++;  // Incrementa o contador de pulsos sempre que uma interrupção ocorre
}

void setup() {
  Serial.begin(115200);

  // Configura o pino do sensor de pulso como entrada
  pinMode(pulsePin, INPUT_PULLUP);


  // Ativa a interrupção no pino do sensor de pulso (na borda de descida)
  attachInterrupt(digitalPinToInterrupt(pulsePin), pulseISR, FALLING);

  Serial.println("Iniciando a leitura da velocidade...");

  connectWifi();
  
  client.setServer(IP_MQTT, 1883);
}


void loop() {
  if (!client.connected()){
    Serial.print(".");
    client.connect("device001");
    delay(1000);
    if (client.connected()){
      Serial.println("Dispositivo conectado ao broker");
    }
  }
  unsigned long currentTime = millis();

  // Calcula a velocidade a cada 1 segundo
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;

    // Número de rotações (cada rotação completa equivale a 20 pulsos)
    float rotations = pulseCount / (float)encoderFuros;

    // Calcula a distância percorrida em cm (rotações * circunferência da roda)
    float distanceCm = rotations * wheelCircumference;

    // Velocidade (distância por segundo em cm/s)
    float speedCmPerSecond = distanceCm;

    // Velocidade em km/h (convertendo cm/s para km/h)
    float velocidade = (speedCmPerSecond / 100.0) * 3.6;

    // Exibe a velocidade no monitor serial
    Serial.print("Velocidade: ");
    Serial.print(velocidade);
    Serial.println(" km/h");

  if (velocidade > velocidade_max){
    velocidade_max = velocidade;
  }
  

  Serial.println("Velocidade 1: " + String(velocidade));

  String mensagem = String(velocidade);

  String mensagem_velocidade_max = String(velocidade_max);

  client.publish("/TEF/device001/attrs/velocidade", mensagem.c_str());
  client.publish("/TEF/device001/attrs/velocidade_max",mensagem_velocidade_max.c_str());
    // Reseta o contador de pulsos
    pulseCount = 0;
  }
  
  client.loop();
}
