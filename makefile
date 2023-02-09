ARDUINO_CLI	= ../arduino-cli_0.30.0_Linux_64bit/arduino-cli
BOARD_ESP32	= esp32:esp32:esp32
BOARD_ESP8266	= esp8266:esp8266:nodemcuv2
PORT_ESP32	= /dev/ttyUSB0
PORT_ESP8266	= /dev/ttyACM0

all: verify upload

clean:
	rm esp32/*.svd

verify: verify-esp32 verify-nodemcu

verify-esp32:
	${ARDUINO_CLI} compile -b ${BOARD_ESP32} esp32/esp32.ino

verify-nodemcu:
	${ARDUINO_CLI} compile -b ${BOARD_ESP8266} esp8266/esp8266.ino

upload-esp32:
	${ARDUINO_CLI} upload -v -t -b ${BOARD_ESP32} --port ${PORT_ESP32} esp32/esp32.ino

upload-nodemcu:
	${ARDUINO_CLI} upload -v -t -b ${BOARD_ESP8266} --port ${PORT_ESP8266} esp8266/esp8266.ino

upload: upload-esp32 upload-nodemcu