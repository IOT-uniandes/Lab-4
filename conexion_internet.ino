#include "ESP8266WiFi.h"

const char* ssid = "Lab_ML340";
const char* password = "UiSnfCra1";
const char* mqtt_server = "157.253.205.17";

void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(115200);
  setup_wifi();
}

void loop(){
  
}
