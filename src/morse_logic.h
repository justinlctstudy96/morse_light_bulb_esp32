#include <config.h>
#include <mqtt.h>
#include <ArduinoJson.h>

void morse_btns_check();
void code_btn(bool pressed);
void state_btn(bool pressed);
void morse_mqtt_pub(bool state, String content);
String vector_to_string(std::vector<std::vector<int>>& vector);