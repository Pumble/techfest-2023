/* Configuration S4A EDU
 * Right motor pins:
 * D6 -> speed
 * D11 -> direction
 * left motor pins: 
 * D5 -> speed
 * D10 -> direction
 */
#define MOTOR_LEFT_SPEED 5
#define MOTOR_LEFT_DIR 10
#define MOTOR_RIGHT_SPEED 6
#define MOTOR_RIGHT_DIR 11
int speed = 255;  // between 50 and 255

// BUILT-IN LED
#define BLINK_INTERVAL 300

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // SETUPS
  Serial.println("starting setup");

  motorSetup();

  Serial.println("setup completed");
}

void loop() {
  forward();
  delay(3000);

  stop();
  delay(1000);

  backward();
  delay(3000);

  stop();
  delay(1000);

  left();
  delay(3000);

  stop();
  delay(1000);

  right();
  delay(3000);

  toogleLight(3);
}

/* ================================== SETUP ================================== */
void motorSetup() {
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);
}

/* ================================== END SETUP ================================== */

/* ================================== MOVEMENT ================================== */

void forward() {
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
}

void backward() {
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}

void stop() {
  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
}

void left() {
  stop();
  // LEFT MOTOR GOES FORWARD
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  // RIGHT MOTOR GOES BACKWARD
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}
void right() {
  stop();
  // RIGHT MOTOR GOES FORWARD
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
  // LEFT MOTOR GOES BACKWARD
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
}

/* ================================== END MOVEMENT ================================== */

/* ================================== TESTING ================================== */

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED_BUILTIN, LOW);
    delay(BLINK_INTERVAL);
  }
}

/* ================================== END TESTING ================================== */