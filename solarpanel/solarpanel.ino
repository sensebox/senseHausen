//Solarpanel
//Bernd 

#include <Servo.h>
Servo servo;

int max = 0;//anpassen
int min = 0;//anpassen
int step = 0;//anpasen
int toleranz = 0;//anpassen
int pos = 0;
int run = 200;//anpassen

//sensor
int left_s = A0;
int right_s = A1;
int center_s = A2;

int left = 0;
int right = 0;
int center = 0;



void setup() {
  //define pin
  pinMode(left_s,INPUT);
  pinMode(right_s,INPUT);
  pinMode(center_s,INPUT);
 
  
  servo.attach(9);

}

void loop() {
  //void check_brigthness(){
  for(int i;i<run;i++){
    correctPosition();
  }
  delay(2000);
  
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
  
  if(left > (center+toleranz)){
    if((pos+step) > max){
      go_min();
    }else{
     pos = pos +step;
     servo.write(pos);
    }    
  }
  if(right > (center+toleranz)){
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
    delay(15);
  }  
}

//move panel to maximal position
void go_max(){
  while(pos < max){
    pos = pos + step;
    servo.write(pos);              
    delay(15);
  }  
}


