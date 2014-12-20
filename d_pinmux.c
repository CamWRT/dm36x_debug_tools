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

struct sys_reg_info {
	const char *name;
	off_t sys_mod_offset;
	const struct reg_field *fields;
	size_t num_fields;
};

#define REG_MUX(_name, _shift, _mask)	{_name, "%01d", _shift, _mask}
#define REG_INFO(_name, offs, fields)	{_name, offs, fields, ARRAY_SIZE(fields)}

const struct reg_field reg_fields_device_id[] = {
	{"DEVREV", "%01X", 28, 0xff},
	{"PARTNUM", "%04X", 12, 0xffff},
	{"MFGR", "%03X", 1, 0x7ff},
};

const struct reg_field reg_fields_pinmux0[] = {
	REG_MUX("MMC/SD0", 24, 1),
	REG_MUX("GIO49", 23, 1),
	REG_MUX("GIO48", 22, 1),
	REG_MUX("GIO47", 21, 1),
	REG_MUX("GIO46", 20, 1),
	REG_MUX("GIO45", 19, 1),
	REG_MUX("GIO44", 18, 1),
	REG_MUX("GIO43", 16, 3),
	REG_MUX("C_WE_FIELD", 14, 3),
	REG_MUX("VD", 13, 1),
	REG_MUX("HD", 12, 1),
	REG_MUX("YIN0", 11, 1),
	REG_MUX("YIN1", 10, 1),
	REG_MUX("YIN2", 9, 1),
	REG_MUX("YIN3", 8, 1),
	REG_MUX("YIN4", 6, 3),
	REG_MUX("YIN5", 4, 3),
	REG_MUX("YIN6", 2, 3),
	REG_MUX("YIN7", 0, 3),
};

const struct reg_field reg_fields_pinmux1[] = {
	REG_MUX("VCLK", 22, 1),
	REG_MUX("EXTCLK", 20, 3),
	REG_MUX("FIELD", 18, 3),
	REG_MUX("LCD_OE", 17, 1),
	REG_MUX("HVSYNC", 16, 1),
	REG_MUX("COUT0", 14, 3),
	REG_MUX("COUT1", 12, 3),
	REG_MUX("COUT2", 10, 3),
	REG_MUX("COUT3", 8, 3),
	REG_MUX("COUT4", 6, 3),
	REG_MUX("COUT5", 4, 3),
	REG_MUX("COUT6", 2, 3),
	REG_MUX("COUT7", 0, 3),
};

const struct reg_field reg_fields_pinmux2[] = {
	REG_MUX("EM_CLK", 12, 1),
	REG_MUX("EM_ADV", 11, 1),
	REG_MUX("EM_WAIT", 10, 1),
	REG_MUX("EM_WE_OE", 9, 1),
	REG_MUX("!EM_CE1", 8, 1),
	REG_MUX("!EM_CE0", 7, 1),
	REG_MUX("EM_D15_8", 6, 1),
	REG_MUX("EM_A7", 4, 3),
	REG_MUX("EM_A3", 2, 3),
	REG_MUX("EM_AR", 0, 3),
};

const struct reg_field reg_fields_pinmux3[] = {
	REG_MUX("GIO26", 31, 1),
	REG_MUX("GIO25", 29, 3),
	REG_MUX("GIO24", 28, 1),
	REG_MUX("GIO23", 26, 3),
	REG_MUX("GIO22", 25, 1),
	REG_MUX("GIO21", 23, 3),
	REG_MUX("GIO20", 21, 3),
	REG_MUX("GIO19", 20, 1),
	REG_MUX("GIO18", 19, 1),
	REG_MUX("GIO17", 17, 3),
	REG_MUX("GIO16", 15, 3),
	REG_MUX("GIO15", 14, 1),
	REG_MUX("GIO14", 13, 1),
	REG_MUX("GIO13", 12, 1),
	REG_MUX("GIO12", 11, 1),
	REG_MUX("GIO11", 10, 1),
	REG_MUX("GIO10", 9, 1),
	REG_MUX("GIO9", 8, 1),
	REG_MUX("GIO8", 7, 1),
	REG_MUX("GIO7", 6, 1),
	REG_MUX("GIO6", 5, 1),
	REG_MUX("GIO5", 4, 1),
	REG_MUX("GIO4", 3, 1),
	REG_MUX("GIO3", 2, 1),
	REG_MUX("GIO2", 1, 1),
	REG_MUX("GIO1", 0, 1),
};

