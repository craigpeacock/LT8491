/*
 * LT8491 - Buck/Boost Battery Charger with MPPT
 * Copyright (C) 2021 Craig Peacock
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef MAIN_LT8491_H_
#define MAIN_LT8491_H_

#define LT8491_SLAVE_ADDRESS		0x10

#define LT8491_TELE_TBAT		0x00
#define LT8491_TELE_POUT		0x02
#define LT8491_TELE_PIN			0x04
#define LT8491_TELE_EFF			0x06
#define LT8491_TELE_IOUT		0x08
#define LT8491_TELE_IIN			0x0A
#define LT8491_TELE_VBAT		0x0C
#define LT8491_TELE_VIN			0x0E
#define LT8491_TELE_VINR		0x10

#define LT8491_STAT_CHARGER		0x12
#define LT8491_STAT_SYSTEM		0x13
#define LT8491_STAT_SUPPLY		0x14
#define LT8491_STAT_TS0_REMAIN 		0x15
#define LT8491_STAT_TS1_REMAIN 		0x16
#define LT8491_STAT_TS2_REMAIN 		0x17
#define LT8491_STAT_TS3_REMAIN 		0x18
#define LT8491_STAT_CHRG_FAULTS 	0x19
#define LT8491_STAT_VERSION		0x1A
#define LT8491_STAT_BOOT_CRC		0x1C
#define LT8491_STAT_CFG_CRC		0x1E

#define LT8491_CTRL_WRT_TO_BOOT		0x20
#define LT8491_CTRL_EE_WRT_EN		0x21
#define LT8491_CTRL_HALT_STARTUP	0x22
#define LT8491_CTRL_CHRG_EN		0x23
#define LT8491_CTRL_RESTART_CHIP	0x24
#define LT8491_CTRL_RESET_FLAG		0x25
#define LT8491_CTRL_UPDATE_TELEM	0x26

#define LT8491_CFG_RSENSE1		0x28
#define LT8491_CFG_RIMON_OUT		0x2A
#define LT8491_CFG_RSENSE2		0x2C
#define LT8491_CFG_RDAC0		0x2E
#define LT8491_CFG_RFBOUT1		0x30
#define LT8491_CFG_RFBOUT2		0x32
#define LT8491_CFG_RDACI		0x34
#define LT8491_CFG_RFBIN2		0x36
#define LT8491_CFG_RFBIN1		0x38
#define LT8491_CFG_INIT_CHRG_EN		0x3A
#define LT8491_CFG_VS3_25C		0x3B
#define LT8491_CFG_UV_S0		0x3C
#define LT8491_CFG_S0_UV		0x3D
#define LT8491_CFG_S0_S1		0x3E
#define LT8491_CFG_S1_S0		0x3F
#define LT8491_CFG_TBAT_MIN		0x40
#define LT8491_CFG_TBAT_MAX		0x41
#define LT8491_CFG_TMR_S0		0x42
#define LT8491_CFG_TMR_S1		0x43
#define LT8491_CFG_TMR_S2		0x44
#define LT8491_CFG_TMR_S3		0x45
#define LT8491_CFG_RSTRT_IN_FLT		0x46
#define LT8491_CFG_RSTRT_IN_DONEA	0x47
#define LT8491_CFG_RSTRT_IN_DONEB	0x48
#define LT8491_CFG_RSTRT_IN_S3		0x49
#define LT8491_CFG_TERMINATE		0x4A
#define LT8491_CFG_SCAN_RATE_LP		0x4B
#define LT8491_CFG_SCAN_RATE		0x4C
#define LT8491_CFG_CHRG_MISC		0x4D
#define LT8491_CFG_TC3			0x4E
#define LT8491_CFG_TC2			0x52
#define LT8491_CFG_TC1			0x56
#define LT8491_CFG_USER_CODE		0x5A

#define LT8491_MFR_DATA1		0x5C
#define LT8491_MFR_DATA2		0x5E
#define LT8491_MFR_DATA3		0x60


struct TELEMETRY {
	float tbat;
	float pout;
	float pin;
	float eff;
	float iout;
	float iin;
	float vbat;
	float vin;
	float vinr;
};

void lt8491_init(uint32_t i2c_master_port, uint8_t i2c_slave_addr);
int lt8491_telemetry(uint32_t i2c_master_port, uint8_t i2c_slave_addr, struct TELEMETRY *telemetry);

#endif
