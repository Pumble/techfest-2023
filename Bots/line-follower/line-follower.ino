/**
 * Fuentes
 * https://www.youtube.com/watch?v=YkfBtjs8uWg&ab_channel=ScienceFun
 * https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 */

#define A1A 3
#define A1B 2
#define B1A 10
#define B1B 11

#define MOVEMENT_FORWARD 'F'
#define MOVEMENT_BACKWARD 'B'
#define MOVEMENT_LEFT 'L'
#define MOVEMENT_RIGHT 'R'
#define MOVEMENT_STOP 'S'
int speed = 51;
#define MOVEMENT_SPEED_UP 'U'
#define MOVEMENT_SPEED_DOWN 'D'

// BUILT-IN LED
#define LED 13
#define BLINK_INTERVAL 300





void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void forward() {  //function of forward
  digitalWrite(LED, HIGH);

  analogWrite(B1B, 0);
  analogWrite(B1A, speed);

  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
}

void backward() {  //function of backward
  digitalWrite(LED, LOW);

  analogWrite(B1B, 0);
  analogWrite(B1A, speed);

  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
}

void rotateRight() {

}

void rotateLeft() {
  
}

void stop() {  //function of stop
  digitalWrite(LED, LOW);

  analogWrite(B1B, 0);
  analogWrite(B1A, speed);

  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
}

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED, LOW);
    delay(BLINK_INTERVAL);
  }
}