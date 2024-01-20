#ifndef ESP_WEB_COMMON_H
#define ESP_WEB_COMMON_H

#include <ESPAsyncWebServer.h>

#define ESP32_LED_PIN 13
#define ESP32_LED_ONBOARD 2

const char* ssid = "****";
const char* password = "****";

const char* esp8266_mdns_url = "esp8266web";
const char* esp32_mdns_url = "esp32web";

AsyncWebServer server(80);

#endif