#define in1 9
#define in2 3
#define in3 5
#define in4 6
#define botao 2
int p_1 = A0;
int p_2 = A1;
int p_3 = A2;
int p_4 = A3;
void setup() {
 Serial.begin(9600);
 pinMode(in1,OUTPUT);
 pinMode(in2,OUTPUT);
 pinMode(in3,OUTPUT);
 pinMode(in4,OUTPUT);
 pinMode(p_3,INPUT);
 pinMode(p_4,INPUT);
 pinMode(p_1,INPUT);
 pinMode(p_2,INPUT);
 
}

void loop() {
  int valor_p1 = analogRead(p_1);
  valor_p1 = map(valor_p1,0,1023,0,255);
  int valor_p2 = analogRead(p_2);
  valor_p2 = map(valor_p2,0,1023,0,255);
  int valor_p3 = analogRead(p_3);
  valor_p3 = map(valor_p3,0,1023,0,255);
  int valor_p4 = analogRead(p_4);
  valor_p4 = map(valor_p4,0,1023,0,255);
  analogWrite(in2,valor_p3);
  analogWrite(in4,valor_p4);
  analogWrite(in1,valor_p1);
  analogWrite(in3,valor_p2);
  
  
}