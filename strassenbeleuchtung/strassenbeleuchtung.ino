int helligkeitPIN = A0;
int helligkeit = 0;

int lampe1 = 13;
int lampe2 = 12;
int lampe3 = 11;
int lampe4 = 10;

void setup() {
  //Serial.begin(9600);
  pinMode(lampe1, OUTPUT);
  pinMode(lampe2, OUTPUT);
  pinMode(lampe3, OUTPUT);
  pinMode(lampe4, OUTPUT);
}

void loop() {
  helligkeit = analogRead(helligkeitPIN);
  if (helligkeit <= 450) {
    digitalWrite(lampe1, HIGH);
    digitalWrite(lampe2, HIGH);
    digitalWrite(lampe3, HIGH);
    digitalWrite(lampe4, HIGH);
    delay(3500);
  } else {
    digitalWrite(lampe1, LOW);
    digitalWrite(lampe2, LOW);
    digitalWrite(lampe3, LOW);
    digitalWrite(lampe4, LOW);
  }
  //Serial.println(helligkeit);
}
