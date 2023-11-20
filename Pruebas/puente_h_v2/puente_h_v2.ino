/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D10 to motor driver input B-IA.
    Arduino digital output D11 to motor driver input B-IB.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
    https://robots-argentina.com.ar/didactica/puente-h-placa-controladora-de-motores-l9110s/
 
  https://www.BananaRobotics.com
*/

// wired connections
#define HG7881_B_IA 10  // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 11  // D11 --> Motor B Input B --> MOTOR B -

// functional connections
#define MOTOR_B_PWM HG7881_B_IA  // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB  // Motor B Direction

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50     // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200    // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000  // brief delay for abrupt motor changes

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  digitalWrite(MOTOR_B_DIR, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
}

void loop() {
  delay(2000);
  analogWrite(MOTOR_B_PWM, 64);
  analogWrite(MOTOR_B_DIR, 128);
  delay(2000);
  analogWrite(MOTOR_B_PWM, 0);
  analogWrite(MOTOR_B_DIR, 128);
  delay(2000);
  analogWrite(MOTOR_B_PWM, 250);
  analogWrite(MOTOR_B_DIR, 0);
  delay(2000);
}