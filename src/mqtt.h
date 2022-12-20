#ifndef _MQTT_H_
#define _MQTT_H_

#include <config.h>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <wifi_c.h>
#include <morse_logic.h>

//extern WiFiClient espClient;
//extern PubSubClient client(WiFiClient);
extern char* mqtt_server;
extern uint16_t mqtt_port;
extern String s;
extern char* MQTT_CLIENT_NAME;

extern char* MQTT_TOPIC_SERVER;

bool mqtt_connect(char* client);
void mqtt_connect_server(char* server, uint16_t port, char* client);
void mqtt_connect_check();
void wifi_mqtt_connect_check();
void mqtt_pub(String content, char* topic, boolean retained);
void mqtt_sub(char* topic);
void on_msg(char* topic, byte* payload, unsigned int length);
void mqtt_loop();
void mqtt_init();


//to be added
//mpu
extern int stibx;
extern char cver[3][2];
extern char nver[3][2];



#endif