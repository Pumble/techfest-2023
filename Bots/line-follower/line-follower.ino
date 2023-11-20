/**
 * Fuentes
 * https://www.youtube.com/watch?v=YkfBtjs8uWg&ab_channel=ScienceFun
 * https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 */

// wired connections
#define HG7881_B_IA 10  // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 9   // D11 --> Motor B Input B --> MOTOR B -

// functional connections
#define MOTOR_B_PWM HG7881_B_IA  // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB  // Motor B Direction






#define A1A 5  // D5
#define A1B 4  // D4


#define MOVEMENT_FORWARD 'F'
#define MOVEMENT_BACKWARD 'B'
#define MOVEMENT_LEFT 'L'
#define MOVEMENT_RIGHT 'R'
#define MOVEMENT_STOP 'S'
int speed = 51;

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
        rotateLeft();
        break;
      case MOVEMENT_RIGHT:
        rotateRight();
        break;
      case MOVEMENT_STOP:
        stop();
        break;
    }
  }
}

/* ============================== SETUP ============================== */

void setupMotors() {
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  digitalWrite(MOTOR_B_DIR, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
}

/* ============================== END SETUP ============================== */

/* ============================== MOVEMENT ============================== */

void forward() {
  Serial.println("forward");

  digitalWrite(MOTOR_B_DIR, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
  // set the motor speed and direction
  digitalWrite(MOTOR_B_DIR, HIGH);           // direction = forward
  analogWrite(MOTOR_B_PWM, 200);  // PWM speed = fast
}

void backward() {
  // digitalWrite(LED, LOW);

  // analogWrite(B2A, 0);
  // analogWrite(B1A, speed);

  // digitalWrite(A1A, HIGH);
  // digitalWrite(A1B, LOW);
}

void rotateRight() {
}

void rotateLeft() {
}

void stop() {
  // digitalWrite(LED, LOW);

  // analogWrite(B2A, 0);
  // analogWrite(B1A, speed);

  // digitalWrite(A1A, LOW);
  // digitalWrite(A1B, LOW);
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