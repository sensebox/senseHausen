//Ampel1
int g_1 = 11;
int y_1 = 12;
int r_1 = 13;

//Ampel2
int g_2 = 8;
int y_2 = 9;
int r_2 = 10;

//Ampel3
int g_3 = 5;
int y_3 = 6;
int r_3 = 7;

void setup() {
    pinMode(g_1, OUTPUT);
    pinMode(y_1, OUTPUT);
    pinMode(r_1, OUTPUT);

    pinMode(g_2, OUTPUT);
    pinMode(y_2, OUTPUT);
    pinMode(r_2, OUTPUT);

    pinMode(g_3, OUTPUT);
    pinMode(y_3, OUTPUT);
    pinMode(r_3, OUTPUT);
}

void loop(){
    digitalWrite(r_1, HIGH);
    digitalWrite(r_3, HIGH);
    digitalWrite(g_2, HIGH);
    delay(5000);
    blink(g_2, 4);
    digitalWrite(g_2, LOW);
    digitalWrite(y_2, HIGH);
    delay(1000);
    digitalWrite(y_2, LOW);
    digitalWrite(r_2, HIGH);
    delay(1000);
    digitalWrite(y_1, HIGH);
    digitalWrite(y_3, HIGH);
    delay(1000);
    digitalWrite(r_1, LOW);
    digitalWrite(y_1, LOW);
    digitalWrite(g_1, HIGH);
    digitalWrite(r_3, LOW);
    digitalWrite(y_3, LOW);
    digitalWrite(g_3, HIGH);
    delay(5000);
    blink(g_1, 4);
    blink(g_3, 4);
    digitalWrite(g_1, LOW);
    digitalWrite(y_1, HIGH);
    digitalWrite(g_3, LOW);
    digitalWrite(y_3, HIGH);
    delay(1000);
    digitalWrite(y_1, LOW);
    digitalWrite(r_1, HIGH);
    digitalWrite(y_3, LOW);
    digitalWrite(r_3, HIGH);
    delay(1000);
    digitalWrite(y_2, HIGH);
    delay(1000);
    digitalWrite(r_2, LOW);
    digitalWrite(y_2, LOW);
}

void blink(int pin, int times){
    for(int i = 0; i < times; i++){
        digitalWrite(pin, LOW);
        delay(500);
        digitalWrite(pin, HIGH);
        delay(500);
    }
}
