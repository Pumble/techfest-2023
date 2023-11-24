int cny_LED = 2;  // salida de KY-033 a pin digital 2
int val_SLin;     // almacena valor leido del sensor
//int ANTERIOR = 1;   // almacena ultimo valor leido del sensor

void setup() {
  Serial.begin(9600);       // inicializa comunicacion serie a 9600 bps
  pinMode(cny_LED, INPUT);  // pin 2 como entrada
}

void loop() {
  val_SLin = digitalRead(cny_LED);  // lee valor de sensor y asigna a variable VALOR

  if (val_SLin == HIGH)       // si VALOR tiene un nivel alto es linea negra
    Serial.println("NEGRO");  // imprime en monitor serial la palabra Linea
  else                        // si VALOR tiene un nivel bajo es fuera de linea
    Serial.println("BLANCO");



  //  if (VALOR != ANTERIOR){   // si el valor es distinto del ultimo
  //    if (VALOR == HIGH)    // si VALOR tiene un nivel alto es linea negra
  //    Serial.println("Linea");  // imprime en monitor serial la palabra Linea
  //    else      // si VALOR tiene un nivel bajo es fuera de linea
  //    Serial.println("Fuera");  // imprime en monitor serial la palabra Fuera
  //    ANTERIOR = VALOR;   // actualiza variable ANTERIOR con el actual de VALOR
  //  }
  delay(500);  // breve demora de medio segundo
}