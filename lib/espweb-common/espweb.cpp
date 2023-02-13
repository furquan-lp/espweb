#include "espweb.h"

#if defined(ESP32)
const PROGMEM char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"160MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File "
    "System)\",\"version\":\"0.8.0\"}";
bool invert_led = false;
#else
const PROGMEM char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"80MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File "
    "System)\",\"version\":\"0.8.0\"}";
bool invert_led = true;
#endif
char server_json_data[sizeof(server_json_template) /
                          sizeof(server_json_template[0]) +
                      128];

char* get_uptime() {
    uint32_t seconds = millis() / 1000;
    uint32_t hours = seconds / (60 * 60);
    uint32_t minutes = (seconds - (hours * 60 * 60)) / 60;
    seconds -= minutes * 60 + hours * (60 * 60);
    char* buf = (char*)malloc(sizeof(*buf) * 20);
    snprintf(buf, 20, "%d:%d:%d", hours, minutes, seconds);
    return buf;
}

void handle_webserver_root(AsyncWebServerRequest* request) {
    /*uint32_t seconds = millis() / 1000;
    const char* format_str = "Hello World!\nSeconds since boot: %d\n";
    char server_str[sizeof(format_str) + 64];
    sprintf(server_str, format_str, seconds);
    request->send(200, "text/plain", server_str);
    */
    request->send(SPIFFS, "/index.html", "text/html");
}

void handle_webserver_style(AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/style.css", "text/css");
}

void handle_webserver_javascript(AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/app.js", "text/javascript");
}

void handle_webserver_images(AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/esp8266.jpg", "image/jpeg");
}

void handle_webserver_json(AsyncWebServerRequest* request) {
    request->send(200, "application/json", server_json_data);
}

void update_server_json_data(const char* ipaddr, uint32_t free_heap) {
    char* up = get_uptime();
    snprintf(server_json_data,
             sizeof(server_json_data) / sizeof(server_json_data[0]),
             server_json_template, up, ipaddr, free_heap);
    free(up);
}

/**
 * Blinks the LED on (LOW or HIGH depending on whether invert is true) for 250ms
 * and off for 250ms.
 */
void blink_led(uint8_t led_pin) {
    uint8_t on = invert_led ? LOW : HIGH;
    digitalWrite(led_pin, on);
    delay(250);
    digitalWrite(led_pin, !on);
    delay(250);
}