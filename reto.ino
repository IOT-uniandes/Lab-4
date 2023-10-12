#include "UbidotsESPMQTT.h"
#define TOKEN "BBFF-EESPNleFuxUwENPdC74YyvgzBezbIV"
#define WIFINAME "LAB_ML340"
#define WIFIPASS "UiSnfCra1"
#define ID1 "park1"
Ubidots client(TOKEN);

void setup(){
  Serial.begin(115200);
  client.setDebug(true);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  pinMode(2, INPUT);
}
