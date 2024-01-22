#include "espweb.h"

#if defined(ESP32)
const PROGMEM char server_json_template[] =
    "{\"uptime_s\":\"%d\",\"uptime_m\":\"%d\",\"uptime_h\":\"%d\",\"uptime_d\":"
    "\"%d\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"rssi\":\"%d\","
    "\"reboots\":\"%d\",\"cpu\":\"160MHz\",\"flash\":\"4MB (1MB reserved"
    " for SPI Flash File System)\",\"version\":\"0.9.6-esp32\"}";
bool invert_led = false;
#else
const PROGMEM char server_json_template[] =
    "{\"uptime_s\":\"%d\",\"uptime_m\":\"%d\",\"uptime_h\":\"%d\",\"uptime_d\":"
    "\"%d\",\"ipaddr\":\"%s\",\"free_heap\":\"%d\",\"rssi\":\"%d\","
    "\"reboots\":\"%d\",\"cpu\":\"80MHz\",\"flash\":\"4MB (1MB reserved for"    " SPI Flash File System)\",\"version\":\"0.9.6-nodemcu\"}";
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
                      170];

/**
 * Returns an array of unsigned 32 bit integers containing the uptime in
 * increasing order of magnitude (i.e. seconds, minutes, etc.).
 * @return uint32_t* {seconds, minutes, hours, days}; must be freed after use
 */
uint32_t* get_uptime() {
    uint32_t* uptime = (uint32_t*)malloc(sizeof(uint32_t) * 4);
    uint32_t seconds = millis() / 1000;
    uptime[3] = seconds / (60 * 60 * 24);
    uptime[2] = seconds % (60 * 60 * 24) / (60 * 60);
    uptime[1] = ((seconds % (60 * 60 * 24)) % (60 * 60)) / 60;
    seconds -=
        (uptime[3] * 60 * 60 * 24) + (uptime[2] * 60 * 60) + (uptime[1] * 60);
    uptime[0] = seconds;
    /*char* buf = (char*)malloc(sizeof(*buf) * 20);
    snprintf(buf, 20, "%d:%d:%d", hours, minutes, seconds);
    return buf;*/
    return uptime;
}

/*
 * Reads the first two bytes of serverdata.bin and assembles a 16 bit
 * integer from them which is then returned as the number of reboots value.
 */
uint16_t get_fs_reboots() {
    File serverdat = SPIFFS.open("/serverdata.bin", "r");
    if (!serverdat) {
        serverdat.close();
        return -1;
    } else {
        uint8_t b1 = serverdat.read();
        uint8_t b2 = serverdat.read();
        serverdat.close();
        uint16_t val = (b1 << 8) + b2;
        /*char* converted;
        long val = strtol(dat, &converted, 10);*/
        return val;
    }
}

/*
 * Increments the value from get_fs_reboots and then writes it as two bytes
 * to serverdata.
 */
void increment_fs_reboots() {
    uint16_t totalreboots = get_fs_reboots();
    if (totalreboots == -1) {
        return;
    }
    uint16_t inc = totalreboots + 1;
    uint8_t bytes[2] = { (inc >> 8) & 0xFF, inc & 0xFF };

    File serverdat = SPIFFS.open("/serverdata.bin", "w");
    if (!serverdat) {
        serverdat.close();
        return;
    }
    serverdat.write(bytes, sizeof(bytes));
    serverdat.close();
}

void log_request(AsyncWebServerRequest* request, const char* file) {
    if (!LOGGING) return;
    const char* methods[] = {"NOP",         "HTTP_GET",    "HTTP_POST",
                             "HTTP_DELETE", "HTTP_PUT",    "HTTP_PATCH",
                             "HTTP_HEAD",   "HTTP_OPTIONS"};
    const int request_method = (int)request->method();
    if (request_method > sizeof(methods) / sizeof(methods[0])) {
        Serial.printf("Error: request->method() out of bounds for methods.");
    } else {
        Serial.printf("%s on %s%s\n", methods[request_method], request->url(),
                      file);
    }
}

void handle_webserver_root(AsyncWebServerRequest* request) {
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
    request->send(SPIFFS, "/script.js", "text/javascript");
    log_request(request, "script.js");
    toggle_led(server_led_pin);
}

void handle_webserver_images(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/esp8266.jpg", "image/jpeg");
    log_request(request, "esp8266.jpg");
    toggle_led(server_led_pin);
}

void handle_webserver_videos(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(SPIFFS, "/espvideo.webm", "video/webm");
    log_request(request, "espvideo.webm");
    toggle_led(server_led_pin);
}

void handle_webserver_json(AsyncWebServerRequest* request) {
    toggle_led(server_led_pin);
    request->send(200, "application/json", server_json_data);
    log_request(request, server_json_data);
    toggle_led(server_led_pin);
}

void update_server_json_data(const char* ipaddr, uint32_t free_heap,
                             int32_t wifi_rssi) {
    uint32_t* up = get_uptime();
    uint16_t reboots = get_fs_reboots();
    snprintf(server_json_data,
             sizeof(server_json_data) / sizeof(server_json_data[0]),
             server_json_template, up[0], up[1], up[2], up[3], ipaddr,
             free_heap, wifi_rssi, reboots);
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
