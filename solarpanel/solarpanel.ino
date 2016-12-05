//Solarpanel
//Bernd 

#include <Servo.h>
Servo servo;
int max = 175;//anpassen
int min = 0;//anpassen
int step = 1;//anpasen
int toleranz = 100;//anpassen
int pos = 0;
int run = 100;//anpassen

//sensor
int left_s = A4;
int right_s = A1;
int center_s = A0;

int left = 0;
int right = 0;
int center = 0;
//_______________________windrad/bell___________________________________
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int button = 7;
boolean pressed = false;
int led_red = 5;
//__________________________________________________________________


void setup() {
  //define pin
  Serial.begin(9600);
  pinMode(left_s,INPUT);
  pinMode(right_s,INPUT);
  pinMode(center_s,INPUT);

  pinMode(led_red,OUTPUT);  
  servo.attach(3);

}

void loop() {
  //void check_brigthness(){
  Serial.print("Test");
  for(int i = 0;i <run;i++){
    correctPosition();
    delay(15);
    Serial.print("Test i");
  }
  //-----------------------bell-----------------------------------
   pressed = digitalRead(button);
  if(pressed){
    playMelody();
    pressed = false;
  }
  redBlink();
  
}

void correctPosition(){
  // werte müssen noch angepasst werden
  /*
   * Alle Sensoren bei "gleichmäßigem" Licht von oben überprüfen 
   * Dann mit Taschenlampe alle testen
   */
  center = analogRead(center_s);
  right = analogRead(right_s);
  left = analogRead(left_s);
  Serial.print("center ");
  Serial.print(center);
  Serial.print(" left ");
  Serial.print(left);
  Serial.print(" right ");
  Serial.println(right);
  
  
  if(right > (center+toleranz)){
    if((pos+step) > max){
      go_min();
    }else{
     pos = pos +step;
     servo.write(pos);
    }    
  }
  if(left > (center+toleranz)){
    if((pos-step) < min){
      go_max();
    }else{
      pos = pos - step;
      servo.write(pos);
    }    
  }
}

//move panel to minimal position
void go_min(){
  while(pos > min){
    pos = pos - step;
    servo.write(pos);              
    delay(25);
  }  
}

//move panel to maximal position
void go_max(){
  while(pos < max){
    pos = pos + step;
    servo.write(pos);              
    delay(25);
  }  
}

void playMelody(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(11, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(11);
  }
}

void redBlink(){
  digitalWrite(led_red,HIGH);
  delay(100);
  digitalWrite(led_red,LOW);
  delay(150);
  digitalWrite(led_red,HIGH);
  delay(100);
  digitalWrite(led_red,LOW);
  delay(700);
  
}


