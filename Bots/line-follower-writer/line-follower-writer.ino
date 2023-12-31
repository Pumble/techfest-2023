/**
 * This arduino is in charge of control the line follower, and it will 
 * send the instructions to the main arduino.
 *
 * References
 * 7-way Multitracking: https://arduinoinfo.mywikis.net/wiki/Robot_7-wayMultiTrackingSensor
 * I2C: https://docs.arduino.cc/tutorials/nano-every/i2c
 * I2C: https://www.tinkercad.com/things/47BHtheMgD5-copy-of-i2c/editel
 * Power up arduino nano: https://linuxhint.com/3-ways-power-up-arduino-nano/
 * Array I2C: https://forum.arduino.cc/t/solved-sending-array-data-with-i2c/537012/3
 */

#include <Wire.h>

// ================================== Wired connections ==================================

// SL: Sensor Line
#define SL_S1 2  // LeftOut
#define SL_S2 3  // LeftIn
#define SL_S3 4  // Center
#define SL_S4 5  // RightIn
#define SL_S5 6  // RightOut

#define SL_DATA_SIZE 5
int dataToSend[SL_DATA_SIZE] = { 0, 0, 0, 0, 0 };  // we going to ignore near and bumper for now
#define READ_INTERVAL 100
#define BLINK_INTERVAL 300
#define INITIAL_DELAY 5000

char movement = NULL;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
    ;

  // SETUPS
  Serial.println("starting setup");
  setupI2C();
  setupLineFollower();
  Serial.println("setup completed");
  delay(INITIAL_DELAY);
}

void loop() {
  getSensorData();
  // showSensorData();

  Wire.beginTransmission(8);  // transmit to device #8
  Wire.write(movement);       // sends the given value
  Wire.endTransmission();


  delay(READ_INTERVAL);
}

/* ================================== SETUP ================================== */

void setupI2C() {
  Wire.begin();  // join i2c bus (address optional for writer).
}

void setupLineFollower() {
  digitalWrite(SL_S1, LOW);
  digitalWrite(SL_S2, LOW);
  digitalWrite(SL_S3, LOW);
  digitalWrite(SL_S4, LOW);
  digitalWrite(SL_S5, LOW);
}

/* ================================== END SETUP ================================== */

/* ================================== LINE FOLLOWER ==================================*/

void getSensorData() {
  dataToSend[0] = digitalRead(SL_S1);
  dataToSend[1] = digitalRead(SL_S2);
  dataToSend[2] = digitalRead(SL_S3);
  dataToSend[3] = digitalRead(SL_S4);
  dataToSend[4] = digitalRead(SL_S5);

  if (dataToSend[0] == 1 && dataToSend[1] == 1 && dataToSend[2] == 1 && dataToSend[3] == 1 && dataToSend[4] == 1) {
    movement = 'S';
  } else if (dataToSend[0] == 0 && dataToSend[1] == 1 && dataToSend[2] == 1 && dataToSend[3] == 1 && dataToSend[4] == 1) {
    movement = 'L';
  } else if (dataToSend[0] == 1 && dataToSend[1] == 0 && dataToSend[2] == 1 && dataToSend[3] == 1 && dataToSend[4] == 1) {
    movement = 'l';
  } else if (dataToSend[0] == 1 && dataToSend[1] == 1 && dataToSend[2] == 0 && dataToSend[3] == 1 && dataToSend[4] == 1) {
    movement = 'C';
  } else if (dataToSend[0] == 1 && dataToSend[1] == 1 && dataToSend[2] == 1 && dataToSend[3] == 0 && dataToSend[4] == 1) {
    movement = 'r';
  } else if (dataToSend[0] == 1 && dataToSend[1] == 1 && dataToSend[2] == 1 && dataToSend[3] == 1 && dataToSend[4] == 0) {
    movement = 'R';
  } else if (dataToSend[0] == 0 && dataToSend[1] == 0 && dataToSend[2] == 0 && dataToSend[3] == 0 && dataToSend[4] == 0) {
    movement = 'X';
  } else {  // SINO, vamos de frente
    movement = 'C';
  }
}

// For debugging
void showSensorData() {
  Serial.print("============================");
  Serial.println();
  for (int i = 0; i < SL_DATA_SIZE; i++) {
    Serial.print(dataToSend[i]);
    Serial.print(", ");
  }
  Serial.println();
}

/* ================================== END LINE FOLLOWER ==================================*/

void toogleLight(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED_BUILTIN, LOW);
    delay(BLINK_INTERVAL);
  }
}
