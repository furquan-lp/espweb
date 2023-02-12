#ifndef ESP_WEB_H
#define ESP_WEB_H

#include <ESPAsyncWebServer.h>

void handle_webserver_root(AsyncWebServerRequest* request);
void handle_webserver_style(AsyncWebServerRequest* request);
void blink_led(uint8_t led_pin, bool invert);

#endif