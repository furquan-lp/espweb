#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include "esp32web.h"

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_ONBOARD, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    digitalWrite(LED_PIN, HIGH);
    uint8_t wifi_attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (wifi_attempt >= 100) {
            Serial.println("Couldn't connect to WiFi. Aborting...");
            digitalWrite(LED_PIN, LOW);
            digitalWrite(LED_ONBOARD, HIGH);
            delay(1000);
            ESP.deepSleep(0);
            return;
        }
        delay(100);
        Serial.print(".");
        wifi_attempt++;
    }
    digitalWrite(LED_PIN, LOW);
    Serial.printf("\nConnected at %s\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, handle_webserver_root);
    server.begin();
}

void loop() { delay(100); }

void handle_webserver_root(AsyncWebServerRequest* request) {
    uint32_t seconds = millis() / 1000;
    const char* format_str = "Hello World!\nSeconds since boot: %d\n";
    char server_str[sizeof(format_str) + 64];
    sprintf(server_str, format_str, seconds);
    request->send(200, "text/plain", server_str);
}