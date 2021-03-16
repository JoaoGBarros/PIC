/*Pinos do Dislpay:{ A,B,C,D,E,F,G }
Pinos do Arduino:{ 2,3,4,5,6,7,8 } */
byte display7segmentos[8][7] = { {1,1,1,1,1,1,1},
  								 { 0,0,0,1,0,0,0 },  // = A
                                 { 1,1,0,0,0,0,0 },  // = B
                                 { 1,0,1,0,0,0,1 },  // = C
                                 { 0,1,0,0,0,1,0 },  // = D
                                 { 1,0,1,0,0,0,0 },  // = E
                                 { 1,0,1,1,0,0,0 },  // = F
                                 { 0,0,0,0,1,0,0 },  // = G
                               };
int botao = 10;
int num = 0;

void setup() {                
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(botao, INPUT);
}

void segmentos7(byte digito) {
  byte pino = 2;
  for (byte segmento = 0; segmento < 7; segmento++) {
    digitalWrite(pino, display7segmentos[digito][segmento]);
    pino++;
  }
}

void loop() {
  
  if(digitalRead(botao)){
    num++; 
    if(num >= 8){
      num = 0;
      segmentos7(num);
    }else{
      segmentos7(num);
    }
    delay(300);
  }
}