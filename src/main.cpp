#include "wifi_c.h"
#include "mqtt.h"
#include "http.h"
#include "config.h"

u_int p_time = 0;

void wifi_mqtt_connect_check(){
  wifi_connect_check();
  mqtt_connect_check();
}

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(PIN_LIGHT_BULB, OUTPUT);
  digitalWrite(PIN_LIGHT_BULB, LOW);
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

  Serial.println("Serial Begin.");

  //wifi init
  wifi_init();
  Serial.println("Wifi Inited.");

  //mqtt init
  mqtt_init();
  Serial.println("MQTT Inited.");

  // String temp = "trashh";
  NVS.begin();
  nvs_setstr_var(GET_VAR_NAME(WIFI_ST_SSID), "trashh");
  nvs_get_config();
  Serial.print("ssid: ");
  Serial.println(WIFI_ST_SSID);
}

void loop() {
  mqtt_loop();
  if (digitalRead(PIN_BUTTON_1) == 0) {
    Serial.println("1pushed");
  }
  if (digitalRead(PIN_BUTTON_2) == 0) {
    Serial.println("2pushed");
  }
  // Serial.println(digitalRead(PIN_BUTTON_1));
  if(millis() - p_time >= 5000) {
    // p_time = millis();
    // Serial.println("-----------------------" + String(millis()) + "-----------------------");
  //   // mqtt_pub("{\"1\":\"\",\"2\":\"\",\"3\":\"{\"name\": \"Countdown14\", \"size\":3}\",\"4\":\"{\"name\": \"Viewco\", \"size\":1}\"");
    // mqtt_pub("natnat", "chi");
    wifi_mqtt_connect_check();
    // JSON_decode("s");
  }

  //nfc
  // nfc_loop();
  // mqtt_pub(nfc_reading_combine());
}
