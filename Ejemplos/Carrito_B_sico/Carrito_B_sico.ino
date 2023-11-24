void setup() {
  pinMode(5, OUTPUT);  //PWM Izquierda
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);  //PWM Derecha
  pinMode(11, OUTPUT);
}

void loop() {
  avanzar();
  delay(2000);

  detener();
  delay(2000);

  retroceder();
  delay(2000);

  detener();
  delay(2000);

  Derecha();
  delay(2000);

  detener();
  delay(2000);

  Izquierda();
  delay(2000);

  detener();
  delay(2000);
}

void avanzar() {
  analogWrite(5, 255);
  digitalWrite(10, LOW);
  analogWrite(6, 255);
  digitalWrite(11, LOW);
}

void detener() {
  analogWrite(5, 0);
  analogWrite(6, 0);
}

void retroceder() {
  analogWrite(5, 255);
  digitalWrite(10, HIGH);
  analogWrite(6, 255);
  digitalWrite(11, HIGH);
}
//---------------------------
void Derecha() {
  analogWrite(6, 255);
  digitalWrite(11, HIGH);
}
void Izquierda() {
  analogWrite(5, 255);
  digitalWrite(10, HIGH);
}
