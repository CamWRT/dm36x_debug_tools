/*
 * Dump DM36x PINMUX regs.
 *
 * (C) 2014 Vladimir Ermakov <vooon341@gmail.com>
 */


#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <err.h>

// from mach-davinchi hardware.h
#define IO_OFFSET	0//0xfd000000
#define IO_ADDR(addr)	((addr) + IO_OFFSET)

#define DAVINCI_SYSTEM_MODULE_BASE        0x01C40000

// from datasheet
#define PINMUX0		IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE + 0x00)
#define PINMUX1		IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE + 0x04)
#define PINMUX2		IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE + 0x08)
#define PINMUX3		IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE + 0x0c)
#define PINMUX4		IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE + 0x10)

#define MMAP_SIZE	(IO_ADDR(0x01C4FFFF) - DAVINCI_SYSTEM_MODULE_BASE)

struct reg_info {
	char *name;
	uint32_t shift;
	uint32_t mask;
};

const struct reg_info mux_info_pinmux0[] = {
	{"MMC/SD0", 24, 1},
	{"GIO49", 23, 1},
	{"GIO48", 22, 1},
	{"GIO47", 21, 1},
	{"GIO46", 20, 1},
	{"GIO45", 19, 1},
	{"GIO44", 18, 1},
	{"GIO43", 16, 3},
	{"C_WE_FIELD", 14, 3},
	{"VD", 13, 1},
	{"HD", 12, 1},
	{"YIN0", 11, 1},
	{"YIN1", 10, 1},
	{"YIN2", 9, 1},
	{"YIN3", 8, 1},
	{"YIN4", 6, 3},
	{"YIN5", 4, 3},
	{"YIN6", 2, 3},
	{"YIN7", 0, 3},
	{NULL}
};

const struct reg_info mux_info_pinmux1[] = {
	{"VCLK", 22, 1},
	{"EXTCLK", 20, 3},
	{"FIELD", 18, 3},
	{"LCD_OE", 17, 1},
	{"HVSYNC", 16, 1},
	{"COUT0", 14, 3},
	{"COUT1", 12, 3},
	{"COUT2", 10, 3},
	{"COUT3", 8, 3},
	{"COUT4", 6, 3},
	{"COUT5", 4, 3},
	{"COUT6", 2, 3},
	{"COUT7", 0, 3},
	{NULL}
};

const struct reg_info mux_info_pinmux2[] = {
	{"EM_CLK", 12, 1},
	{"EM_ADV", 11, 1},
	{"EM_WAIT", 10, 1},
	{"EM_WE_OE", 9, 1},
	{"!EM_CE1", 8, 1},
	{"!EM_CE0", 7, 1},
	{"EM_D15_8", 6, 1},
	{"EM_A7", 4, 3},
	{"EM_A3", 2, 3},
	{"EM_AR", 0, 3},
	{NULL}
};

const struct reg_info mux_info_pinmux3[] = {
	{"GIO26", 31, 1},
	{"GIO25", 29, 3},
	{"GIO24", 28, 1},
	{"GIO23", 26, 3},
	{"GIO22", 25, 1},
	{"GIO21", 23, 3},
	{"GIO20", 21, 3},
	{"GIO19", 20, 1},
	{"GIO18", 19, 1},
	{"GIO17", 17, 3},
	{"GIO16", 15, 3},
	{"GIO15", 14, 1},
	{"GIO14", 13, 1},
	{"GIO13", 12, 1},
	{"GIO12", 11, 1},
	{"GIO11", 10, 1},
	{"GIO10", 9, 1},
	{"GIO9", 8, 1},
	{"GIO8", 7, 1},
	{"GIO7", 6, 1},
	{"GIO6", 5, 1},
	{"GIO5", 4, 1},
	{"GIO4", 3, 1},
	{"GIO3", 2, 1},
	{"GIO2", 1, 1},
	{"GIO1", 0, 1},
	{NULL}
};

const struct reg_info mux_info_pinmux4[] = {
	{"GIO42", 30, 3},
	{"GIO41", 28, 3},
	{"GIO40", 26, 3},
	{"GIO39", 24, 3},
	{"GIO38", 22, 3},
	{"GIO37", 20, 3},
	{"GIO36", 18, 3},
	{"GIO35", 16, 3},
	{"GIO34", 14, 3},
	{"GIO33", 12, 3},
	{"GIO32", 10, 3},
	{"GIO31", 8, 3},
	{"GIO30", 6, 3},
	{"GIO29", 4, 3},
	{"GIO28", 2, 3},
	{"GIO27", 0, 3},
	{NULL}
};

const struct reg_info *mux_info_table[] = {
	mux_info_pinmux0,
	mux_info_pinmux1,
	mux_info_pinmux2,
	mux_info_pinmux3,
	mux_info_pinmux4,
};


int main(int argc, char *argv[])
{
	volatile uint32_t *map = NULL;

	int fd = open("/dev/mem", O_RDWR);
	if (fd < 0)
		err(1, "open /dev/mem:");

	map = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PINMUX0);
	if (map == MAP_FAILED)
		err(1, "mmap:");

	uint32_t device_id = map[10];

	printf("DEVICE_ID: 0x%08X\n", device_id);
	printf(
			"\tDEVREV: %01X\n"
			"\tPARTNUM: %04X\n"
			"\tMFGR: %03X\n",
			(device_id >> 28),
			(device_id >> 12) & 0xffff,
			(device_id >> 1) & 0x7ff);

	for (int i = 0; i < 4; i++) {
		printf("PINMUX%d: 0x%08X\n", i, map[i]);
		for (const struct reg_info *p = mux_info_table[i]; p->name != NULL; p++)
			printf("\t%s: %02X\n", p->name, (map[i] >> p->shift) & p->mask);
	}

	munmap(map, MMAP_SIZE);
	close(fd);
	return 0;
}
