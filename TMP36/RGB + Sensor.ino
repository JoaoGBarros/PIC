int sensor = A0;
int pino_r= 9;
int pino_g = 10;
int pino_b = 11;
int v = 0;
int g = 0;
int b = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(pino_r, OUTPUT);
  pinMode(pino_g, OUTPUT);
  pinMode(pino_b, OUTPUT); 
}

void serCor(int v, int g, int b){
  analogWrite(pino_r, v);
  analogWrite(pino_g, g);
  analogWrite(pino_b, b);
}

void informaCor(float temperatura){
  if(temperatura < 10){
    v = 0;
    g = 0;
    b = 255;
  }else if(temperatura >= 10 && temperatura < 20){
    v = 0;
    g = 255;
    b = 0;
  }else if(temperatura >= 20 && temperatura < 30){
    v = 255;
    g = 255;
    b = 0;
  }else{
    v = 255;
    g = 0;
    b = 0;
  }
}

void loop()
{
  
  int leitura = analogRead(sensor);
  float voltagem = leitura / 1024.0;
  float temperatura = voltagem * 5;
  temperatura = temperatura - 0.5;
  temperatura = temperatura * 100;
  
  informaCor(temperatura);
  serCor(v, g, b);
  Serial.print(temperatura);
  Serial.println("C");
  delay(1000);
}