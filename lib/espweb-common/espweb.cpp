#include "espweb.h"

#if defined(ESP32)
const PROGMEM char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"160MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File "
    "System)\",\"version\":\"0.8.4\"}";
bool invert_led = false;
#else
const PROGMEM char server_json_template[] =
    "{\"uptime\":\"%s\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"cpu\":"
    "\"80MHz\",\"flash\":\"4MB (1MB reserved for SPI Flash File "
    "System)\",\"version\":\"0.8.4\"}";
bool invert_led = true;
#endif
bool led_toggled = false;
// TODO: This may introduce a bug if ESP32_LED_ONBOARD is not defined as
// espweb.h may be imported before it is defined
#if defined(ESP32)
uint8_t server_led_pin = ESP32_LED_ONBOARD;
#else
uint8_t server_led_pin = LED_BUILTIN;
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

void log_request(AsyncWebServerRequest* request, const char* file) {
    if (!LOGGING) return;
    const char* methods[] = {"NOP",         "HTTP_GET",    "HTTP_POST",
                             "HTTP_DELETE", "HTTP_PUT",    "HTTP_PATCH",
                             "HTTP_HEAD",   "HTTP_OPTIONS"};
    Serial.printf("%s on %s%s\n", methods[request->method()], request->url(),
                  file);
}

void handle_webserver_root(AsyncWebServerRequest* request) {
    /*uint32_t seconds = millis() / 1000;
    const char* format_str = "Hello World!\nSeconds since boot: %d\n";
    char server_str[sizeof(format_str) + 64];
    sprintf(server_str, format_str, seconds);
    request->send(200, "text/plain", server_str);
    */
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/index.html", "text/html");
    log_request(request, "index.html");
    toggle_led(server_led_pin);
}

void handle_webserver_about(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/about.html", "text/html");
    log_request(request, "about.html");
    toggle_led(server_led_pin);
}

void handle_webserver_style(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/style.css", "text/css");
    log_request(request, "style.css");
    toggle_led(server_led_pin);
}

void handle_webserver_javascript(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/app.js", "text/javascript");
    log_request(request, "app.js");
    toggle_led(server_led_pin);
}

void handle_webserver_images(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/esp8266.jpg", "image/jpeg");
    log_request(request, "esp8266.jpg");
    toggle_led(server_led_pin);
}

void handle_webserver_json(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(200, "application/json", server_json_data);
    log_request(request, server_json_data);
    toggle_led(server_led_pin);
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

/**
 * Toggles the LED on or off
 */
void toggle_led(uint8_t led_pin) {
    uint8_t on = invert_led ? LOW : HIGH;
    if (led_toggled) {
        digitalWrite(led_pin, !on);
        led_toggled = false;
    } else {
        digitalWrite(led_pin, on);
        led_toggled = true;
    }
}