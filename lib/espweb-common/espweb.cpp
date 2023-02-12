#include "espweb.h"

uint32_t uptime() { return millis() / 1000; }

String processor(const String& var) {
    if (var == "SECONDS") {
        return String(uptime());
    } else {
        return "ERR!";
    }
}

void handle_webserver_root(AsyncWebServerRequest* request) {
    /*uint32_t seconds = millis() / 1000;
    const char* format_str = "Hello World!\nSeconds since boot: %d\n";
    char server_str[sizeof(format_str) + 64];
    sprintf(server_str, format_str, seconds);
    request->send(200, "text/plain", server_str);
    */
    request->send(SPIFFS, "/index.html", String(), false, processor);
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