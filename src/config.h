#include <ArduinoNvs.h>

#define PIN_LIGHT_BULB 4
#define PIN_BUTTON_1 19
#define PIN_BUTTON_2 18

#define GET_VAR_NAME(var) (#var)

extern String MQTT_URL;
extern String MQTT_PORT;
extern char WIFI_ST_SSID[100];
extern char WIFI_ST_PW[100];
extern char WIFI_AP_SSID[100];
extern char WIFI_AP_PW[100];
extern char MQTT_PUB_TOPIC[100];
extern char MQTT_SUB_TOPIC[100];

void nvs_update_config();
void nvs_init();

void nvs_setstr_var(String name, String val);