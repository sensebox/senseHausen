//Infrarot
int infrarotPIN = A0;
int infrarotDistance = 0;
int parkLEDred = 6;
int parkLEDgreen = 7;

//Sensor general
int spur1a= 3;
int spur1e= 12;
int distancemax = 100;
unsigned int time=0;
unsigned int distance1=0;
unsigned int distance2=0;
unsigned int zaehler1=0;
unsigned int zaehler2=0;

//Sensor1
int trig = 12;
int echo = 11;
int schalter11= 1;
int schalter12= 1;

//Sensor2
int trig1 = 9;
int echo1 = 10;
int schalter21= 1;
int schalter22= 1;

void setup () {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(parkLEDred, OUTPUT);
  pinMode(parkLEDgreen, OUTPUT);
}


void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  time=pulseIn(echo, HIGH);
  distance1=time/58;
  delay(100);
  if (distance1 < spur1e and distance1 > spur1a and schalter11 == 1) zaehler1++;
  if (distance1<distancemax) schalter11 = 0;
  else schalter11 = 1;
  Serial.print("Distance1: ");
  Serial.println(distance1);
  //Serial.println(zaehler1);

  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  time=pulseIn(echo1, HIGH);
  distance2=time/58;
  delay(100);
  if (distance2 < spur1e and distance2 > spur1a and schalter21 == 1) zaehler2++;
  if (distance2<distancemax) schalter11 = 0;
  else schalter21 = 1;
  Serial.print("Distance2: ");
  Serial.println(distance2);
  //Serial.println(zaehler2);

  infrarotDistance = analogRead(infrarotPIN);
  if (infrarotDistance < 440 or infrarotDistance > 460) {
    digitalWrite(parkLEDred, HIGH);
    digitalWrite(parkLEDgreen, LOW);
  } else {
    digitalWrite(parkLEDred, LOW);
    digitalWrite(parkLEDgreen, HIGH);
  }
}
