#include "espweb.h"

#ifdef EW_ESP32
const char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"160MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File System)\"}";
#else
const char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"80MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File System)\"}";
char server_json_data[sizeof(server_json_template) /
                          sizeof(server_json_template[0]) +
                      128];
#endif

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
void blink_led(uint8_t led_pin, bool invert) {
    uint8_t on = invert ? LOW : HIGH;
    digitalWrite(led_pin, on);
    delay(250);
    digitalWrite(led_pin, !on);
    delay(250);
}