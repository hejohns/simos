CXX := avr-gcc
mmcu := atmega2560
F_CPU := 16000000UL
ARDUINO := 105
USB_PID := null
CXXFLAGS := -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(mmcu) -DF_CPU=$(F_CPU) -MMD -DUSB_VID=$(USB_PID) -DUSB_PID=$(USB_PID) -DARDUINO=$(ARDUINO) -D__PROG_TYPES_COMPAT__

export CPATH := .:

default:

test: 

main.o: main.c
	$(CXX) $(CXXFLAGS) $< -o $@

uart.o: uart.c uart.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean: rm *.o *.d
