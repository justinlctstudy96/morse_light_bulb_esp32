#include <config.h>

char WIFI_ST_SSID[100] = "";
char WIFI_ST_PW[100] = "";
char WIFI_AP_SSID[100] = "chi";
char WIFI_AP_PW[100] = "05270625";
char MQTT_PUB_TOPIC[100] = "chi";
char MQTT_SUB_TOPIC[100] = "chi";

void pin_init() {
    delay(10);
    // output
    pinMode(PIN_LIGHT_BULB, OUTPUT);
    digitalWrite(PIN_LIGHT_BULB, LOW);
    pinMode(PIN_LIGHT_BTN_STATE, OUTPUT);
    digitalWrite(PIN_LIGHT_BTN_STATE, LOW);
    pinMode(PIN_LIGHT_BTN_CONNECTED, OUTPUT);
    digitalWrite(PIN_LIGHT_BTN_CONNECTED, LOW);
    // input
    pinMode(PIN_BTN_MORSE, INPUT_PULLUP);
    pinMode(PIN_BTN_MODE, INPUT_PULLUP);
    pinMode(PIN_BTN_BULB, INPUT_PULLUP);
}

void nvs_update_config() {
    NVS.begin();
    sprintf(WIFI_ST_SSID, "%s", NVS.getString("WIFI_ST_SSID"));
    sprintf(WIFI_ST_PW, "%s", NVS.getString("WIFI_ST_PW"));
}

void nvs_init() {
    NVS.begin();
    nvs_update_config();
}

void nvs_setstr_var(String name, String val) {
    Serial.println(name);
    Serial.println(val);
    NVS.setString(name, val);
}

void nvs_setchar_var(char* val) {
    NVS.setString(val, String(GET_VAR_NAME(val)));
}