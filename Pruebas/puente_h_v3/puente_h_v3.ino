/*
 L9110 motor driver controlando 2 motores CC
 COPIAR Y PEGAR SOBRE EL SKETCH DE ARDUINO

  https://robots-argentina.com.ar/didactica/puente-h-placa-controladora-de-motores-l9110s/
*/

// const int AIA = 6;   // (pwm) pin 6 conectado a pin A-IA
// const int AIB = 5;   // (pwm) pin 5 conectado a pin A-IB
// const int BIA = 10;  // (pwm) pin 10 conectado a pin B-IA --> velodicdad
// const int BIB = 9;   // (pwm) pin 9 conectado a pin B-IB  --> direccion

const int AIA = 8;   // (pwm) pin 6 conectado a pin A-IA
const int AIB = 7;   // (pwm) pin 5 conectado a pin A-IB
const int BIA = 10;  // (pwm) pin 10 conectado a pin B-IA --> velodicdad
const int BIB = 9;   // (pwm) pin 9 conectado a pin B-IB  --> direccion

byte speed = 200;
// cambie este valor (100 a 255) para controlar
// la speed de los motores

void setup() {
  pinMode(AIA, OUTPUT);  // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}

void loop() {
  forward();
  delay(5000);
  softStop();
  delay(1000);
  backward();
  delay(5000);
  hardStop();
  delay(1000);
  left();
  delay(5000);
  right();
  delay(5000);
}

// FORWARD
void backward() {
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void forward() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}

void left() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void right() {
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}

void softStop() {
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIB, LOW);
  digitalWrite(BIA, LOW);
}

void hardStop() {
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIB, HIGH);
  digitalWrite(BIA, HIGH);
}