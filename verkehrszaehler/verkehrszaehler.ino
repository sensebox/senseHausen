#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//Infrarot(parkinglot)
int infrarotPIN = A0;
int infrarotDistance = 0;
int parkLEDred = 6;
int parkLEDgreen = 7;

//Sensor general

unsigned int time=0;
unsigned int distancemax = 10;
unsigned int distancemin = 3;
unsigned int distance = distancemax;
unsigned int counter_left = 0;
unsigned int counter_right = 0;

//Sensor left
int trig_left = 12;
int echo_left = 11;

//Sensor rigth
int trig_right = 9;
int echo_right = 10;


void setup () {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 2);
  lcd.setRGB(colorR, colorG, colorB);
    
  // Print a message to the LCD.
  lcd.print("Anzahl Fahrzeuge");
  writeLCD();
  
  pinMode(trig_right, OUTPUT);
  pinMode(echo_right, INPUT);

  pinMode(trig_left, OUTPUT);
  pinMode(echo_left, INPUT);

  pinMode(parkLEDred, OUTPUT);
  pinMode(parkLEDgreen, OUTPUT);
}


void loop()
{
  //Serial.println(checkForCarRight());
  //Serial.println(checkForCarLeft());
  
  if(checkForCarRight()){
    delay(500);
    writeLCD();
  }
  if(checkForCarLeft()){
    delay(500);
    writeLCD();
  }
   checkCarLot();  
}

void writeLCD(){
  for(int i = 0; i < 15;i++){
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }
  
  //atention Left and Right are mixed up so they are "corrected" for print
  lcd.setCursor(11, 1);
  lcd.print("R");
  lcd.setCursor(12, 1);
  lcd.print(counter_left);

  lcd.setCursor(0, 1);
  lcd.print("L");
  lcd.setCursor(1, 1);
  lcd.print(counter_right);
}
boolean checkForCarRight(){
  
  digitalWrite(trig_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_right, LOW);
  time=pulseIn(echo_right, HIGH);
  distance=time/58;
  delay(100);

   //Serial.print("right ");
   //Serial.println(distance);
  //wait for car
  if((distance > distancemin)and(distance < distancemax)){
    //wait for car to pass
    delay(500);
    while((distance > distancemin)and(distance < distancemax)){

      //Serial.print("right ");
      //Serial.println(distance);
    
      digitalWrite(trig_right, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_right, LOW);
      time=pulseIn(echo_right, HIGH);
      distance=time/58;
      delay(100);
    }
    counter_right++;
    return true;
  }
    return false;
 }

boolean checkForCarLeft(){
 digitalWrite(trig_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_left, LOW);
  time=pulseIn(echo_left, HIGH);
  distance=time/58;
  delay(100);
  ////Serial.print("left: ");
  ////Serial.println(distance);
  //checkfor car
  if((distance > distancemin)and(distance < distancemax)){
    //wait for car to pass
    delay(500);
    while((distance > distancemin)and(distance < distancemax)){
    
      ////Serial.print("left: ");
      ////Serial.println(distance);
    
      digitalWrite(trig_left, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_left, LOW);
      time=pulseIn(echo_left, HIGH);
      distance=time/58;
      delay(100);
    }
    counter_left++;
    return true;
  }
    return false;
 }

void checkCarLot(){
  infrarotDistance = analogRead(infrarotPIN);
  Serial.println(infrarotDistance);
  if ((infrarotDistance < 440) or (infrarotDistance > 680)) {
    digitalWrite(parkLEDred, HIGH);
    digitalWrite(parkLEDgreen, LOW);
  } else {
    digitalWrite(parkLEDred, LOW);
    digitalWrite(parkLEDgreen, HIGH);
  }
}

