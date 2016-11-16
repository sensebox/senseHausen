//OLED
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>

//senseBox
#include "HDC100X.h"
#include "BMP280.h"
#include <Makerblog_TSL45315.h>
#include <SPI.h>

//Load sensors
Makerblog_TSL45315 TSL = Makerblog_TSL45315(TSL45315_TIME_M4);
HDC100X HDC(0x43);
BMP280 BMP;

//measurement variables
float temperature = 0;
float humidity = 0;
double tempBaro, pressure;
uint32_t lux;
uint16_t uv;
int messTyp;
#define UV_ADDR 0x38
#define IT_1   0x1

// Variren
const unsigned int postingInterval = 60000;

void setup() {
  //Serial.begin(9600);
  //----OLED
  int y = 9;
  Wire.begin();
  SeeedGrayOled.init();             //initialize SEEED OLED display
  SeeedGrayOled.clearDisplay();     //Clear Display.
  SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
  SeeedGrayOled.setTextXY(0,0);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putString("Welcome to"); //Print Hello World
  SeeedGrayOled.setTextXY(1,0);  //set Cursor to ith line, 0th column
  SeeedGrayOled.putString("  senseBox  "); //Print Hello World
  
  SeeedGrayOled.setTextXY(3,0);  
  SeeedGrayOled.putString("Temp"); 
  SeeedGrayOled.setTextXY(3,y);  
  SeeedGrayOled.putString("°C"); 
  
  SeeedGrayOled.setTextXY(5,0);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putString("Hum"); //Print Hello World
  SeeedGrayOled.setTextXY(5,y);  
  SeeedGrayOled.putString("  %");
  
  SeeedGrayOled.setTextXY(7,0);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putString("Uv"); //Print Hello World
  SeeedGrayOled.setTextXY(7,y);  
  SeeedGrayOled.putString(" mw");
  
  SeeedGrayOled.setTextXY(9,0);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putString("Lux"); //Print Hello World
  SeeedGrayOled.setTextXY(9,y);  
  SeeedGrayOled.putString("Lux");
  
  SeeedGrayOled.setTextXY(11,0);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putString("Pres"); //Print Hello World
  SeeedGrayOled.setTextXY(11,y);  
  SeeedGrayOled.putString("hPa");
  
  //---senseBox---------------
  //Serial.println("senseBox Home software version 2.2");
  //Serial.print("Initializing sensors...");
  Wire.beginTransmission(UV_ADDR);
  Wire.write((IT_1 << 2) | 0x02);
  Wire.endTransmission();
  delay(500);
  HDC.begin(HDC100X_TEMP_HUMI, HDC100X_14BIT, HDC100X_14BIT, DISABLE);
  TSL.begin();
  BMP.begin();
  BMP.setOversampling(4);
  //Serial.println("Starting loop.");
}

void loop() {
  //-----Pressure-----//
  //Serial.println("Posting pressure");
  messTyp = 2;
  char result = BMP.startMeasurment();
  if (result != 0) {
    delay(result);
    result = BMP.getTemperatureAndPressure(tempBaro, pressure);    
    //Serial.println(result);
    oledPrint(11,pressure);
  }
  
  //-----Humidity-----//
  //Serial.println("Posting humidity");
  messTyp = 2;
  humidity = HDC.getHumi();  
  //Serial.println(humidity);
  oledPrint(5,humidity);
  
  //-----Temperature-----//
  //Serial.println("Posting temperature");
  messTyp = 2;
  temperature = HDC.getTemp();  
  //Serial.println(temperature);
  oledPrint(3,temperature);
  
  //-----Lux-----//
  //Serial.println("Posting illuminance");
  messTyp = 1;
  lux = TSL.readLux();  
  //Serial.println(lux);
  oledPrint(9,lux);
      
  //UV intensity
  //Serial.println("Posting uv");
  messTyp = 1;
  uv = getUV();
  //Serial.println(uv);
  oledPrint(7,uv);
}



uint16_t getUV() {
  byte msb = 0, lsb = 0;
  uint16_t uvValue;
  Wire.requestFrom(UV_ADDR + 1, 1); //MSB
  delay(1);
  if (Wire.available()) msb = Wire.read();

  Wire.requestFrom(UV_ADDR + 0, 1); //LSB
  delay(1);
  if (Wire.available()) lsb = Wire.read();

  uvValue = (msb << 8) | lsb;

  return uvValue * 5;
}
void oledPrint(int row,int value){
  
  SeeedGrayOled.setTextXY(row,5);  //set Cursor to ith line, 0th column  
  SeeedGrayOled.putNumber(value); //Print Hello World
}



 
