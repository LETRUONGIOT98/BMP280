#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_BMP085 bmp;
#include "DHT.h"            
 
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
 
DHT dht(DHTPIN, DHTTYPE); 
void setup() {
  dht.begin();
  lcd.init(); 
  if (!bmp.begin()) {
  lcd.print("CAM BIEN LOI");
   
  while (1) {}
  }
      lcd.setCursor(2, 0);
  lcd.print("CAM BIEN BMP180");
}
  
void loop() {
    //read pressure
    float A = bmp.readPressure()/100.0+0.01;
    float T = bmp.readTemperature();
    float h = dht.readHumidity();
    lcd.setCursor(0, 1);
    lcd.print("AP SUAT: ");
    lcd.setCursor(9, 1);
    lcd.print(A);
    lcd.print(" hPa");

    //read altitude
    lcd.setCursor(0, 2);
    lcd.print("NHIET DO: ");
    lcd.setCursor(10, 2);
    lcd.print(T);
    lcd.setCursor(16, 2);
    lcd.print(" *C");

    ////
    lcd.setCursor(0, 3);
    lcd.print("DO AM: ");
    lcd.setCursor(10, 3);
    lcd.print(h);
    lcd.setCursor(16, 3);
    lcd.print(" %");
    delay(300);
}