const struct reg_field reg_fields_pinmux4[] = {
	REG_MUX("GIO42", 30, 3),
	REG_MUX("GIO41", 28, 3),
	REG_MUX("GIO40", 26, 3),
	REG_MUX("GIO39", 24, 3),
	REG_MUX("GIO38", 22, 3),
	REG_MUX("GIO37", 20, 3),
	REG_MUX("GIO36", 18, 3),
	REG_MUX("GIO35", 16, 3),
	REG_MUX("GIO34", 14, 3),
	REG_MUX("GIO33", 12, 3),
	REG_MUX("GIO32", 10, 3),
	REG_MUX("GIO31", 8, 3),
	REG_MUX("GIO30", 6, 3),
	REG_MUX("GIO29", 4, 3),
	REG_MUX("GIO28", 2, 3),
	REG_MUX("GIO27", 0, 3),
};

const struct reg_field reg_fields_arm_intmux[] = {
	REG_MUX("INT0", 31, 1),
	REG_MUX("INT7", 25, 1),
	REG_MUX("INT8", 24, 1),
	REG_MUX("INT62", 23, 1),
	REG_MUX("INT61", 22, 1),
	REG_MUX("INT59", 21, 1),
	REG_MUX("INT58", 20, 1),
	REG_MUX("INT57", 19, 1),
	REG_MUX("INT56", 18, 1),
	REG_MUX("INT55", 17, 1),
	REG_MUX("INT54", 16, 1),
	REG_MUX("INT53", 15, 1),
	REG_MUX("INT52", 14, 1),
	REG_MUX("INT43", 13, 1),
	REG_MUX("INT38", 12, 1),
	REG_MUX("INT30", 11, 1),
	REG_MUX("INT29", 10, 1),
	REG_MUX("INT28", 9, 1),
	REG_MUX("INT26", 8, 1),
	REG_MUX("INT24", 7, 1),
	REG_MUX("INT20", 5, 1),
	REG_MUX("INT19", 4, 1),
	REG_MUX("INT18", 3, 1),
	REG_MUX("INT17", 2, 1),
	REG_MUX("INT13", 1, 1),
	REG_MUX("INT10", 0, 1),
};

const struct reg_field reg_fields_edma_evtmux[] = {
	REG_MUX("EVT63", 22, 1),
	REG_MUX("EVT62", 21, 1),
	REG_MUX("EVT61", 20, 1),
	REG_MUX("EVT60", 19, 1),
	REG_MUX("EVT59", 18, 1),
	REG_MUX("EVT58", 17, 1),
	REG_MUX("EVT57", 16, 1),
	REG_MUX("EVT56", 15, 1),
	REG_MUX("EVT55", 14, 1),
	REG_MUX("EVT54", 13, 1),
	REG_MUX("EVT53", 12, 1),
	REG_MUX("EVT43", 9, 1),
	REG_MUX("EVT42", 8, 1),
	REG_MUX("EVT41", 7, 1),
	REG_MUX("EVT40", 6, 1),
	REG_MUX("EVT26", 5, 1),
	REG_MUX("EVT19", 4, 1),
	REG_MUX("EVT18", 3, 1),
	REG_MUX("EVT12", 2, 1),
	REG_MUX("EVT3", 1, 1),
	REG_MUX("EVT2", 0, 1),
};

const struct sys_reg_info sys_registers[] = {
	REG_INFO("DEVICE_ID", 0x28, reg_fields_device_id),
	REG_INFO("PINMUX0", 0x00, reg_fields_pinmux0),
	REG_INFO("PINMUX1", 0x04, reg_fields_pinmux1),
	REG_INFO("PINMUX2", 0x08, reg_fields_pinmux2),
	REG_INFO("PINMUX3", 0x0C, reg_fields_pinmux3),
	REG_INFO("PINMUX4", 0x10, reg_fields_pinmux4),
	REG_INFO("ARM_INTMUX", 0x18, reg_fields_arm_intmux),
	REG_INFO("EDMA_EVTMUX", 0x1C, reg_fields_edma_evtmux),
};


static void print_fields(uint32_t reg, const struct reg_field *fp, const size_t len)
{
	char buf[16];

	for (int i = 0; i < len; i++) {
		snprintf(buf, sizeof(buf), fp[i].fmt, (reg >> fp[i].shift) & fp[i].mask);
		printf("\t%s: %s\n", fp[i].name, buf);
	}
}

int main(int argc, char *argv[])
{
	int fd;
	volatile void *sys_mod = mmap_perith(SYSTEM_MODULE_BASE, MMAP_SZ_SYSTEM_MODULE, &fd);

	for (int i = 0; i < ARRAY_SIZE(sys_registers); i++) {
		uint32_t reg = read_u32(sys_mod + sys_registers[i].sys_mod_offset);

		printf("%s: 0x%08X\n", sys_registers[i].name, reg);
		print_fields(reg, sys_registers[i].fields, sys_registers[i].num_fields);
	}

	munmap_perith(sys_mod, MMAP_SZ_SYSTEM_MODULE, &fd);
	return 0;
}
