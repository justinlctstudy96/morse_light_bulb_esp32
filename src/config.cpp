#include <config.h>

char WIFI_ST_SSID[100] = "";
char WIFI_ST_PW[100] = "";
char WIFI_AP_SSID[100] = "chi";
char WIFI_AP_PW[100] = "05270625";
char MQTT_PUB_TOPIC[100] = "chi";
char MQTT_SUB_TOPIC[100] = "chun";

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