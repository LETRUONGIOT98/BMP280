/*
 * Interfacing Arduino with BME280 temperature, humidity and pressure sensor.
 * Temperature, humidity and pressure values are displayed on 20x4 LCD.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
 
#include <Wire.h>             // include Wire library, required for I2C devices
#include <Adafruit_Sensor.h>  // include Adafruit sensor library
#include <Adafruit_BME280.h>  // include adafruit library for BME280 sensor
#include <LiquidCrystal.h>    // include LCD library
 
// define device I2C address: 0x76 or 0x77 (0x77 is library default address)
#define BME280_I2C_ADDRESS  0x76
 
Adafruit_BME280 bme280;
 
// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
void setup()
{
  Serial.begin(9600);
 
  // set up the LCD's number of columns and rows
  lcd.begin(20, 4);
  
  Serial.println(F("BME280"));
  
  /*if (!bme280.begin(BME280_I2C_ADDRESS))
  {  
    Serial.println("KHONG TIM THAY CAM BIEN BME280");
    while (1);
  }*/
 
  lcd.setCursor(2, 0);
  lcd.print("Arduino + BME280");
  lcd.setCursor(0, 1);
  lcd.print("NHIET DO:");
  lcd.setCursor(0, 2);
  lcd.print("DO AM:");
  lcd.setCursor(0, 3);
  lcd.print("AP SUAT:");
}
 
char text[13]; 
 
// main loop
void loop()
{
  // get temperature, pressure and altitude from library
  float temperature=bme280.readTemperature();  // get temperature
  float humidity=bme280.readHumidity();     // get humidity
  float pressure= bme280.readPressure();     // get pressure
  float altitude_   = bme280.readAltitude(1013.25); // get altitude (this should be adjusted to your local forecast)
 
  // print data on the LCD screen
  // 1: print temperature
  sprintf(text, "%d.%02u%cC  ", (int)temperature, (int)(temperature * 100)%100, 223);
  lcd.setCursor(7, 1);
  lcd.print(text);
  // 2: print humidity
  sprintf(text, "%d.%02u %%  ", (int)humidity, (int)(humidity * 100)%100);
  lcd.setCursor(7, 2);
  lcd.print(text);
  // 3: print pressure
  sprintf(text, "%u.%02u hPa ", (int)(pressure / 100), (int)((uint32_t)pressure % 100));
  lcd.setCursor(7, 3);
  lcd.print(text);
 
  // print data on the serial monitor software
  // 1: print temperature
  Serial.print("NHIET DO:");
  Serial.print(temperature);
  Serial.println(" °C");
  // 1: print humidity
  Serial.print("DO AM:");
  Serial.print(humidity);
  Serial.println(" %");
  // 3: print pressure
  Serial.print("AP SUAT: ");
  Serial.print(pressure / 100);
  Serial.println(" hPa");
  // 4: print altitude
  Serial.print("Approx Altitude = ");
  Serial.print(altitude_);
  Serial.println(" m");
    
  Serial.println();  // start a new line
  delay(2000);       // wait 2 seconds
  
}
