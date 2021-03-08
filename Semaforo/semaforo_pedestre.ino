int led_vermelho = 13;
int led_amarelo = 12;
int led_verde = 11;
int led_vermelho_pedestre = 10;
int led_verde_pedestre = 9;
int botao = 3;
int Cross;


void setup() {
    pinMode(led_vermelho, OUTPUT);
    pinMode(led_amarelo, OUTPUT);
    pinMode(led_verde, OUTPUT);
    pinMode(led_vermelho_pedestre, OUTPUT);
    pinMode(led_verde_pedestre, OUTPUT);
    pinMode(botao, INPUT);
  	Cross = 0;
}

void changeLights(int crosstime){
  delay(1000);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho_pedestre, LOW);
  digitalWrite(led_amarelo, HIGH);
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_verde_pedestre, HIGH);

  delay(crosstime);

  for(int i =0; i <= 10; i++){
    digitalWrite(led_verde_pedestre, LOW);
    delay(200);
    digitalWrite(led_verde_pedestre, HIGH);
    delay(200);
  }

  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_verde_pedestre, LOW);
}

void loop(){
    int crosstime = 2000;
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_vermelho_pedestre, HIGH);
    
      
    
    if(digitalRead(botao) == 1 && (((millis() - Cross)>= 5000) || Cross == 0)){
      changeLights(crosstime);
      Cross = 0;
      Cross = millis();
    }else{
      Serial.print("Ainda nao passou 5 segundos desde a ultima vez que apertou o botao");
    }
}
