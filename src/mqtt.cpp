#include "mqtt.h"

WiFiClient espClient;
PubSubClient mqttclient(espClient);
char* mqtt_server = "codeguys-mqtt.lol";
uint16_t mqtt_port = 1883;
String s=";";
int id = 0;
char* MQTT_CLIENT_NAME = "nathalie";


bool mqtt_connect(char* client){
    mqttclient.connect(client);
    if (mqttclient.connected()) {
      Serial.println("MQTT: Connected as \"" + String(MQTT_CLIENT_NAME)+"\"");
    } else {
      Serial.println("MQTT: Connection Failure");
    }
    return mqttclient.connected();
}

void mqtt_connect_server(char* server, uint16_t port, char* client){
    mqttclient.setServer(mqtt_server, mqtt_port);
    MQTT_CLIENT_NAME = client;
    if (mqtt_connect(client)) mqtt_sub(MQTT_SUB_TOPIC);
}

void mqtt_connect_check(){
  if (!mqttclient.connected()) {
    if (!wifi_stat()) {
      Serial.println("MQTT: WiFi not connected");
      return;
    }
    Serial.println("MQTT: Broker not connected. Reconnecting ...");
    if (mqtt_connect(MQTT_CLIENT_NAME)) mqtt_sub(MQTT_SUB_TOPIC);
    delay(500);
  }
}

void wifi_mqtt_connect_check(){
  wifi_connect_check();
  mqtt_connect_check();
}

void mqtt_pub(String content, char* topic, boolean retained = false){
  wifi_mqtt_connect_check();
  if (mqttclient.publish(topic, content.c_str(), retained)) Serial.println("MQTT: Publish \"" + content + "\" to topic \"" + String(topic) + "\"");
  else Serial.println("MQTT: Publish \"" + content + "\" failed");
}

void mqtt_sub(char* topic) {
  wifi_mqtt_connect_check();
  Serial.println("MQTT: Subscribed to topic \"" + String(topic) + "\"");
  mqttclient.subscribe(topic, 0);
  mqttclient.setCallback(on_msg);
}

void on_msg(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT: Received message from \"" + String(topic) + "\": ");
  String msg;
  for (int i = 0; i<length; i++) {
    msg += (char)payload[i];
    Serial.print((char) payload[i]);
  }
  Serial.println();
  mqtt_morse_msg_render(msg);
  // digitalWrite(PIN_LIGHT_BULB, !digitalRead(PIN_LIGHT_BULB));
}

void mqtt_loop() {
  mqttclient.loop();
}

void mqtt_init() {
  mqtt_connect_server(mqtt_server, mqtt_port, MQTT_CLIENT_NAME);
  mqtt_sub(MQTT_SUB_TOPIC);
}




