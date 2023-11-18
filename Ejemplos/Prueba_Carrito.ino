void setup() {
  pinMode(5,OUTPUT);  //PWM Isquierda
  pinMode(10,OUTPUT);
  pinMode(6,OUTPUT);  //PWM Derecha
  pinMode(11,OUTPUT);
}
void loop() {
  avanzar();
  delay(3000);
  detener();
  delay(2000);
}

void avanzar(){
  analogWrite(5,255);
  digitalWrite(10,LOW);
  analogWrite(6,255);
  digitalWrite(11,LOW);
}
void detener(){
  analogWrite(5,0);
  analogWrite(6,0);
}
