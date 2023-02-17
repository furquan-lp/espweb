#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <espweb.h>
#include <espweb_common.h>

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(ESP32_LED_PIN, OUTPUT);
    pinMode(ESP32_LED_ONBOARD, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    digitalWrite(ESP32_LED_PIN, HIGH);
    uint8_t wifi_attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (wifi_attempt >= 20) {
            Serial.println("Couldn't connect to WiFi. Aborting...");
            digitalWrite(ESP32_LED_PIN, LOW);
            digitalWrite(ESP32_LED_ONBOARD, HIGH);
            delay(1000);
            esp_deep_sleep_start();
            return;
        }
        blink_led(ESP32_LED_ONBOARD);
        Serial.print(".");
        wifi_attempt++;
    }
    digitalWrite(ESP32_LED_PIN, LOW);
    Serial.printf("\nConnected at %s\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, handle_webserver_root);
    server.begin();
}

void loop() { delay(100); }