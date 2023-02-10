#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "****";
const char* password = "****";

uint32_t count = 0;

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    digitalWrite(LED_BUILTIN, LOW);
    uint8_t wifi_attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (wifi_attempt >= 100) {
            Serial.println("Couldn't connect to WiFi. Aborting...");
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            ESP.deepSleep(0);
            return;
        }
        delay(100);
        Serial.print(".");
        wifi_attempt++;
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.printf("\nConnected at %s\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", "Hello World!");
    });
    server.begin();
}

void loop() {}