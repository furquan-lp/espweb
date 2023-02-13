#ifndef ESP_WEB_H
#define ESP_WEB_H

#include <ESPAsyncWebServer.h>

void handle_webserver_root(AsyncWebServerRequest* request);
void handle_webserver_style(AsyncWebServerRequest* request);
void handle_webserver_javascript(AsyncWebServerRequest* request);
void handle_webserver_images(AsyncWebServerRequest* request);
void handle_webserver_json(AsyncWebServerRequest* request);
void update_server_json_data(const char* ipaddr, uint32_t free_heap);
void blink_led(uint8_t led_pin);

#endif