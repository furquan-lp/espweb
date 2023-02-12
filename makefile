ARDUINO_CLI	= ../arduino-cli_0.30.0_Linux_64bit/arduino-cli
ESPTOOL	= esptool
SPIFFS_TOOL	= python spiffsgen.py
SPIFFS_TOOL_FLAGS	= --page-size 256 --block-size 8192 --no-magic-len --aligned-obj-ix-tables --meta-len=0 0xFA000
SPIFFS_BEGIN_ESP8266	= 0x300000
BOARD_ESP32	= esp32:esp32:esp32
BOARD_ESP8266	= esp8266:esp8266:nodemcuv2:eesz=4M1M
PORT_ESP32	= /dev/ttyUSB0
PORT_ESP8266	= /dev/ttyACM0
SOURCE_ESP32	= src/esp32
SOURCE_ESP8266	= src/esp8266
SOURCE_LIBRARIES	= lib
SOURCE_SPIFFS	= src/web
BUILD_ESP8266	= esp8266-build/esp8266.ino.bin
BUILD_SPIFFS	= spiffs.bin

all: verify upload

clean:
	rm esp32/*.svd

verify: verify-esp32 verify-nodemcu

verify-esp32:
	${ARDUINO_CLI} compile --warnings all --libraries ${SOURCE_LIBRARIES} -b ${BOARD_ESP32} ${SOURCE_ESP32}/esp32.ino

verify-nodemcu:
	${ARDUINO_CLI} compile --warnings all --libraries ${SOURCE_LIBRARIES} -b ${BOARD_ESP8266} ${SOURCE_ESP8266}/esp8266.ino --build-path esp8266-build

upload-esp32:
	${ARDUINO_CLI} upload -v -t -b ${BOARD_ESP32} --port ${PORT_ESP32} ${SOURCE_ESP32}/esp32.ino

upload-nodemcu:
	${SPIFFS_TOOL} ${SPIFFS_TOOL_FLAGS} ${SOURCE_SPIFFS} ${BUILD_SPIFFS}
	${ESPTOOL} --chip esp8266 --port ${PORT_ESP8266} --baud 115200 --before default_reset --after hard_reset write_flash 0x0 ${BUILD_ESP8266} ${SPIFFS_BEGIN_ESP8266} ${BUILD_SPIFFS}
#	${ARDUINO_CLI} upload -v -t -b ${BOARD_ESP8266} --port ${PORT_ESP8266} ${SOURCE_ESP8266}/esp8266.ino

upload: upload-esp32 upload-nodemcu