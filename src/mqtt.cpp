#include "mqtt.h"

WiFiClient espClient;
PubSubClient mqttclient(espClient);
// const char* mqtt_server = "18.162.55.224";
char* mqtt_server = "codeguys-mqtt.lol";
uint16_t mqtt_port = 1883;
String s=";";
int id = 0;
char* MQTT_CLIENT_NAME = "nathalie";
char* MQTT_TOPIC_PUB = "/chi";
char* MQTT_TOPIC_SUB = "/chun";


void mqtt_connect(char* client){
    mqttclient.connect(client);
    Serial.println("mqtt connected as \"" + String(MQTT_CLIENT_NAME)+"\"");
}

void mqtt_connect_server(char* server, uint16_t port, char* client){
    mqttclient.setServer(mqtt_server, mqtt_port);
    MQTT_CLIENT_NAME = client;
    mqtt_connect(client);
    mqtt_sub("chun");
}

void mqtt_connect_check(){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqtt_connect(MQTT_CLIENT_NAME);
    mqtt_sub(MQTT_TOPIC_SUB);
    delay(500);
  }
}

void mqtt_pub(String content, char* topic){
  mqtt_connect_check();
  mqttclient.publish(topic, content.c_str());
  Serial.println("published");
}

void mqtt_sub(char* topic) {
  MQTT_TOPIC_SUB = topic;
  mqttclient.subscribe(MQTT_TOPIC_SUB, 0);
  mqttclient.setCallback(on_msg);
}

void on_msg(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message from ");
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i<length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  digitalWrite(PIN_LIGHT_BULB, !digitalRead(PIN_LIGHT_BULB));
}

void mqtt_loop() {
  mqttclient.loop();
}

void mqtt_init() {
  mqtt_connect_server(mqtt_server, mqtt_port, MQTT_CLIENT_NAME);
  mqtt_sub(MQTT_TOPIC_SUB);
}




