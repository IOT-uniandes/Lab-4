/*#include "UbidotsESPMQTT.h"
#define TOKEN "BBFF-fd78a2a5f865f0c23ff51f142c418c949ea"
#define WIFINAME "Lab_ML340"
#define WIFIPASS "UiSnfCra1"
//#define ID1 "park1"
Ubidots client(TOKEN);

void setup(){
  Serial.begin(115200);
  client.setDebug(true);
  client.wifiConnection(WIFINAME, WIFIPASS);
  //client.begin(callback);
  //pinMode(2, INPUT);
}*/

/****************************************
 * Include Libraries
 ****************************************/
 
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <stdio.h>  


/****************************************
 * Define Constants
 ****************************************/

#define WIFISSID "Tony" // Put your WifiSSID here
#define PASSWORD "abcdefgh" // Put your wifi password here
#define TOKEN "BBFF-5HXoey9AJWqvpGGY3v6F6rNSmchX0a"
#define DEVICE_LABEL "Lab4" // Assig the device label
#define MQTT_CLIENT_NAME "1" // MQTT client Name

#define VARIABLE_LABEL_1 "puesto1"
#define VARIABLE_LABEL_2 "puesto2"
#define VARIABLE_LABEL_3 "puesto3"
#define VARIABLE_LABEL_4 "puesto4"
#define VARIABLE_LABEL_5 "puesto5"
#define VARIABLE_LABEL_6 "puesto6"
#define VARIABLE_LABEL_7 "puesto7"
#define VARIABLE_LABEL_8 "puesto8"

char mqttBroker[] = "things.ubidots.com";
char payload[700];
char topic[150];

// Space to store values to send
char str_temp[6];
char str_lat[6];
char str_lng[6];

/****************************************
 * Define Variables for IR Sensor
 ****************************************/

bool countloop = true;
int prevX1 = 0;
int prevX2 = 0;
int prevX3 = 0;
int prevX4 = 0;
int prevX5 = 0;
int prevX6 = 0;
int prevX7 = 0;
int prevX8 = 0;

/****************************************
 * Initializate constructors for objects
 ****************************************/

ESP8266WiFiMulti WiFiMulti;
WiFiClient ubidots;
PubSubClient client(ubidots);


/****************************************
 * Auxiliar Functions
 ****************************************/
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
} 

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN,"")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("Try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}


/****************************************
 * Main Functions
 ****************************************/
 
void setup() {
    Serial.begin(115200);
    WiFiMulti.addAP(WIFISSID, PASSWORD);
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(mqttBroker, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
      reconnect();

      // Subscribes for getting the value of the control variable in the temperature-box device
      /*char topicToSubscribe[200];
      sprintf(topicToSubscribe, "%s", ""); // Cleans the content of the char
      sprintf(topicToSubscribe, "%s%s", "/v1.6/devices/", "temperature-box");
      sprintf(topicToSubscribe, "%s/%s/lv", topicToSubscribe, "control");
      client.subscribe(topicToSubscribe);*/
    }

    // Values to send

    if (Serial.available() > 0) {
      String received = Serial.readStringUntil('\n');
      int x1,x2,x3,x4,x5,x6,x7,x8;
      sscanf(received.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d", &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);

      float lat = 6.101;
      float lng= -1.293;

      /* START VARIABLE 1 */
      if (x1 != prevX1) {
        dtostrf(x1, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_1); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload1:");
        Serial.println(payload);
        prevX1 = x1;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 1 */

      /* START VARIABLE 2 */
      if (x2 != prevX2) {
        dtostrf(x2, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_2); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload2:");
        Serial.println(payload);
        prevX2 = x2;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 2 */

      /* START VARIABLE 3 */
      if (x3 != prevX3) {
        dtostrf(x3, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_3); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload3:");
        Serial.println(payload);
        prevX3 = x3;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 3 */

      /* START VARIABLE 4 */
      if (x4 != prevX4) {
        dtostrf(x4, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_4); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload4:");
        Serial.println(payload);
        prevX4 = x4;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 4 */

      /* START VARIABLE 5 */
      if (x5 != prevX5) {
        dtostrf(x5, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_5); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload5:");
        Serial.println(payload);
        prevX5 = x5;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 5 */

      /* START VARIABLE 6 */
      if (x6 != prevX6) {
        dtostrf(x6, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_6); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload6:");
        Serial.println(payload);
        prevX6 = x6;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }
      /* END VARIABLE 6 */

      /* START VARIABLE 7 */
      if (x7 != prevX7) {
        dtostrf(x7, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_7); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload7:");
        Serial.println(payload);
        prevX7 = x7;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }

      /* END VARIABLE 7 */

      /* START VARIABLE 8 */
      if (x8 != prevX8) {
        dtostrf(x8, 4, 2, str_temp);
        dtostrf(lat, 4, 2, str_lat);
        dtostrf(lng, 4, 2, str_lng);

        sprintf(topic, "%s", ""); // Cleans the topic content
        sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

        sprintf(payload, "%s", ""); // Cleans the payload content
        sprintf(payload, "{\"%s\":", VARIABLE_LABEL_8); // Adds the variable label   
        sprintf(payload, "%s {\"value\": %s", payload, str_temp); // Adds the value
        sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
        sprintf(payload, "%s } }", payload); // Closes the dictionary brackets

        Serial.print("\tTopic:");
        Serial.println(topic);
        Serial.print("\tPayload8:");
        Serial.println(payload);
        prevX8 = x8;
        client.publish(topic, payload);
        client.loop();
        delay(2000);
      }

      /* END VARIABLE 8 */


      //client.loop();
    }

}

