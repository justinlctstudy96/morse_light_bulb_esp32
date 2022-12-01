#include <wifi_apser.h>

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <title>ChiChun Light Bulb</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>

    </style>
</head>

<body>
    <h1>ChiChun Light Bulb</h1>
    <div id="current-st-config">
        <div>Current WiFi Station Configuration: </div>
        <div>SSID: %CURRENTSTSSID%</div>
        <div>PW: %CURRENTSTPW%</div>
    </div>
    <form action="/wifi_st_config" target="hidden-form">
        WiFi Station Update:
        <br> <input type="text" name="input_st_ssid" placeholder="SSID">
        <br> <input type="text" name="input_st_pw" placeholder="Password">
        <input type="submit" value="submit">
    </form>
</body>
<script></script>

</html>
)rawliteral";

String processor(const String& var){
    if (var == "CURRENTSTSSID") return WIFI_ST_SSID;
    if (var == "CURRENTSTPW") return WIFI_ST_PW;
}
void notFound(AsyncWebServerRequest *request) {request->send(404, "text/plain", "Not found");}


void ap_server_init() {
    Serial.print("Initizlizing AP server ");
    Serial.println(WIFI_AP_SSID);
    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PW);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
    });
    server.on("/wifi_st_config", HTTP_GET, [](AsyncWebServerRequest *request) {
        String temp_st_ssid = request->getParam("input_st_ssid")->value();
        String temp_st_pw = request->getParam("input_st_pw")->value();
        nvs_setstr_var("WIFI_ST_SSID", temp_st_ssid);
        nvs_setstr_var("WIFI_ST_PW", temp_st_pw);
        nvs_update_config();
        wifi_init();
        request->send_P(200, "text/html", index_html, processor);
        // request->send(200, "text/text", "WiFi station config successfully updated");
    });
    server.onNotFound(notFound);
    server.begin();
}