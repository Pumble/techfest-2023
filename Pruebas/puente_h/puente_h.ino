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
  pinMode(LED, OUTPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  // // Resetear los pins
  // digitalWrite(A1A, LOW);
  // digitalWrite(A2A, LOW);
  // digitalWrite(B1A, LOW);
  // digitalWrite(B1B, LOW);

  // Iniciar el serial
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps

  Serial.println("select direction of movement");
  Serial.println("F.forward");
  Serial.println("B.backward");
  Serial.println("L.left");
  Serial.println("R.right");
  Serial.println("S.stop");
}

int input = 0;
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    input = (char)Serial.read();
    Serial.println((char)input);

    switch (input) {
      case MOVEMENT_FORWARD:
        forward();
        break;
      case MOVEMENT_BACKWARD:
        digitalWrite(LED, LOW);
        backward();
        break;
      case MOVEMENT_LEFT:
        digitalWrite(LED, LOW);
        break;
      case MOVEMENT_RIGHT:
        digitalWrite(LED, HIGH);
        break;
      case MOVEMENT_STOP:
        digitalWrite(LED, LOW);
        break;
      case MOVEMENT_SPEED_UP:
        speedUp();
        break;
      case MOVEMENT_SPEED_DOWN:
        speedDown();
        break;
    }
  }
}

void speedUp() {
  speed += 51;
  if (speed > 255)
    speed = 255;
}

void speedDown() {
  speed -= 51;
  if (speed < 51)
    speed = 51;
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