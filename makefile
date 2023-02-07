ARDUINO_CLI	= ../arduino-cli_0.29.0_Linux_64bit/arduino-cli
BOARD_ESP32	= esp32:esp32:esp32
PORT_ESP32	= /dev/ttyUSB0

all: verify upload

clean:
	rm esp32/*.svd

verify:
	${ARDUINO_CLI} compile -b ${BOARD_ESP32} esp32/esp32.ino

upload:
	${ARDUINO_CLI} upload -v -b ${BOARD_ESP32} --port ${PORT_ESP32} esp32/esp32.ino