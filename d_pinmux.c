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

#define REG_FMT_D01(_name, _shift, _mask)	{_name, "%01d", _shift, _mask}
#define REG_INFO(_name, offs, fields)		{_name, offs, fields, ARRAY_SIZE(fields)}

const struct reg_field reg_fields_device_id[] = {
	{"DEVREV", "%01X", 28, 0xff},
	{"PARTNUM", "%04X", 12, 0xffff},
	{"MFGR", "%03X", 1, 0x7ff},
};

const struct reg_field reg_fields_pinmux0[] = {
	REG_FMT_D01("MMC/SD0", 24, 1),
	REG_FMT_D01("GIO49", 23, 1),
	REG_FMT_D01("GIO48", 22, 1),
	REG_FMT_D01("GIO47", 21, 1),
	REG_FMT_D01("GIO46", 20, 1),
	REG_FMT_D01("GIO45", 19, 1),
	REG_FMT_D01("GIO44", 18, 1),
	REG_FMT_D01("GIO43", 16, 3),
	REG_FMT_D01("C_WE_FIELD", 14, 3),
	REG_FMT_D01("VD", 13, 1),
	REG_FMT_D01("HD", 12, 1),
	REG_FMT_D01("YIN0", 11, 1),
	REG_FMT_D01("YIN1", 10, 1),
	REG_FMT_D01("YIN2", 9, 1),
	REG_FMT_D01("YIN3", 8, 1),
	REG_FMT_D01("YIN4", 6, 3),
	REG_FMT_D01("YIN5", 4, 3),
	REG_FMT_D01("YIN6", 2, 3),
	REG_FMT_D01("YIN7", 0, 3),
};

const struct reg_field reg_fields_pinmux1[] = {
	REG_FMT_D01("VCLK", 22, 1),
	REG_FMT_D01("EXTCLK", 20, 3),
	REG_FMT_D01("FIELD", 18, 3),
	REG_FMT_D01("LCD_OE", 17, 1),
	REG_FMT_D01("HVSYNC", 16, 1),
	REG_FMT_D01("COUT0", 14, 3),
	REG_FMT_D01("COUT1", 12, 3),
	REG_FMT_D01("COUT2", 10, 3),
	REG_FMT_D01("COUT3", 8, 3),
	REG_FMT_D01("COUT4", 6, 3),
	REG_FMT_D01("COUT5", 4, 3),
	REG_FMT_D01("COUT6", 2, 3),
	REG_FMT_D01("COUT7", 0, 3),
};

const struct reg_field reg_fields_pinmux2[] = {
	REG_FMT_D01("EM_CLK", 12, 1),
	REG_FMT_D01("EM_ADV", 11, 1),
	REG_FMT_D01("EM_WAIT", 10, 1),
	REG_FMT_D01("EM_WE_OE", 9, 1),
	REG_FMT_D01("!EM_CE1", 8, 1),
	REG_FMT_D01("!EM_CE0", 7, 1),
	REG_FMT_D01("EM_D15_8", 6, 1),
	REG_FMT_D01("EM_A7", 4, 3),
	REG_FMT_D01("EM_A3", 2, 3),
	REG_FMT_D01("EM_AR", 0, 3),
};

const struct reg_field reg_fields_pinmux3[] = {
	REG_FMT_D01("GIO26", 31, 1),
	REG_FMT_D01("GIO25", 29, 3),
	REG_FMT_D01("GIO24", 28, 1),
	REG_FMT_D01("GIO23", 26, 3),
	REG_FMT_D01("GIO22", 25, 1),
	REG_FMT_D01("GIO21", 23, 3),
	REG_FMT_D01("GIO20", 21, 3),
	REG_FMT_D01("GIO19", 20, 1),
	REG_FMT_D01("GIO18", 19, 1),
	REG_FMT_D01("GIO17", 17, 3),
	REG_FMT_D01("GIO16", 15, 3),
	REG_FMT_D01("GIO15", 14, 1),
	REG_FMT_D01("GIO14", 13, 1),
	REG_FMT_D01("GIO13", 12, 1),
	REG_FMT_D01("GIO12", 11, 1),
	REG_FMT_D01("GIO11", 10, 1),
	REG_FMT_D01("GIO10", 9, 1),
	REG_FMT_D01("GIO9", 8, 1),
	REG_FMT_D01("GIO8", 7, 1),
	REG_FMT_D01("GIO7", 6, 1),
	REG_FMT_D01("GIO6", 5, 1),
	REG_FMT_D01("GIO5", 4, 1),
	REG_FMT_D01("GIO4", 3, 1),
	REG_FMT_D01("GIO3", 2, 1),
	REG_FMT_D01("GIO2", 1, 1),
	REG_FMT_D01("GIO1", 0, 1),
};

const struct reg_field reg_fields_pinmux4[] = {
	REG_FMT_D01("GIO42", 30, 3),
	REG_FMT_D01("GIO41", 28, 3),
	REG_FMT_D01("GIO40", 26, 3),
	REG_FMT_D01("GIO39", 24, 3),
	REG_FMT_D01("GIO38", 22, 3),
	REG_FMT_D01("GIO37", 20, 3),
	REG_FMT_D01("GIO36", 18, 3),
	REG_FMT_D01("GIO35", 16, 3),
	REG_FMT_D01("GIO34", 14, 3),
	REG_FMT_D01("GIO33", 12, 3),
	REG_FMT_D01("GIO32", 10, 3),
	REG_FMT_D01("GIO31", 8, 3),
	REG_FMT_D01("GIO30", 6, 3),
	REG_FMT_D01("GIO29", 4, 3),
	REG_FMT_D01("GIO28", 2, 3),
	REG_FMT_D01("GIO27", 0, 3),
};

