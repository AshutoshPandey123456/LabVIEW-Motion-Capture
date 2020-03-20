#include<Wire.h>
#include<dht.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
dht DHT;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int flexSensorPin = A0; //analog pin 0
#define DHT11_PIN 8
const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
void setup(){
  Serial.begin(9600);
    lcd.begin(16, 2);
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}
void loop(){
  int flexSensorReading = analogRead(flexSensorPin);
int flex0to100 = map(flexSensorReading, 240, 350, 0, 100);
Serial.println("Flex Reading");
Serial.println(flex0to100);
delay(700); //just here to slow down the output for easier reading
  int chk = DHT.read11(DHT11_PIN);
Serial.println(" Humidity " );
Serial.println(DHT.humidity, 1);
  lcd.setCursor(0, 0);
lcd.print(DHT.humidity, 1);
lcd.print("%H");
lcd.print(" ");
Serial.println(" Temperature ");
lcd.print(DHT.temperature, 1);
lcd.print("degC");
delay(1000);
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  lcd.setCursor(0, 1);
  Serial.print("AccX = "); Serial.print(AccX);
  Serial.print(" || AccY = "); Serial.print(AccY);
Serial.print(" || AccZ = "); Serial.print(AccZ);
  Serial.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);
  lcd.print(AccX);
  lcd.print(" ");
  lcd.print(AccY);
  lcd.print(" ");
  lcd.print(AccZ); delay(800);
  }
