#include <SoftwareSerial.h>  //Importamos la librería, usualmente se importa por defecto
SoftwareSerial BT1(1, 0);    //Crea conexion al bluetooth - PIN 1 a TX y PIN 0 a RX
int entrada;

/*
  CONEXIONES:
  ARDUINO   BLUETOOTH
  5V        VCC
  GND       GND
  PIN 1     TX
  PIN 0     RX
*/

void setup() {
  BT1.begin(9600);      //Iniciamos la comunicación con el BT que creamos
  pinMode(13, OUTPUT);  //Definimos el pin 13 como salida
}

void loop() {
  while (BT1.available() == 0) {
  }

  entrada = BT1.read();  //Leemos el valor del BT
  if (entrada == '1') {
    digitalWrite(13, HIGH);  //Encendemos el led de la placa
  } else if (entrada == '2') {
    digitalWrite(13, LOW);  //Apagamos el led de la placa
  }

  //ejemplo con switch
  switch (entrada)  //comparamos el valor guardado en la variable dato
  {
    case 'a':               //si el dato leido es a
      digitalWrite(13, 1);  //Setiamos a 5V el pin 13
      break;
    case 'b':               //si el dato leido es b
      digitalWrite(13, 0);  //setiamos a 0V el pin 13
      break;
  }
}