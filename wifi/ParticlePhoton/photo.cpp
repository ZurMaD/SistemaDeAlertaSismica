//********Conexiones********//
//GND - GND
//VCC - VCC
//SDA - Pin A4
//SCL - Pin A5
 //********Librerias********//
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
 //********Constantes********//
 //******MPU6050******//
MPU6050 sensor;
 
int ax, ay, az;
int gx, gy, gz;
int axant = 0, ayant = 0,azant = 0;
float Aceleracion,Aceleracionant;
volatile bool mpuInterrupt = false;

//******Altavoz******//
int pinzumbador = 13;    // pin del zumbador
int frecuencia = 4000;      // frecuencia correspondiente a la nota La

//******Setup******//
void setup()
{
  //********ConfiguracionMPU6050********//
  Serial.begin(57600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
  //********ConfiguracionAltavoz********//
}

//******Loop******//
void loop() 
{ //15500
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  //Calcular modulos
  Aceleracion = pow(( pow(ax,2)+pow(ay,2)+pow(az,2) ),0.5);
  Aceleracionant = pow(( pow(axant,2)+pow(ayant,2)+pow(azant,2) ),0.5);
  //Logica Verificadora de sismo
  if ((abs(Aceleracion-Aceleracionant))>1500){
      tone(pinzumbador,frecuencia);    // inicia el zumbido
      Serial.println("      ALERTA      ");
      
  }else{
    noTone(pinzumbador);               // lo detiene a los dos segundos
  }
 
  delay(9);
  //Mostrar las lecturas separadas por un [tab]
  Serial.print("a[x y z] g[x y z]:\t");
  Serial.print(Aceleracion); Serial.print("\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
  
  
  //Guardado de valores
  axant= ax;
  ayant= ay;
  azant= az;
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  delay(100);

}//********Funciones********//
