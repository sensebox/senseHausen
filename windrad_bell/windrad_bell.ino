
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

void setup() {
  pinMode(led_red,OUTPUT);
}

void loop() {
  pressed = digitalRead(button);
  if(pressed){
    playMelody();
    pressed = false;
  }
  redBlink();
  
  
  
  
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

