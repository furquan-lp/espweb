#include "espweb.h"

uint32_t uptime_seconds() { return millis() / 1000; }

const char* server_json_template =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\"}";
char server_json_data[sizeof(server_json_template) /
                          sizeof(server_json_template[0]) +
                      128];

const char* get_uptime() {
    uint32_t seconds = millis() / 1000;
    uint32_t hours = seconds / (60 * 60);
    uint32_t minutes = (seconds - (hours * 60 * 60)) / 60;
    seconds -= minutes * 60 + hours * (60 * 60);
    char buf[20];
    snprintf(buf, (sizeof(buf) / sizeof(buf[0])), "%d:%d:%d", hours, minutes,
             seconds);
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

void update_server_json_data(const char* ipaddr, uint32_t free_heap) {
    snprintf(server_json_data,
             sizeof(server_json_data) / sizeof(server_json_data[0]),
             server_json_template, get_uptime(), ipaddr, free_heap);
}

/**
 * Blinks the LED on (LOW or HIGH depending on whether invert is true) for 250ms
 * and off for 250ms.
 */
void blink_led(uint8_t led_pin, bool invert) {
    uint8_t on = invert ? LOW : HIGH;
    digitalWrite(led_pin, on);
    delay(250);
    digitalWrite(led_pin, !on);
    delay(250);
}