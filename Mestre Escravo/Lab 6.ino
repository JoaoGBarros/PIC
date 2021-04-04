#include <Wire.h>


#define SDA_PIN 4
#define SCL_PIN 5
const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;
int botao = 5;
byte i = 0;


void setup() {
  pinMode(botao, INPUT);
  Wire.begin(); 
}



void loop() {
  	
  	
    if(digitalRead(botao)){
      Wire.beginTransmission(I2C_SLAVE);
  	  Wire.write(i);
        i++;
        if(i > 2){
          i = 0;
        }
      }
  	
  	delay(100);
  	Wire.endTransmission();
  
  
    
  	
    
}