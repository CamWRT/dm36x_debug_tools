/*
 * Dump DM36x PINMUX regs.
 *
 * (C) 2014 Vladimir Ermakov <vooon341@gmail.com>
 */


#include <err.h>

#include "davinci.h"


struct reg_field {
	const char *name;
	const char *fmt;
	uint32_t shift;
	uint32_t mask;
};

struct pll_reg_info {
	const char *name;
	off_t offset;
	const struct reg_field *fields;
	size_t num_fields;
};

#define REG_FMT_D01(_name, _shift, _mask)	{_name, "%01d", _shift, _mask}
#define REG_INFO(_name, offs, fields)		{_name, offs, fields, ARRAY_SIZE(fields)}

const struct reg_field reg_fields_pid[] = {
	{"TYPE", "%02X", 16, 0xff},
	{"CLASS", "%02X", 8, 0xff},
	{"REV", "%02X", 0, 0xff},
};

const struct reg_field reg_fields_ocsel[] = {
	REG_FMT_D01("OCSRC", 4, 1),
};

const struct reg_field reg_fields_oscdiv1[] = {
	REG_FMT_D01("OD1EN", 15, 1),
	REG_FMT_D01("RATIO", 0, 0x1f),
};

const struct reg_field reg_fields_cken[] = {
	REG_FMT_D01("OBSCLK", 1, 1),
	REG_FMT_D01("AUXEN", 0, 1),
};

const struct reg_field reg_fields_ckstat[] = {
	REG_FMT_D01("BPON", 3, 1),
	REG_FMT_D01("OBSON", 1, 1),
	REG_FMT_D01("AUXEN", 0, 1),
};

const struct pll_reg_info pllc_registers[] = {
	REG_INFO("PID", 0x00, reg_fields_pid),
	REG_INFO("OCSEL", 0x104, reg_fields_ocsel),
	REG_INFO("OSCDIV1", 0x124, reg_fields_oscdiv1),
	REG_INFO("CKEN", 0x148, reg_fields_cken),
	REG_INFO("CKSTAT", 0x14C, reg_fields_ckstat),
};


static void print_fields(uint32_t reg, const struct reg_field *fp, const size_t len)
{
	char buf[16];

	for (int i = 0; i < len; i++) {
		snprintf(buf, sizeof(buf), fp[i].fmt, (reg >> fp[i].shift) & fp[i].mask);
		printf("\t%s: %s\n", fp[i].name, buf);
	}
}

static void print_pllc(volatile void *pllc_mod)
{
	for (int i = 0; i < ARRAY_SIZE(pllc_registers); i++) {
		uint32_t reg = read_u32(pllc_mod + pllc_registers[i].offset);

		printf("%s: 0x%08X\n", pllc_registers[i].name, reg);
		print_fields(reg, pllc_registers[i].fields, pllc_registers[i].num_fields);
	}
}

int main(int argc, char *argv[])
{
	int fd;
	volatile void *sys_mod = mmap_perith(SYSTEM_MODULE_BASE, MMAP_SZ_SYSTEM_MODULE, &fd);

	printf("--------------------\nPLLC1:\n");
	print_pllc(sys_mod + 0x800);

	printf("--------------------\nPLLC2:\n");
	print_pllc(sys_mod + 0xC00);

	munmap_perith(sys_mod, MMAP_SZ_SYSTEM_MODULE, &fd);
	return 0;
}
