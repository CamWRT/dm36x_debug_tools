
TOOLCHAIN?=/opt/codesourcery/arm-2013.05/bin

PATH:=$(PATH):$(TOOLCHAIN)

CROSS_COMPILE?=arm-none-linux-gnueabi-

CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++

CFLAGS:=-std=c99 -I. -O2 -fmerge-constants

all: d_pinmux d_gpio d_pll


d_pinmux: d_pinmux.c

d_gpio: d_gpio.c

d_pll: d_pll.c


clean:
	rm -f d_pinmux d_gpio d_pll
