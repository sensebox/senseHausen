
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 46; 

//-----------ultrasonic
int trig = 12;  // Trig-Pin des Sensors ist an Pin 12 angeschlossen.
int echo = 11;  // Echo-Pin des Sensors ist an Pin 11 angeschlossen.
unsigned int time = 0;
unsigned int distance = 20;
int boat_dist = 5;

//----------trafic light
int led_red = 10;
int led_green = 8;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object

   //trafficligth
   pinMode(led_red, OUTPUT);
   pinMode(led_green, OUTPUT);
   digitalWrite(led_green,HIGH);
}

void loop() {
  int temp = messure();
  Serial.println(temp);
  if(temp <= boat_dist){
    digitalWrite(led_green,LOW);
    digitalWrite(led_red,HIGH);
    openBridge();
    delay(6000);
    while(temp <= boat_dist ){
       Serial.println("boat");
        delay(1000);
        temp = messure();
    }
    closeBridge();
    digitalWrite(led_green,HIGH);
    digitalWrite(led_red,LOW);
    delay(1000);
  }
  delay(100);

}

void closeBridge(){
  for (pos = 0; pos <= 46 pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}

void openBridge(){
  for (pos = 46; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}

int messure(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  time = pulseIn(echo, HIGH);
  distance = time / 58;
  return distance;
}

