/**
 * References
 * https://www.youtube.com/watch?v=YkfBtjs8uWg&ab_channel=ScienceFun
 * H-Bridge: https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 * H-Bridge: https://robots-argentina.com.ar/didactica/puente-h-placa-controladora-de-motores-l9110s/
 * 7-way Multitracking: https://arduinoinfo.mywikis.net/wiki/Robot_7-wayMultiTrackingSensor
 * I2C: https://docs.arduino.cc/tutorials/nano-every/i2c
 * I2C: https://www.tinkercad.com/things/47BHtheMgD5-copy-of-i2c/editel
 * Power up arduino nano: https://linuxhint.com/3-ways-power-up-arduino-nano/
 */

#include <Wire.h>

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
byte speed = 255;
byte turn_speed = 200;
byte hard_turn_speed = 150;

// BUILT-IN LED
#define LED LED_BUILTIN
#define BLINK_INTERVAL 300

enum MOVEMENT_STATUS {
  STAND_BY,
  HARD_LEFT,
  LEFT,
  CENTER,
  RIGHT,
  HARD_RIGHT,
  LOST
};
MOVEMENT_STATUS movement = STAND_BY;
#define MOVEMENT_DELAY 1000
#define MOVEMENT_HARD_DELAY 50

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // SETUPS
  Serial.println("starting setup");

  setupMotors();
  setupI2C();

  Serial.println("setup completed");

  delay(5000);
}

int input = 0;
void loop() {
  switch (movement) {
    case HARD_LEFT:
      hardLeft();
      break;
    case LEFT:
      left();
      break;
    case CENTER:
      forward();
      break;
    case RIGHT:
      right();
      break;
    case HARD_RIGHT:
      hardRight();
      break;
    case LOST:
    case STAND_BY:
      softStop();
      break;
  }
  delay(MOVEMENT_DELAY);
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

void setupI2C() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

/* ================================== END SETUP ================================== */

/* ================================== MOVEMENT ================================== */

void forward() {
  analogWrite(MOTOR_LEFT_PWM, speed);
  analogWrite(MOTOR_LEFT_DIR, 0);

  analogWrite(MOTOR_RIGHT_PWM, speed);
  analogWrite(MOTOR_RIGHT_DIR, 0);
}

void backward() {
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_LEFT_DIR, speed);

  analogWrite(MOTOR_RIGHT_PWM, 0);
  analogWrite(MOTOR_RIGHT_DIR, speed);
}

void left() {
  analogWrite(MOTOR_LEFT_PWM, speed);
  analogWrite(MOTOR_LEFT_DIR, 0);

  digitalWrite(MOTOR_RIGHT_PWM, LOW);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}

void right() {
  digitalWrite(MOTOR_LEFT_PWM, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);

  analogWrite(MOTOR_RIGHT_PWM, speed);
  analogWrite(MOTOR_RIGHT_DIR, 0);
}

void hardLeft() {
  analogWrite(MOTOR_LEFT_PWM, speed);
  analogWrite(MOTOR_LEFT_DIR, 0);

  analogWrite(MOTOR_RIGHT_PWM, 0);
  analogWrite(MOTOR_RIGHT_DIR, speed);
}

void hardRight() {
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_LEFT_DIR, speed);

  analogWrite(MOTOR_RIGHT_PWM, speed);
  analogWrite(MOTOR_RIGHT_DIR, 0);
}

void softStop() {
  // Serial.println("Stop");

  digitalWrite(MOTOR_RIGHT_PWM, LOW);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);

  digitalWrite(MOTOR_LEFT_PWM, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
}

/* ================================== END MOVEMENT ================================== */

/* ================================== I2C-COMMUNICATION ================================== */

/**
 * { 1, 1, 1, 1, 1 } = stand by
 * { 0, 1, 1, 1, 1 } = hard left
 * { 1, 0, 1, 1, 1 } = left
 * { 1, 1, 0, 1, 1 } = center
 * { 1, 1, 1, 0, 1 } = right
 * { 1, 1, 1, 1, 0 } = hard right
 * { 0, 0, 0, 0, 0 } = lost
 */

void receiveEvent(int howMany) {

  char c = Wire.read();  // receive a character
  switch (c) {
    case 'S':
      movement = STAND_BY;
      break;
    case 'L':
      movement = HARD_LEFT;
      break;
    case 'l':
      movement = LEFT;
      break;
    case 'C':
      movement = CENTER;
      break;
    case 'r':
      movement = RIGHT;
      break;
    case 'R':
      movement = HARD_RIGHT;
      break;
    case 'X':
      movement = LOST;
      break;
    default:
      movement = CENTER;
      break;
  }

  Serial.print("selected movement: ");
  Serial.println(c);
}

/* ================================== END I2C-COMMUNICATION ================================== */

/* ================================== TESTING ================================== */

void testLoop() {
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

/* ================================== END TESTING ================================== */

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED, LOW);
    delay(BLINK_INTERVAL);
  }
}


// SEGIR LEYENDO
// https://projecthub.arduino.cc/lightthedreams/line-following-robot-34b1d3
// https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot
