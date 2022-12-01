#include "wifi_c.h"
#include "mqtt.h"
#include "http.h"
#include "config.h"
#include "wifi_apser.h"
#include "morse_logic.h"

u_int p_time = 0;

void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
  delay(100);
  while(!Serial) {}
  Serial.println("Serial Begin.");

  delay(10);
  pinMode(PIN_LIGHT_BULB, OUTPUT);
  digitalWrite(PIN_LIGHT_BULB, LOW);
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

  // non-volatiled storage init
  nvs_init();

  // wifi ap server init
  ap_server_init();

  //wifi init
  wifi_init();

  //mqtt init
  mqtt_init();
}

void loop() {
  // mqtt_loop();
  morse_btns_check();
  if(millis() - p_time >= 5000) {
    p_time = millis();
  // Serial.println("-----------------------" + String(millis()) + "-----------------------");
    wifi_mqtt_connect_check();
  // JSON_decode("s");
    // mqtt_pub("eofijasf", MQTT_PUB_TOPIC, false);
  }

}
