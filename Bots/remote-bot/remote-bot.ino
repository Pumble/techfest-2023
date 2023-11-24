/**
 * RESOURCES
 * Bluetooth: https://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/
 */

// INCLUDES
#include <SoftwareSerial.h>
#include <Servo.h>

/* ================================== VAR DEFINITION ================================== */

// ================================== MOVEMENT VARS
#define MOVEMENT_FORWARD 'F'   // 70
#define MOVEMENT_BACKWARD 'B'  // 66
#define MOVEMENT_LEFT 'L'      // 76
#define MOVEMENT_RIGHT 'R'     // 82
#define MOVEMENT_STOP 'S'      // 83
#define SERVO_DOWN 'M'         // 77
#define SERVO_UP 'N'           // 78

// ================================== MOTOR VARS
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

// ================================== BLUETOOTH VARS
/* Programa el modulo bluetooth HC-06 con un nuevo: 
 * NAME  (Nombre de 20 caracteres)
 * PIN     (Clave de cuatro numeros)
 * BPS     (Velocidad de conexion en baudios) //Mejor no cambiar
 * CONEXIONES:
 * ARDUINO   BLUETOOTH
 * 5V        VCC
 * GND       GND
 * PIN 1     TX
 * PIN 0     RX  
 */
char BT_NAME[21] = "hentaiGratis";  // Nombre de 20 caracteres maximo+
char BT_PASSWORD[5] = "1234";       // PIN O CLAVE de 4 caracteres numericos
#define BT_BPS 19200                // 1=1200 , 2=2400, 3=4800, 4=9600, 5=19200, 6=38400, 7=57600, 8=115200
// #define BT_TX_PIN 1
// #define BT_RX_PIN 0
#define BT_TX_PIN 9
#define BT_RX_PIN 10
SoftwareSerial bt(BT_TX_PIN, BT_RX_PIN);  //Crea conexion al bluetooth - PIN 1 a TX y PIN 0 a RX

// ================================== SERVO VARS
#define SERVO_LEFT_PIN 7
#define SERVO_RIGHT_PIN 8
Servo leftServo;
Servo rightServo;
#define SERVO_INITIAL_POSITION 90
#define SERVO_DOWN_POSITION 15
#define SERVO_MIDDLE_POSITION 45
#define SERVO_HIGH_POSITION 90

// BUILT-IN LED
#define BLINK_INTERVAL 300

/* ================================== END VAR DEFINITION ================================== */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // SETUPS
  Serial.println("starting setup");

  motorSetup();
  servoSetup();
  bluetoothSetup();

  Serial.println("setup completed");
}

void loop() {
  while (bt.available() == 0) {}
  int input = bt.read();
  Serial.println((char)input);

  processCommand(input);
}

/* ================================== SETUP ================================== */
void motorSetup() {
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);
}

void bluetoothSetup() {
  Serial.println("configuring bluetooth");

  bt.begin(BT_BPS);  // inicialmente la comunicacion serial a 9600 Baudios (velocidad de fabrica) MEJOR NO CAMBIAR

  bt.print("AT");       // Inicializa comando AT
  bt.print("AT+ORGL");  // Restaura el dispositivo de fabrica
  delay(1000);

  // Setear los nuevos valores
  bt.print("AT+RESET");  // Reset device
  // bt.print("AT+RMSAD");  // Delete authenticaded device
  delay(1000);  // espera 1 segundo

  bt.print("AT+NAME");  // Configura el nuevo nombre
  bt.print(BT_NAME);

  // bt.print("AT+BAUD");  // Configura la nueva velocidad
  // bt.print(BT_BPS);

  bt.print("AT+PIN");  // Configura el nuevo PIN
  bt.print(BT_PASSWORD);

  bt.flush();

  Serial.println("Bluetooth configured");
  // getBluetoothData();
}

void servoSetup() {
  leftServo.attach(SERVO_LEFT_PIN);    // attaches the servo on pin SERVO_LEFT_PIN to the servo object
  rightServo.attach(SERVO_RIGHT_PIN);  // attaches the servo on pin SERVO_RIGHT_PIN to the servo object

  leftServo.write(SERVO_INITIAL_POSITION);
  rightServo.write(SERVO_INITIAL_POSITION);

  Serial.println("servos configured");
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
  // RIGHT MOTOR GOES FORWARD
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
  // LEFT MOTOR GOES BACKWARD
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
}

void right() {
  stop();
  // LEFT MOTOR GOES FORWARD
  analogWrite(MOTOR_LEFT_SPEED, speed);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  // RIGHT MOTOR GOES BACKWARD
  analogWrite(MOTOR_RIGHT_SPEED, speed);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}

/* ================================== END MOVEMENT ================================== */

/* ================================== BLIETOOTH ================================== */

void getBluetoothData() {
  Serial.println();
  Serial.println();
  Serial.print("VERSION: ");
  Serial.println(bt.print("AT+VERSION"));
  Serial.print("STATE: ");
  Serial.println(bt.print("AT+STATE"));
  Serial.print("ROLE: ");
  Serial.println(bt.print("AT+ROLE"));
  Serial.print("NAME: ");
  Serial.println(bt.print("AT+NAME"));
  Serial.print("PASSWORD: ");
  Serial.println(bt.print("AT+PSWD"));
  delay(1000);  // espera 1 segundo
}

void processCommand(int input) {
  switch (input) {
    case MOVEMENT_FORWARD:
      digitalWrite(LED_BUILTIN, HIGH);
      forward();
      break;
    case MOVEMENT_BACKWARD:
      digitalWrite(LED_BUILTIN, LOW);
      backward();
      break;
    case MOVEMENT_LEFT:
      digitalWrite(LED_BUILTIN, LOW);
      stop();
      left();
      break;
    case MOVEMENT_RIGHT:
      digitalWrite(LED_BUILTIN, HIGH);
      stop();
      right();
      break;
    case MOVEMENT_STOP:
      digitalWrite(LED_BUILTIN, LOW);
      stop();
      break;
    case SERVO_DOWN:
      leftServo.write(SERVO_DOWN_POSITION);
      rightServo.write(SERVO_DOWN_POSITION);
      break;
    case SERVO_UP:
      leftServo.write(SERVO_HIGH_POSITION);
      rightServo.write(SERVO_HIGH_POSITION);
      break;
  }
}

/* ================================== END BLIETOOTH ================================== */

/* ================================== TESTING ================================== */

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED_BUILTIN, LOW);
    delay(BLINK_INTERVAL);
  }
}

void motorTest() {
  int movement_delay = 3000;
  int stop_delay = 1000;

  forward();
  delay(movement_delay);

  stop();
  delay(stop_delay);

  backward();
  delay(movement_delay);

  stop();
  delay(stop_delay);

  left();
  delay(movement_delay);

  stop();
  delay(stop_delay);

  right();
  delay(movement_delay);

  stop();
  delay(stop_delay);
}

void servoTest() {
  int servo_delay = 3000;

  leftServo.write(SERVO_DOWN_POSITION);
  rightServo.write(SERVO_DOWN_POSITION);
  delay(servo_delay);

  leftServo.write(SERVO_MIDDLE_POSITION);
  rightServo.write(SERVO_MIDDLE_POSITION);
  delay(servo_delay);

  leftServo.write(SERVO_HIGH_POSITION);
  rightServo.write(SERVO_HIGH_POSITION);
  delay(servo_delay);
}

/* ================================== END TESTING ================================== */