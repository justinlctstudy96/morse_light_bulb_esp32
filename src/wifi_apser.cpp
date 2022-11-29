#include <wifi_apser.h>

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
  <html>
  <head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
 
  </style>
  </head>
  <body>
    <h1></h1>
  </body>
  <script>

  </script>
</html>
)rawliteral";

String processor(const String& var){}

void ap_server_init() {
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html, processor);
      // request->send_P(200, "text/html", index_html);
    });
}