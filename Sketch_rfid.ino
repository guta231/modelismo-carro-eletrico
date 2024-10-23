#include <WiFi.h>
#include <PubSubClient.h>


#define RXD1 16   // Pino RX da Serial1 (conectado ao Arduino 1)
#define TXD1 17   // Pino TX da Serial1 (não usado)

#define RXD2 18   // Pino RX da Serial2 (conectado ao Arduino 2)
#define TXD2 19   // Pino TX da Serial2 (não usado)


const char* ssid = "A34 de Gustavo";
const char* password = "gustavogostoso";
const char* IP_MQTT = "4.228.225.124";

WiFiClient(espClient);
PubSubClient client(espClient);


void connectwifi(){
  if (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
  }else{
    Serial.print("WiFi conectado");
  }
}

void setup() {
  // Inicializa as duas portas seriais para os Arduinos
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); // Comunicação com Arduino 1
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // Comunicação com Arduino 2
  connectwifi();
  client.setServer(IP_MQTT, 1883);
  // Inicializa a Serial padrão para monitoramento via USB
  Serial.begin(115200);
  Serial.println("Esperando dados dos Arduinos...");
}

void loop() {
  if (!client.connected()){
    Serial.print(".");
    client.connect("device004");
    if (client.connected()){
      Serial.print("Dispositivo conectado ao Broker");
    }
  }
  // Verifica se há dados vindos do Arduino 1
  if (Serial1.available()) {
    String rfidData1 = Serial1.readStringUntil('\n'); // Lê o UID do Arduino 1
    Serial.print("Recebido do Arduino 1: ");
    Serial.println(rfidData1);  // Exibe no monitor serial do ESP32
    client.publish("/TEF/device004/attrs/ID_car", rfidData1.c_str());
  }

  // Verifica se há dados vindos do Arduino 2
  if (Serial2.available()) {
    String rfidData2 = Serial2.readStringUntil('\n'); // Lê o UID do Arduino 2
    Serial.print("Recebido do Arduino 2: ");
    Serial.println(rfidData2);  // Exibe no monitor serial do ESP32
    client.publish("/TEF/device004/attrs/ID_car", rfidData2.c_str());
  }
  client.loop();
}