const struct reg_field reg_fields_arm_intmux[] = {
	REG_FMT_D01("INT0", 31, 1),
	REG_FMT_D01("INT7", 25, 1),
	REG_FMT_D01("INT8", 24, 1),
	REG_FMT_D01("INT62", 23, 1),
	REG_FMT_D01("INT61", 22, 1),
	REG_FMT_D01("INT59", 21, 1),
	REG_FMT_D01("INT58", 20, 1),
	REG_FMT_D01("INT57", 19, 1),
	REG_FMT_D01("INT56", 18, 1),
	REG_FMT_D01("INT55", 17, 1),
	REG_FMT_D01("INT54", 16, 1),
	REG_FMT_D01("INT53", 15, 1),
	REG_FMT_D01("INT52", 14, 1),
	REG_FMT_D01("INT43", 13, 1),
	REG_FMT_D01("INT38", 12, 1),
	REG_FMT_D01("INT30", 11, 1),
	REG_FMT_D01("INT29", 10, 1),
	REG_FMT_D01("INT28", 9, 1),
	REG_FMT_D01("INT26", 8, 1),
	REG_FMT_D01("INT24", 7, 1),
	REG_FMT_D01("INT20", 5, 1),
	REG_FMT_D01("INT19", 4, 1),
	REG_FMT_D01("INT18", 3, 1),
	REG_FMT_D01("INT17", 2, 1),
	REG_FMT_D01("INT13", 1, 1),
	REG_FMT_D01("INT10", 0, 1),
};

const struct reg_field reg_fields_edma_evtmux[] = {
	REG_FMT_D01("EVT63", 22, 1),
	REG_FMT_D01("EVT62", 21, 1),
	REG_FMT_D01("EVT61", 20, 1),
	REG_FMT_D01("EVT60", 19, 1),
	REG_FMT_D01("EVT59", 18, 1),
	REG_FMT_D01("EVT58", 17, 1),
	REG_FMT_D01("EVT57", 16, 1),
	REG_FMT_D01("EVT56", 15, 1),
	REG_FMT_D01("EVT55", 14, 1),
	REG_FMT_D01("EVT54", 13, 1),
	REG_FMT_D01("EVT53", 12, 1),
	REG_FMT_D01("EVT43", 9, 1),
	REG_FMT_D01("EVT42", 8, 1),
	REG_FMT_D01("EVT41", 7, 1),
	REG_FMT_D01("EVT40", 6, 1),
	REG_FMT_D01("EVT26", 5, 1),
	REG_FMT_D01("EVT19", 4, 1),
	REG_FMT_D01("EVT18", 3, 1),
	REG_FMT_D01("EVT12", 2, 1),
	REG_FMT_D01("EVT3", 1, 1),
	REG_FMT_D01("EVT2", 0, 1),
};

const struct reg_field reg_fields_vdac_config[] = {
	REG_FMT_D01("TVSHORT", 31, 1),
	REG_FMT_D01("TVINT", 30, 1),
	REG_FMT_D01("PDTVSHORTZ", 19, 1),
	REG_FMT_D01("XDMODE", 5, 1),
	REG_FMT_D01("PWDNZ_TVDETECT", 4, 1),
	REG_FMT_D01("PWDNBUFZ", 3, 1),
	REG_FMT_D01("PWD_C", 2, 1),
	REG_FMT_D01("PWD_B", 1, 1),
	REG_FMT_D01("PWD_A", 0, 1),
};

const struct reg_field reg_fields_usb_phy_ctrl[] = {
	REG_FMT_D01("PHYCLKFREQ", 12, 15),
	REG_FMT_D01("DATAPOL", 11, 1),
	REG_FMT_D01("PHYCLKSRC", 9, 3),
	REG_FMT_D01("PHYCLKGD", 8, 1),
	REG_FMT_D01("SESNDEN", 7, 1),
	REG_FMT_D01("VBDTCTEN", 6, 1),
	REG_FMT_D01("VBUSENS", 5, 1),
	REG_FMT_D01("PHYPLLON", 4, 1),
	REG_FMT_D01("OTGPDWN", 1, 1),
	REG_FMT_D01("PHYPDWN", 0, 1),
};

const struct reg_field reg_fields_vpss_clk_ctrl[] = {
	REG_FMT_D01("VPSS_CLKMD", 7, 1),
	REG_FMT_D01("VENC_CLK_SRC", 5, 3),
	REG_FMT_D01("DACCLKEN", 4, 1),
	REG_FMT_D01("VENCCLKEN", 3, 1),
	REG_FMT_D01("PCLK_INV", 2, 1),
	REG_FMT_D01("VPSS_MUXSEL", 0, 3),
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
	REG_INFO("VDAC_CONFIG", 0x2C, reg_fields_vdac_config),
	REG_INFO("USB_PHY_CTRL", 0x34, reg_fields_usb_phy_ctrl),
	REG_INFO("VPSS_CLK_CTRL", 0x44, reg_fields_vpss_clk_ctrl),
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
