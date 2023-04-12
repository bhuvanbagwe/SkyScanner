#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

//#include "Slider_Code.h"; // Refer's to the Slider_code window
#define Panservopin 5 //D1
#define Tiltservopin 4 //D2
//#define sensor A0;

int Panval=0;
int Tiltval=0;
float sensor=0;
const char* ssid = "BAGWE 2.4G";  // SSID
const char* password = "swanandib"; //Pass

Servo Panservo, Tiltservo;  //create servo object to control a servo
AsyncWebServer server(80);  //Server is always on port 80

// Function for Sensor Value 
String sensorval()
{
  sensor = analogRead(A0);
  if (isnan(sensor)) {
    Serial.println("Unable to detect Sensor");
    return "";
  }
  else {
    Serial.println(sensor);
    return String(sensor);
  }
}
//String piezoval() {}

void setup() 
{
  // put your setup code here, to run once:
pinMode(12,INPUT);
Panservo.attach(5);
Tiltservo.attach(4);

Panservo.write(0);
Tiltservo.write(0);

Serial.begin(115200);// Baud Rate
delay(500);
Panservo.attach(Panservopin); //servo on D1
Tiltservo.attach(Tiltservopin);//servo on D2

bool status; 
 if(!SPIFFS.begin())
 {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
WiFi.begin(ssid, password);
Serial.print(" Initializing Conncetion to : ");
Serial.println(ssid);
Serial.println("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("....");
}
Serial.print(" Please access the assembly at ");
Serial.println(WiFi.localIP());
server.begin();  
Serial.println("Server Activated");

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", sensorval().c_str());
  });

  // Start server
  server.begin();
}



void loop() 
{
// put your main code here, to run repeatedly:
int signalval= analogRead(A0);
for (Panval=0; Panval<=180; Panval++ )
{
  Panservo.write(Panval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(100);
}
for (Panval>=180; Tiltval<=180; Tiltval++)
{
  Tiltservo.write(Tiltval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(10);
  }
for (Panval<=180-1; Panval>=0; Panval++ )
{
  Panservo.write(Panval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(10);
}
for (Tiltval<=180-1; Tiltval>=0; Tiltval++ )
{
  Tiltservo.write(Tiltval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(10);
}
for (Panval<=180; Panval>=0; Panval-- )
{
  Panservo.write(Panval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(10);
}
for (Tiltval<=180; Tiltval>=0; Tiltval-- )
{
  Tiltservo.write(Tiltval);
  Serial.print("Pan Angle : ");
  Serial.println(Panval);
  Serial.print("Tilt Angle : ");
  Serial.println(Tiltval);
  Serial.print("Signalval : ");
  sensorval();
//  Serial.println(signalval);
//  Serial.println("");
  delay(10);
}
}
