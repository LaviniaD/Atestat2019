// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <Wire.h>
#include <Arduino.h>

//include the library for all the sensors exept humidity
#include "Sensors.h"

// Replace with your network credentials
const char* ssid = "UPC4747867";
const char* password = "ffyQhrd6whtt";


// Soil Humidity sensor
const int humPin = 34;

//the sensor struct -> i ll use this to send the data from the sesnors
struct SensorData sensData;

//the LEDs
const int led1 = 15;
const int led2 = 2;
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//string here
String shumi;
String sens1;
String sens2;
String sens3;
String sens4;
String sens5;
String sens6;
String sens7;

String processor(const String& var)
{
  
  return String();
}


void setup() {
  Wire.begin();
Serial.begin(115200);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
digitalWrite( led1, LOW);
digitalWrite( led2, LOW);
 //initialize the sensors here
 sensorsInit();

  if(!SPIFFS.begin()){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
 
  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
  });

  

  //========================read the sensors and send the data ==============
  server.on("/readADC", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", shumi);
  });

 server.on("/readSens1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens1);
  });

  server.on("/readSens2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens2);
  });

  server.on("/readSens3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens3);
  });

  server.on("/readSens4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens4);
  });

  server.on("/readSens5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens5);
  });

  server.on("/readSens6", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens6);
  });

  server.on("/readSens7", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", sens7);
  });

  
  // Route to set GPIO to HIGH
  server.on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led1, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led1, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/on2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led2, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/off2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led2, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  shumi = String(analogRead(humPin));
  sensData = sensorsRead();
  sens1=String(sensData.ShT31D.temp);
  sens2=String(sensData.ShT31D.humi);
  sens3=String(sensData.GY30);
  sens4=String(sensData.mq5);
  sens5=String(sensData.mq135);
  sens6=String(sensData.ms5611.pressure);
  sens7=String(sensData.ms5611.altitude);

}
