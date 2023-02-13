#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <espweb.h>
#include <espweb_common.h>

String ip_address = "NULL";

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    digitalWrite(LED_BUILTIN, LOW);
    uint8_t wifi_attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (wifi_attempt >= 20) {
            Serial.println("Couldn't connect to WiFi. Aborting...");
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            ESP.deepSleep(0);
            return;
        }
        blink_led(LED_BUILTIN, true);
        Serial.print(".");
        wifi_attempt++;
    }
    digitalWrite(LED_BUILTIN, HIGH);
    ip_address = WiFi.localIP().toString();
    Serial.printf("\nConnected at %s\n", ip_address.c_str());

    if (!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
    }

    server.on("/", HTTP_GET, handle_webserver_root);
    server.on("/style.css", HTTP_GET, handle_webserver_style);
    server.on("/data", HTTP_GET, handle_webserver_json);
    server.on("/app.js", HTTP_GET, handle_webserver_javascript);
    server.on("/esp8266.jpg", HTTP_GET, handle_webserver_images);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void loop() {
    update_server_json_data(ip_address.c_str(), ESP.getFreeHeap());
    delay(2000);
}