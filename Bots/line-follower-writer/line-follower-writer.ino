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
#define SL_S1 2    // LeftOut
#define SL_S2 3    // LeftIn
#define SL_S3 4    // Center
#define SL_S4 5    // RightIn
#define SL_S5 6    // RightOut
#define SL_CLP 7   // Bump
#define SL_NEAR 8  // Near
#define SL_DATA_SIZE 7
int dataToSend[SL_DATA_SIZE] = { 0, 0, 0, 0, 0, 0, 0 };
#define READ_INTERVAL 100

#define BLINK_INTERVAL 300

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
    ;

  // SETUPS
  Serial.println("starting setup");
  setupI2C();
  Serial.println("setup completed");
}

void loop() {
  getSensorData();
  Wire.beginTransmission(8);
  for (int i = 0; i < SL_DATA_SIZE; i++) {
    Wire.write(dataToSend[i]);  //data bytes are queued in local buffer
  }
  Wire.endTransmission();
  delay(READ_INTERVAL);
}

/* ================================== SETUP ================================== */

void setupI2C() {
  Wire.begin();  // join i2c bus (address optional for writer).
}

/* ================================== END SETUP ================================== */

/* ================================== LINE FOLLOWER ==================================*/

void getSensorData() {
  dataToSend[0] = digitalRead(SL_S1);
  dataToSend[1] = digitalRead(SL_S2);
  dataToSend[2] = digitalRead(SL_S3);
  dataToSend[3] = digitalRead(SL_S4);
  dataToSend[4] = digitalRead(SL_S5);
  dataToSend[5] = digitalRead(SL_CLP);
  dataToSend[6] = digitalRead(SL_NEAR);
}

// For debugging
void showSensorData() {
  Serial.print("============================");
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
