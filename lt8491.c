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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "i2c.h"
#include "lt8491.h"

void lt8491_init(uint32_t i2c_master_port, uint8_t i2c_slave_addr)
{
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RSENSE1,     5 * 100);	// 5mOhms
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RIMON_OUT, 240 * 100);	// 240k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RSENSE2,     5 * 100);	// 5mOhms
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RDAC0,   150.1 * 100);	// 150.1k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBOUT1,   274 * 10);	// 274k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBOUT2,  23.2 * 100);	// 23.2k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RDACI,   18.34 * 100);	// 18.34k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBIN2,   7.32 * 100);	// 7.32k
	i2c_write_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBIN1,   95.3 * 10);	// 95.3k

	printf("Version:        0x%04X\r\n",i2c_read_byte(i2c_master_port, i2c_slave_addr, LT8491_STAT_VERSION));

	printf("CFG_RSENSE1:    0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RSENSE1));
	printf("CFG_RIMON_OUT:  0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RIMON_OUT));
	printf("CFG_RSENSE2:    0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RSENSE2));
	printf("CFG_RDAC0:      0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RDAC0));
	printf("CFG_RFBOUT1:    0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBOUT1));
	printf("CFG_RFBOUT2:    0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBOUT2));
	printf("CFG_RDACI:      0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RDACI));
	printf("CFG_RFBIN2:     0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBIN2));
	printf("CFG_RFBIN1:     0x%04X\r\n",i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_CFG_RFBIN1));

	printf("\r\n");
	sleep(1);
}

int lt8491_telemetry(uint32_t i2c_master_port, uint8_t i2c_slave_addr, struct TELEMETRY *telemetry)
{
	telemetry->tbat = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_TBAT) / 10;
	telemetry->pout = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_POUT) / 100;
	telemetry->pin  = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_PIN)  / 100;
	telemetry->eff  = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_EFF)  / 100;
	telemetry->iout = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_IOUT) / 1000;
	telemetry->iin  = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_IIN)  / 1000;
	telemetry->vbat = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_VBAT) / 100;
	telemetry->vin  = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_VIN)  / 100;
	telemetry->vinr = (float) i2c_read_short(i2c_master_port, i2c_slave_addr, LT8491_TELE_VINR) / 100;
}

int lt8491_status(uint32_t i2c_master_port, uint8_t i2c_slave_addr, struct STATUS *status)
{
	status->charger.value = i2c_read_byte(i2c_master_port, i2c_slave_addr, LT8491_STAT_CHARGER);
	status->system.value = i2c_read_byte(i2c_master_port, i2c_slave_addr, LT8491_STAT_SYSTEM);
	status->supply.value = i2c_read_byte(i2c_master_port, i2c_slave_addr, LT8491_STAT_SUPPLY);
	status->faults.value = i2c_read_byte(i2c_master_port, i2c_slave_addr, LT8491_STAT_CHRG_FAULTS);
}
