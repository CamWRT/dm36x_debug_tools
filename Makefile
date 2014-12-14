
TOOLCHAIN?=/opt/codesourcery/arm-2013.05/bin

PATH:=$(PATH):$(TOOLCHAIN)

CROSS_COMPILE?=arm-none-linux-gnueabi-

CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++

CFLAGS:=-std=c99 -I.

all: d_pinmux d_gpio


d_pinmux: d_pinmux.c

d_gpio: d_gpio.c


clean:
	rm -f d_pinmux d_gpio
