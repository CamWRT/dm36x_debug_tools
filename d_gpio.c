/*
 * Dump DM36x PINMUX regs.
 *
 * (C) 2014 Vladimir Ermakov <vooon341@gmail.com>
 */


#include "davinci.h"

const char *bank_name[] = {"01", "23", "45", "6"};

struct gpio_bank {
	uint32_t dir;
	uint32_t out_data;
	uint32_t set_data;
	uint32_t clr_data;
	uint32_t in_data;
	uint32_t set_ris_trig;
	uint32_t clr_ris_trig;
	uint32_t set_fal_trig;
	uint32_t clr_fal_trig;
	uint32_t intstat;
};

void print_bytes(uint32_t val, char hi, char lo)
{
	for (int i = 31; i >= 0; i--) {
		putchar((val & (1 << i))? hi : lo);
		putchar(' ');
		if (!(i % 8)) putchar(' ');
	}
	putchar('\n');
}

int main(int argc, char *argv[])
{
	int fd;
	volatile uint32_t *gpio = mmap_perith(GPIO_BASE, MMAP_SZ_GPIO, &fd);

	volatile struct gpio_bank *bank = gpio + 0x10/4;

	for (int i = 0; i < 4; i++) {
		printf("DIR %2s: 0x%08X: ", bank_name[i], bank[i].dir);
		print_bytes(bank[i].dir, 'I', 'O');
		printf("IN  %2s: 0x%08X: ", bank_name[i], bank[i].in_data);
		print_bytes(bank[i].in_data, '1', '0');
	}

	munmap_perith(gpio, MMAP_SZ_GPIO, &fd);
	return 0;
}
