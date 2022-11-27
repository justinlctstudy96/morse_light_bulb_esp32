#include "wifi_c.h"

// const char* wifi_ssid = "abc556";
// const char* wifi_password = "dg123456";
// const char* wifi_ssid = "唔讀書";
// const char* wifi_password = "Jsn36879!";
const char* wifi_ssid = "trash";
const char* wifi_password = "12345678";
// const char* wifi_ssid = "AEM_Guest";
// const char* wifi_password = "aem36285536";

void wifi_init(){
    WiFi.begin(wifi_ssid, wifi_password);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    Serial.print("connecting to WiFi ");
    while(WiFi.status() != WL_CONNECTED){
    // while (WiFi.localIP().toString() == "0.0.0.0") {
    // while (!WiFi.localIP().isSet()) {
        Serial.print('.');
        delay(100);
    }
}

bool wifi_stat() // connected will return true
{
    if (WiFi.status() == WL_CONNECTED) return true;
    return false;
}

void wifi_connect_check() {
    if (!wifi_stat()) {
        Serial.println("wifi not connected, reconnecting...");
        wifi_init();
        delay(500);
    }
}
