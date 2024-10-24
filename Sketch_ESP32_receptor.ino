void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial a 9600 bps
}

void loop() {
    if (Serial.available()) { // Verifica se há dados disponíveis
        String codigoIR = Serial.readStringUntil('\n'); // Lê até a nova linha
        Serial.print("Recebido do Arduino: ");
        Serial.println(codigoIR); // Exibe o código IR recebido
    }
}
