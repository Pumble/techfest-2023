/*
 * 1A: speed
 * 1B: direction.
 */
#define MOTOR_A_IA 7
#define MOTOR_A_IB 8
#define MOTOR_B_IA 10
#define MOTOR_B_IB 11

const int MOTOR_SPEED_INTERVAL = 51;
int motor_speed = 255;
#define MOTOR_DIR_DELAY 200  // brief delay for abrupt motor changes

// FUNCIONA COMO PROXY, PARA HACERLO MAS LEGIBLE
#define MOTOR_A_PWM MOTOR_A_IA  // Motor A PWM Speed
#define MOTOR_A_DIR MOTOR_A_IB  // Motor A Direction
#define MOTOR_B_PWM MOTOR_B_IA  // Motor B PWM Speed
#define MOTOR_B_DIR MOTOR_B_IB  // Motor B Direction

#define MOVEMENT_FORWARD 'F'
#define MOVEMENT_BACKWARD 'B'
#define MOVEMENT_STOP 'S'
#define GEAR_UP '+'
#define GEAR_DOWN '-'


void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // SETEAR LOS PINES
  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);

  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);
  digitalWrite(MOTOR_B_DIR, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
}

void loop() {
  boolean isValidInput;
  // draw a menu on the serial port
  Serial.println("-----------------------");
  Serial.println("MENU:");
  Serial.println("U) Speed Up");
  Serial.println(MOVEMENT_FORWARD + ") Forward");
  Serial.println("D) Speed Down");
  Serial.println("R) Reverse");
  Serial.println("B) Brake");
  Serial.println("-----------------------");
  do {
    byte c;
    // get the next character from the serial port
    Serial.print("?");
    while (!Serial.available())
      ;  // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch ((int)c) {
      case GEAR_UP:             // 1) Speed Up
        speedUp();
        isValidInput = true;
        break;

      case MOVEMENT_FORWARD:    // 2) Forward
        forward();
        isValidInput = true;
        break;

      case GEAR_DOWN:           // 3) Speed down
        speedDown();
        isValidInput = true;
        break;

      case MOVEMENT_BACKWARD:   // 4) Reverse
        reverse();
        isValidInput = true;
        break;

      case MOVEMENT_STOP:       // 5) Brake
        brake();
        isValidInput = true;
        break;
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        Serial.println("Invalid");
        break;
    }
  } while (isValidInput == true);

  // repeat the main loop and redraw the menu...
}

void speedUp() {
  Serial.println("Speed Up...");
  motor_speed += MOTOR_SPEED_INTERVAL;
  if (motor_speed > HIGH)
    motor_speed = HIGH;
  Serial.println("speed: " + motor_speed);
}

void speedDown() {
  Serial.println("Speed down...");
  motor_speed -= MOTOR_SPEED_INTERVAL;
  if (motor_speed < MOTOR_SPEED_INTERVAL)
    motor_speed = MOTOR_SPEED_INTERVAL;
  Serial.println("speed: " + motor_speed);
}

void forward() {
  Serial.println("Forward...");

  // always stop motors briefly before abrupt changes
  brake();

  // set the motor speed and direction
  digitalWrite(MOTOR_A_DIR, HIGH);        // direction = forward
  analogWrite(MOTOR_A_PWM, motor_speed);  // PWM speed = fast
  digitalWrite(MOTOR_B_DIR, HIGH);        // direction = forward
  analogWrite(MOTOR_B_PWM, motor_speed);  // PWM speed = fast
}

void reverse() {
  Serial.println("Reverse...");
  // always stop motors briefly before abrupt changes
  brake();

  // set the motor speed and direction
  digitalWrite(MOTOR_A_DIR, LOW);         // direction = reverse
  analogWrite(MOTOR_A_PWM, motor_speed);  // PWM speed = fast
  digitalWrite(MOTOR_B_DIR, LOW);         // direction = reverse
  analogWrite(MOTOR_B_PWM, motor_speed);  // PWM speed = fast
}

void brake() {
  Serial.println("Brake...");
  // always stop motors briefly before abrupt changes
  digitalWrite(MOTOR_A_DIR, LOW);
  digitalWrite(MOTOR_A_PWM, LOW);
  digitalWrite(MOTOR_B_DIR, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
  delay(MOTOR_DIR_DELAY);
}