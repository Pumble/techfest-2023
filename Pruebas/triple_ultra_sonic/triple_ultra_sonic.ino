const int US_LEFT_TRIGGER = 8;
const int US_LEFT_ECHO = 9;
const int US_CENTER_TRIGGER = 6;
const int US_CENTER_ECHO = 7;
const int US_RIGHT_TRIGGER = 4;
const int US_RIGHT_ECHO = 5;
float US_LEFT_DURATION, US_LEFT_DISTANCE;
float US_CENTER_DURATION, US_CENTER_DISTANCE;
float US_RIGHT_DURATION, US_RIGHT_DISTANCE;
const int US_DURATION = 10;

void setup() {
  Serial.begin(9600);

  // Set the pin mode for every ultra sonic sensor
  pinMode(US_LEFT_TRIGGER, OUTPUT);
  pinMode(US_LEFT_ECHO, INPUT);
  digitalWrite(US_LEFT_TRIGGER, LOW);

  pinMode(US_CENTER_TRIGGER, OUTPUT);
  pinMode(US_CENTER_ECHO, INPUT);
  digitalWrite(US_CENTER_TRIGGER, LOW);

  pinMode(US_RIGHT_TRIGGER, OUTPUT);
  pinMode(US_RIGHT_ECHO, INPUT);
  digitalWrite(US_RIGHT_TRIGGER, LOW);
}

void loop() {
  float US_LEFT_DISTANCE = ultraSonicHY_SRF05(US_LEFT_TRIGGER, US_LEFT_ECHO);
  float US_CENTER_DISTANCE = ultraSonicHC_SR04(US_CENTER_TRIGGER, US_CENTER_ECHO);
  float US_RIGHT_DISTANCE = ultraSonicHY_SRF05(US_RIGHT_TRIGGER, US_RIGHT_ECHO);

  Serial.println("=== Distances ===");
  printDistance("Left", US_LEFT_DISTANCE);
  printDistance("Center", US_CENTER_DISTANCE);
  printDistance("Right", US_RIGHT_DISTANCE);
  delay(1000);
}

float ultraSonicHC_SR04(int trigPin, int echoPin) {
  float t;  // tiempo que demora en llegar el eco
  float d;  // distancia en centimetros

  digitalWrite(trigPin, LOW);
  delayMicroseconds(US_DURATION);
  digitalWrite(trigPin, HIGH);

  t = pulseIn(echoPin, HIGH);
  d = (t * .0343) / 2;
  return d;
}

float ultraSonicHY_SRF05(int trigPin, int echoPin) {
  float t;  // tiempo que demora en llegar el eco
  float d;  // distancia en centimetros

  digitalWrite(trigPin, HIGH);
  delay(US_DURATION);
  digitalWrite(trigPin, LOW);

  t = pulseIn(echoPin, HIGH);
  d = t / 59;
  return d;
}

void printDistance(String side, float distance) {
  Serial.print(side);
  Serial.print(": ");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
}