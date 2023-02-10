#ifndef ESP_WEB_COMMON_H
#define ESP_WEB_COMMON_H

#include <ESPAsyncWebServer.h>

#define ESP32_LED_PIN 13
#define ESP32_LED_ONBOARD 2

const char* ssid = "****";
const char* password = "****";

AsyncWebServer server(80);

#endif