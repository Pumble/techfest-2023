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
byte speed = 200;

// BUILT-IN LED
#define LED LED_BUILTIN
#define BLINK_INTERVAL 300

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // SETUPS
  Serial.println("starting setup");
  setupMotors();
  Serial.println("xxxxx");
  setupI2C();

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

void setupI2C() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
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

/* ================================== END MOVEMENT ================================== */

/* ================================== I2C-COMMUNICATION ================================== */

// void receiveEvent(int howMany) {

//   while (1 < Wire.available()) {
//     char c = Wire.read();
//     Serial.print(c);
//   }

//   int x = Wire.read();
//   Serial.print(x);
//   Serial.print("\n");
// }

// void receiveEvent(int howMany) {
//   int c = Wire.read();  // receive a character
//   Serial.print("data received: ");
//   Serial.println(c);
//   if (c == 0) {
//     digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
//   }
//   if (c == 1) {
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   }
// }

#define SL_DATA_SIZE 7
int receivedData[SL_DATA_SIZE] = { 0, 0, 0, 0, 0, 0, 0 };

void receiveEvent(int howmany)  //howmany = Wire.write()executed by Master
{
  Serial.println("============================");
  for (int i = 0; i < howmany; i++) {
    receivedData[i] = Wire.read();
    Serial.print(receivedData[i]);
    Serial.print(", ");
  }
  Serial.println();
}

/* ================================== END I2C-COMMUNICATION ================================== */

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED, LOW);
    delay(BLINK_INTERVAL);
  }
}