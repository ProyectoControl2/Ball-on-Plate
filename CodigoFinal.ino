
# include  <Servo.h>   /* Incluir para servos */
# include  <PID_v1.h>  /* Incluir para PID      */

Servo uno;
Servo dos;
int pos=0;
int pos2=0;
char lectura; //Variable para guardar la lectura del Serial
bool datoX=true;
bool datoY=false;
double EjeX;
double EjeY;
int cont=0;
int preanguloX=0;
int anguloX=0;
int preanguloY=0;
int anguloY=0;
int preanguloPIDX=0;
int anguloPIDX=0;
int preanguloPIDY=0;
int anguloPIDY=0;

String stringEjeX;
String stringEjeY;


double KpX=0.3, KiX=0.03, KdX=0.08;
double SetpointX, InputX, OutputX;
double KpY=0.3, KiY=0.08, KdY=0.13;
double SetpointY, InputY, OutputY;


PID PIDX(&InputX, &OutputX, &SetpointX, KpX, KiX, KdX, DIRECT);
PID PIDY(&InputY, &OutputY, &SetpointY, KpY, KiY, KdY, DIRECT);
void setup()
{
   //Iniciamos el Serial:
   Serial.begin(9600);
    uno.attach(10);
    dos.attach(11);
  
  InputY = EjeY;
  SetpointX = 0;
  InputX = EjeX;
  SetpointY = 0;

  //turn the PID on
  PIDX.SetMode(AUTOMATIC);
  PIDY.SetMode(AUTOMATIC);

}

void loop()
{
   //Si recibimos algo por serial, lo guardamos
   if(Serial.available() >= 1)
   {    
    do{
      lectura = Serial.read();  
      if(datoX){
      stringEjeX=lectura;
      datoX=false;
      cont=cont+1;
      EjeX=stringEjeX.toDouble();
      }
      else{
      EjeY=lectura;
      datoX=true;
      cont=cont+1;
      EjeY=stringEjeY.toDouble();
      }
    }while(cont<2); 
    cont=0;
  preanguloX=EjeX*0.4;
  anguloPIDX=preanguloPIDX+90;
  preanguloPIDY=EjeY*0.32;
  anguloPIDY=preanguloPIDY+90;
  SetpointX = 0;
  SetpointY = 0;
  InputX = anguloPIDX;
  InputY = anguloPIDY;
  PIDX.Compute();
  PIDY.Compute();
  preanguloX=OutputX*0.4;
  anguloX=preanguloX+90;
  uno.write(anguloX);
  preanguloY=OutputY*0.32;
  anguloY=preanguloY+90;
  dos.write(anguloY);
 }
}

      /*
   
      if(lectura == 'a')
      {
      digitalWrite(LED, HIGH);
      for(pos=0;pos<170;pos +=2)
      {
        uno.write(pos);
        dos.write(pos);
        }
      }
      if(lectura == 'b')
      {
       for (pos = 180; pos > 10; pos -= 2) { 
       dos.write(pos);
       pos2=(pos-180)*(-1);
       uno.write(pos2);
       }
      }
      if(lectura == 'c')
      {
       for (pos = 180; pos > 10; pos -= 2) { 
       uno.write(pos);
       pos2=(pos-180)*(-1);
       dos.write(pos2);
       }
      }
      if(lectura == 'd')
      {
       digitalWrite(LED, LOW);         
       for (pos = 180; pos > 10; pos -= 2) { 
       uno.write(pos);
       dos.write(pos);
       }
      }
   */
   

