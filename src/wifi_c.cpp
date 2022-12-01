#include "wifi_c.h"

// const char* wifi_ssid = "abc556";
// const char* wifi_password = "dg123456";
// const char* wifi_ssid = "唔讀書";
// const char* wifi_password = "Jsn36879!";
// const char* wifi_ssid = "trash";
// const char* wifi_password = "12345678";
// const char* wifi_ssid = "AEM_Guest";
// const char* wifi_password = "aem36285536";

void wifi_init(){
    WiFi.begin(WIFI_ST_SSID, WIFI_ST_PW);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    Serial.print("WiFi: Connecting to WiFi ");
    Serial.print(WIFI_ST_SSID);
    int count = 0;
    while(WiFi.status() != WL_CONNECTED){
        Serial.print('.');
        delay(100);
        count++;
        // if (count>20) ESP.restart();
        if (count>80) {
            Serial.println();
            break;
        }
    }
    if(WiFi.status() == WL_CONNECTED) Serial.println("connected");
}

bool wifi_stat() { // connected will return true
    return WiFi.status() == WL_CONNECTED;
}

void wifi_connect_check() {
    if (!wifi_stat()) {
        Serial.println("WiFi: Reconnecting...");
        wifi_init();
        delay(500);
    }
}
