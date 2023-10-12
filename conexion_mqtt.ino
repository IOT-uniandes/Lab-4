#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Actualizar ssid, password y mqtt_servere (ip del servidor MQTT) con los datos actuales de conexión del laboratorio.
const char* ssid = "Lab_ML340";
const char* password = "UiSnfCra1";
const char* mqtt_server = "157.253.195.202";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
void setup_wifi() {
  delay(10);
  // Inicio conexión red wifi
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void reconnect() {
  // Queda en loop hasta realizar la conexión
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Crea un ID de cliente de forma aleatoria
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Intento de conexión
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Este es el mensaje que debe enviar cuando conecte
      client.publish("outTopic", "Somos el Grupo #");
      // Vuelve a suscribir
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("Intente de nuevo en 5 segundos");
      delay(5000);
    }
  }
}
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}