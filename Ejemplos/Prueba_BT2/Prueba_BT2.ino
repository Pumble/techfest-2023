#include <SoftwareSerial.h>  //Importamos la librería, usualmente se importa por defecto
SoftwareSerial BT1(3, 2);    //Crea conexion al bluetooth - PIN 3 a TX y PIN 2 a RX
int entrada;

/*
  CONEXIONES:
  ARDUINO   BLUETOOTH
  5V        VCC
  GND       GND
  PIN 3     TX
  PIN 2     RX
*/

void setup() {
  Serial.begin(9600);   //Inicializamos la comunicación serial con el arduino
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

  Serial.println(entrada);  //podemos visualizar el dato que ingresamos, en la salida del Monitor se visualiza en código
}