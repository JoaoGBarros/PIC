#include <Wire.h> //biblioteca do protocolo I2C
#include <LiquidCrystal.h>

// Endereço do sensor
const uint8_t MPU = 0x68;
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
// Pinos SDA  e SCL
const uint8_t scl = A5;
const uint8_t sda = A4;

// Fator de escala
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;
//int cursor;

// Configurações do MPU6050
const int PWR_MGMT_1 =    0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG =   0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG =  0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT =    0x3B; // registro de leitura do eixo X do acelerômetro

//Variaveis para guardar os dados "crus" das aceleração e velocidade angular recebidos pelo sensor
int16_t AccelX, AccelY, AccelZ, GirX, GirY, GirZ;

void setup() {
  Serial.begin(38400); //Inicializa serial
  Wire.begin(MPU); //Inicializa IC2
  IniciaMPU(); //Inicializa sensor MPU
  //lcd.begin(16, 2);
  //cursor = 0;
}

void loop() {
  double Ax, Ay, Az, Gx, Gy, Gz;

  delay(3000);
  ReadValue(); //Recebe um dado do MPU


  
  //dividir pelo fator
  Ax = (double)AccelX/AccelScaleFactor;
  Ay = (double)AccelY/AccelScaleFactor;
  Az = (double)AccelZ/AccelScaleFactor;
  Gx = (double)GirX/GyroScaleFactor;
  Gy = (double)GirY/GyroScaleFactor;
  Gz = (double)GirZ/GyroScaleFactor;

  //Imprime o que foi recebido
  
//  Serial.print("Ax: "); Serial.print(Ax);
//  Serial.print(" | Ay: "); Serial.print(Ay);
//  Serial.print(" | Az: "); Serial.println(Az);
//  Serial.print("Gx: "); Serial.print(Gx);
//  Serial.print(" | Gy: "); Serial.print(Gy);
//  Serial.print(" | Gz: "); Serial.println(Gz);
//  Serial.println();
//  lcd.setCursor(cursor, 0);
  ImprimeLetra(Ax,Ay,Az,Gx,Gy,Gz);

  


  //delay(1000); //Espera 1 seg
}

//Função para escrever um dado em um registrador
void I2C_Write(uint8_t regAddress, uint8_t data){ 
  Wire.beginTransmission(MPU);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

// Lê os 12 primeiros bytes, 2 bytes para cada coordenada (aceleração e depois velocidade angular)
void ReadValue(){
  Wire.beginTransmission(MPU);
  Wire.write(ACCEL_XOUT);
  Wire.endTransmission();
  Wire.requestFrom(MPU, (uint8_t)12);
  
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read()); 
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
  GirX = (((int16_t)Wire.read()<<8) | Wire.read());
  GirY = (((int16_t)Wire.read()<<8) | Wire.read());
  GirZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//Inicializa sensor MPU6050
void IniciaMPU(){
  I2C_Write(PWR_MGMT_1, 0);
  I2C_Write(GYRO_CONFIG, 0);
  I2C_Write(ACCEL_CONFIG, 0);
}

void ImprimeLetra(double Ax,double Ay,double Az,double Gx,double Gy,double Gz){
  if(Ax >= 0.2 && Ay >= 0.6 && Az < 0.9){ //Diagonal DF
    Serial.print("E");
    return;
  }

  if(Ax <= 0 && Ay >= 0.6 && Az < 0.9){ //Diagonal EF
    Serial.print("R");
    return;
  }

  if(Ax >= 0.2 && Ay <= -0.1 && Az < 0.9){ //Diagonal  DT
    Serial.print("E");
    return;
  }

  if(Ax <= 0 && Ay <= -0.1 && Az < 0.9){ //Diagon ET
    Serial.print("D");
    return;
  }
  
  if(Ay >= 0.5 && Az < 0.9 && Ax >= -0.1){ // FRENTE
    Serial.print("B");
    return;
  }
  
  if(Ay <= -0.1 && Az < 0.9){ //TRAS
    Serial.print("T");
    return; 
  }


  if(Ax <= 0 ){ //ESQUERDA
    Serial.print("A");
    return;
  }

  if(Ax >= 0.1){ // DIREITA
    Serial.print("O");
    return;
  }

  else{
    Serial.print(" ");
    return;
  }

}
