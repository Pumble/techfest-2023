/**
 * Referencias:
 * https://hetpro-store.com/TUTORIALES/hy-srf05-sensor-ultrasonico/
 */

const int Trigger = 8;
const int Echo = 9;

void setup() {
  Serial.begin(9600);

  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
}

void loop() {
  long t;  // tiempo que demora en llegar el eco
  long d;  // distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delay(10);
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);
  d = t / 59;

  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();
  delay(1000);
}
