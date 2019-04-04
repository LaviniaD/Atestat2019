#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <Wire.h>
#include <Arduino.h>

//the library that contains all sensors, except the Soil Humidity one
#include "Sensors.h"

// Replace with your network credentials
const char* ssid = "UPC4747867";
const char* password = "ffyQhrd6whtt";


// Soil Humidity sensor
const int humPin = 34;
int outHum;

struct SensorData sensData;

//the LEDs
const int led1 = 15;
const int led2 = 25;
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String list[9];

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
  server.on("/readSens0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[0]);
  });

 server.on("/readSens1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[1]);
  });

  server.on("/readSens2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[2]);
  });

  server.on("/readSens3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[3]);
  });

  server.on("/readSens4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[4]);
  });

  server.on("/readSens5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[5]);
  });

  server.on("/readSens6", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[6]);
  });

  server.on("/readSens7", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plane", list[7]);
  });
  
  


  // Route to set GPIO to HIGH/LOW
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


  outHum= analogRead(humPin);
  outHum = map(outHum,4095,0,0,100);
  sensData = sensorsRead();

  list[0]=String(outHum);
  list[1]=String(sensData.ShT31D.temp);
  list[2]=String(sensData.ShT31D.humi);
  list[3]=String(sensData.GY30);
  list[4]=String(sensData.mq5);
  list[5]=String(sensData.mq135);
  list[6]=String(sensData.ms5611.pressure);
  list[7]=String(sensData.ms5611.altitude);
   if(list[3].toInt()>300) //there's enough light
  {
    digitalWrite(led2, LOW);    
    digitalWrite(led1, LOW);  
  }
}
