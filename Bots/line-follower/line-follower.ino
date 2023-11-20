/**
 * Referencias
 * https://www.youtube.com/watch?v=YkfBtjs8uWg&ab_channel=ScienceFun
 * https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 * https://robots-argentina.com.ar/didactica/puente-h-placa-controladora-de-motores-l9110s/
 */

// ================================== Wired connections ==================================
#define MOTOR_RIGHT_AIA 8
#define MOTOR_RIGHT_AIB 7
#define MOTOR_LEFT_BIA 10
#define MOTOR_LEFT_BIB 9

// ================================== Functional connections ==================================
// Motor and H-Bridge
#define MOTOR_RIGHT_PWM MOTOR_RIGHT_AIA  // Motor Right Speed
#define MOTOR_RIGHT_DIR MOTOR_RIGHT_AIB  // Motor Right Direction
#define MOTOR_LEFT_PWM MOTOR_LEFT_BIA    // Motor Left Speed
#define MOTOR_LEFT_DIR MOTOR_LEFT_BIB    // Motor Left Direction
// Movement for testing
#define MOVEMENT_FORWARD 'W'
#define MOVEMENT_BACKWARD 'S'
#define MOVEMENT_LEFT 'A'
#define MOVEMENT_RIGHT 'D'
#define MOVEMENT_STOP 'X'
byte speed = 200;

// BUILT-IN LED
#define LED 13
#define BLINK_INTERVAL 300

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // SETUPS
  Serial.println("starting setup");
  setupMotors();

  Serial.println("setup completed");
}

int input = 0;
void loop() {
  if (Serial.available() > 0) {
    input = (char)Serial.read();
    Serial.println((char)input);

    switch (input) {
      case MOVEMENT_FORWARD:
        forward();
        break;
      case MOVEMENT_BACKWARD:
        backward();
        break;
      case MOVEMENT_LEFT:
        left();
        break;
      case MOVEMENT_RIGHT:
        right();
        break;
      case MOVEMENT_STOP:
        softStop();
        break;
    }
  }
}

/* ================================== SETUP ================================== */

void setupMotors() {
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);  // fijar los pines como salidas
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);

  digitalWrite(MOTOR_RIGHT_PWM, LOW);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
  digitalWrite(MOTOR_LEFT_PWM, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
}

/* ================================== END SETUP ================================== */

/* ================================== MOVEMENT ================================== */

void forward() {
  Serial.println("Forward");

  analogWrite(MOTOR_RIGHT_PWM, speed);
  analogWrite(MOTOR_RIGHT_DIR, 0);
  analogWrite(MOTOR_LEFT_PWM, speed);
  analogWrite(MOTOR_LEFT_DIR, 0);
}

void backward() {
  Serial.println("Backward");

  analogWrite(MOTOR_RIGHT_PWM, 0);
  analogWrite(MOTOR_RIGHT_DIR, speed);
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_LEFT_DIR, speed);
}

void left() {
  Serial.println("Left");

  analogWrite(MOTOR_RIGHT_PWM, speed);
  analogWrite(MOTOR_RIGHT_DIR, 0);
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_LEFT_DIR, speed);
}

void right() {
  Serial.println("Right");

  analogWrite(MOTOR_RIGHT_PWM, 0);
  analogWrite(MOTOR_RIGHT_DIR, speed);
  analogWrite(MOTOR_LEFT_PWM, speed);
  analogWrite(MOTOR_LEFT_DIR, 0);
}

void softStop() {
  Serial.println("Stop");

  digitalWrite(MOTOR_RIGHT_PWM, LOW);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);

  digitalWrite(MOTOR_LEFT_PWM, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
}

/* ============================== END MOVEMENT ============================== */

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED, LOW);
    delay(BLINK_INTERVAL);
  }
}