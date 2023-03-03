#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <espweb.h>
#include <espweb_common.h>

String ip_address = "NULL";
uint8_t loop_counter_0 = 0;

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.print("Connecting to WiFi");
    digitalWrite(LED_BUILTIN, LOW);
    WiFi.persistent(false);
    if (!init_WiFi()) {
        Serial.println("Couldn't connect to WiFi. Aborting...");
        return;
    }
    digitalWrite(LED_BUILTIN, HIGH);
    ip_address = WiFi.localIP().toString();
    Serial.printf("\nConnected at %s\n", ip_address.c_str());

    if (!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
    }

    if (MDNS.begin(esp8266_mdns_url)) {
        Serial.printf("mDNS server started at http://%s.local/\n",
                      esp8266_mdns_url);
    }

    server.on("/", HTTP_GET, handle_webserver_root);
    server.on("/style.css", HTTP_GET, handle_webserver_style);
    server.on("/about.html", HTTP_GET, handle_webserver_about);
    server.on("/data", HTTP_GET, handle_webserver_json);
    server.on("/script.js", HTTP_GET, handle_webserver_javascript);
    server.on("/esp8266.jpg", HTTP_GET, handle_webserver_images);
    server.on("/espvideo.webm", HTTP_GET, handle_webserver_videos);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void loop() {
    if (loop_counter_0 >= 20 && !WiFi.isConnected()) {
        Serial.println(
            "WiFi is disconnected. Attempting to reestablish connection");
        WiFi.disconnect();
        if (!init_WiFi()) return;
    }
    MDNS.update();
    update_server_json_data(ip_address.c_str(), ESP.getFreeHeap(), WiFi.RSSI());
    delay(2000);
    loop_counter_0 = loop_counter_0 >= 20 ? 0 : loop_counter_0 + 1;
}

bool init_WiFi() {
    WiFi.begin(ssid, password);
    uint8_t wifi_attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (wifi_attempt >= 50) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            return false;
        }
        blink_led(LED_BUILTIN);
        Serial.print(".");
        wifi_attempt++;
    }
    WiFi.setAutoReconnect(true);
    return true;
}