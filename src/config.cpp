#include <config.h>

char WIFI_ST_SSID[100] = "";
char WIFI_ST_PW[100] = "";

void nvs_get_config() {
    NVS.begin();
    sprintf(WIFI_ST_SSID, "%s", NVS.getString("WIFI_ST_SSID"));
    sprintf(WIFI_ST_PW, "%s", NVS.getString("WIFI_ST_PW"));
}

void nvs_setstr_var(String name, String val) {
    Serial.println(name);
    Serial.println(val);
    NVS.setString(name, val);
}

void nvs_setchar_var(char* val) {
    NVS.setString(val, String(GET_VAR_NAME(val)));
}