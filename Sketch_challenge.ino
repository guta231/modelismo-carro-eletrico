//*************** Definição dos Pinos ***********************
#define pinIN1 10    //Motor 1
#define pinIN2 9     //Motor 1
#define pinIN3 6     //Motor 2
#define pinIN4 5     //Motor 2 
#define pinPot1  A1  //Potenciometro Frente e Reverso
#define pinPot2  A2  //Potenciometro Direito e Esquerdo
#define pinBotao A3  //Botao
#define   pino_D0  3

int           rpm;
volatile byte pulsos;
unsigned long timeold;


unsigned int pulsos_por_volta = 20;

//variaveis dos botões
boolean botaoAnt = HIGH;
boolean botao    = HIGH;

//variaveis para o estado do joystick
int pot1 = 512;
int pot2 = 512;
boolean botao1 = false;


//Variaveis para controle da direção
int pDireita  = 100;
int pEsquerda = 100;

void contador()
{

  pulsos++;
}


void setup() {
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);  

  Serial.begin(115200);

  pinMode(pino_D0, INPUT);
  
  //Interrupcao 1 - pino digital 3
  //Aciona o contador a cada pulso
  attachInterrupt(1, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;
}


void loop() {
    if (millis() - timeold >= 1000)
  {
    detachInterrupt(1);
    rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos;
    timeold = millis();
    pulsos = 0;

   
    Serial.println("RPM = ");
    Serial.println(rpm, DEC);
    int velocidade = rpm*22;
    Serial.print("velocidade = ");
    Serial.print(velocidade);
    Serial.print(" cm/m");
  
    attachInterrupt(1, contador, FALLING);
  }
  
  //Leitura do Joystick (potenciometros)
  pot1 = analogRead(pinPot1);
  pot2 = analogRead(pinPot2);

  //Leitura do Botao do Joystick
  botao = digitalRead(pinBotao);
  if (botao && (botao != botaoAnt)) {
     botao1 = !botao1;
  }
  botaoAnt = botao;

  
  if (botao1) {
     //Aciona o freio
     digitalWrite(pinIN1, HIGH);
     digitalWrite(pinIN2, HIGH);
     digitalWrite(pinIN3, HIGH);
     digitalWrite(pinIN4, HIGH);
  } else {

     //Controle da direção 
     if (pot2 < 512) {
        //Esquerda 
        pDireita  = 100;
        pEsquerda = map(pot2, 511, 0, 100, 0); 
     } else {
        //Direita
        pDireita  = map(pot2, 512, 1023, 100, 0);
        pEsquerda = 100;       
     }

     if (pot1 < 512) {
        //Reverso
        int velocidade = map(pot1, 511, 0, 0, 255);

        analogWrite(pinIN1, 0);
        analogWrite(pinIN2, velocidade * pDireita / 100);
     
        analogWrite(pinIN3, 0);
        analogWrite(pinIN4, velocidade * pEsquerda / 100); 
     } else {
        //Para frente
        int velocidade = map(pot1, 512, 1023, 0, 255);

        analogWrite(pinIN1, velocidade * pDireita / 100);
        analogWrite(pinIN2, 0);
     
        analogWrite(pinIN3, velocidade * pEsquerda / 100);
        analogWrite(pinIN4, 0);                         
     }
  }  
}
