#ifndef DAVINCI_H
#define DAVINCI_H

// from mach-davinci hardware.h
#define IO_OFFSET	0	// 0xfd000000
#define IO_ADDR(addr)	((addr) + IO_OFFSET)

#define DAVINCI_SYSTEM_MODULE_BASE	0x01C40000
#define DAVINCI_GPIO_BASE		0x01C67000
#define DAVINCI_PLLC1_BASE		0x01C40800
#define DAVINCI_PLLC2_BASE		0x01C40C00

// from datasheet
#define SYSTEM_MODULE_BASE	IO_ADDR(DAVINCI_SYSTEM_MODULE_BASE)
#define GPIO_BASE		IO_ADDR(DAVINCI_GPIO_BASE)
#define PLLC1_BASE		IO_ADDR(DAVINCI_PLLC1_BASE)
#define PLLC2_BASE		IO_ADDR(DAVINCI_PLLC2_BASE)

#define MMAP_SZ_SYSTEM_MODULE	(0x01C4FFFF - DAVINCI_SYSTEM_MODULE_BASE)
#define MMAP_SZ_GPIO		(0x01C67FFF - DAVINCI_GPIO_BASE)
#define MMAP_SZ_PLLC		(0x01C40BFF - DAVINCI_PLLC1_BASE)


#define ARRAY_SIZE(arr)		(sizeof(arr)/sizeof(arr[0]))

/* MMAP helper */

#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


static inline volatile void *mmap_perith(off_t addr, size_t size, int *fd)
{
	volatile void *mem;

	*fd = open("/dev/mem", O_RDWR);
	if (*fd < 0)
		err(1, "open /dev/mem:");

	mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, addr);
	if (mem == MAP_FAILED)
		err(1, "mmap:");

	return mem;
}

static inline void munmap_perith(volatile void *mem, size_t size, int *fd)
{
	munmap(mem, size);
	close(*fd); *fd = -1;
}

static inline uint32_t read_u32(volatile void *reg)
{
	return *((uint32_t*)reg);
}

#endif /* DAVINCI_H */
