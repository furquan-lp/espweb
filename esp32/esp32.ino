#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#define LED_PIN 13
#define LED_ONBOARD 2

const char* ssid = "****";
const char* password = "****";

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_ONBOARD, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    digitalWrite(LED_PIN, HIGH);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    digitalWrite(LED_PIN, LOW);
    Serial.printf("\nConnected at %s\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", "Hello World!");
    });
    server.begin();
}

void loop() {}
