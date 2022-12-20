#include <ArduinoNvs.h>

#define PIN_LIGHT_BULB 4
#define PIN_BTN_MORSE 19 // morse_btn
#define PIN_BTN_MODE 18 // morse_mode
#define PIN_BTN_BULB 21 // bulb_on_off
#define PIN_LIGHT_BTN_STATE 23 // indicating morse mode on/off
#define PIN_LIGHT_BTN_CONNECTED 22 // indicating mqtt connected?

#define GET_VAR_NAME(var) (#var)

extern String MQTT_URL;
extern String MQTT_PORT;
extern char WIFI_ST_SSID[100];
extern char WIFI_ST_PW[100];
extern char WIFI_AP_SSID[100];
extern char WIFI_AP_PW[100];
extern char MQTT_PUB_TOPIC[100];
extern char MQTT_SUB_TOPIC[100];
extern int MORSE_RECORD_TIMEOUT;

void pin_init();
void nvs_update_config();
void nvs_init();

void nvs_setstr_var(String name, String val);