#include <Servo.h> // libreria del servo

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and blynk
save space */
#define BLYNK_PRINT Serial // libreria de Blynk 


#include <ESP8266WiFi.h> // libreria de coneccion WIFI
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "lAfFOyblDED7hFAJI7nHQImlMmzaM4uG"; // Token de Blynk

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "HOME-2A12";// nombre de la red WIFI
//char pass[] = "64A1B6166758ACA2"; // clave de la red WIFI
char ssid[] = "AndroidAP";// nombre de la red WIFI con el smartphone
char pass[] = "rplk9969"; // clave de la red WIFI con el smartphone

Servo ServoPuerta;

BLYNK_WRITE(V1){
  int Estado = param.asInt(); // verifica el estado del boton de puerta del garaje
  if (Estado == HIGH){
    ServoPuerta.write(180); // si es High, abre la puerta
  }
  if (Estado == LOW){
    ServoPuerta.write(90); // si es LOW, cierra la puerta
  }
}
void setup()
{
  // Debug console
  Serial.begin(9600); //Inicia puerto serial, no se esta usando
ServoPuerta.attach(14); // inicia el servo por el pin 14 del NodeMCU
pinMode(12,INPUT);// sensor ventana
pinMode(13,INPUT);// sensor puerta
pinMode(15,OUTPUT);// buzzer
digitalWrite(15,LOW); // Apaga el buzzer desde un inicio
  Blynk.begin(auth, ssid, pass); // inicia Blynk con coneccion a la red  Wifi
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

}
void leerSensores(){
  if(!digitalRead(12)){ // lee el pin 12 del NodeMCU, sensor de ventana 
  digitalWrite(15,HIGH); // activa el buzzer
  Blynk.notify("Alarma de Ventana abierta"); // envia mensaje al celular
  //delay(300);
}
else{
  digitalWrite(15,LOW); // apaga el buzzer
}
if(!digitalRead(13)){ // lee el pin del NodeMCU, sensor de puerta
 digitalWrite(15,HIGH); // activa el buzzer
 Blynk.notify("Alarma puerta abierta"); // envia mensaje al celular
 // delay(300);
}
else{
  digitalWrite(15,LOW); // apaga el buzzer
}
}


void loop()
{

  Blynk.run(); // corre siempre la libreria de Blynk
leerSensores(); // corre la funcion para leer los sensores de la puerta y ventana.
  
}
