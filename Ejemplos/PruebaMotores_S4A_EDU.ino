/*CONFIGURACION DEL S4A EDU

Pines Motor Derecho:
D6 -> Velocidad
D11 -> Dirección de Giro
 
Pines Motor Izquierdo: 
D5 -> Velocidad
D10 -> Dirección de Giro*/

//Variables
int VL = 5,VR = 6; //Pines de Velocidad
int GL = 10, GR = 11; //Pines de Dirección de Giro
int vel = 255; //de 50 a 255 funciona bien


void setup()
{
  //Seteamos los motores
  pinMode(VL,OUTPUT);
  pinMode(VR,OUTPUT);
  pinMode(GL,OUTPUT);
  pinMode(GR,OUTPUT);
}

void loop()
{
   Probamos();
}

void Probamos() {
  adelante();
  delay(1000);
  
  detener();
  delay(1000);
  
  atras();
  delay(1000);
  
  detener();
  delay(1000);
  
  izquierda();
  delay(1000);

  detener();
  delay(1000);
  
  derecha();
  delay(1000);

  detener();
  delay(1000);
}


//DIRECCIONES
void adelante() {
  analogWrite(VL,vel);
  digitalWrite(GL,HIGH);
  analogWrite(VR,vel);
  digitalWrite(GR,HIGH);
}

void atras() {
  analogWrite(VL,vel);
  digitalWrite(GL,LOW);
  analogWrite(VR,vel);
  digitalWrite(GR,LOW);
}

void detener() {
  analogWrite(VL,0);
  analogWrite(VR,0);
}

void izquierda() {
  detener();
  analogWrite(VL,vel);
  digitalWrite(GL,HIGH);
}
void derecha() {
  detener();
  analogWrite(VR,vel);
  digitalWrite(GR,HIGH);
}
