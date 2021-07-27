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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <libgen.h>
#include "i2c.h"
#include "lt8491.h"

static void print_usage(char *prg)
{
	fprintf(stderr, "Usage: %s [options]\n",prg);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "	-p <i2c device> 	I2C port\n");
	fprintf(stderr, "	-a <i2c addr> 		I2C address of power meter (in hex)\n");
	fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
	uint32_t hI2C;
	char * devname = "/dev/i2c-0";
	unsigned char i2caddr = 0x10;

	printf("LT8491 - Buck/Boost Battery Charger with MPPT\r\n");
	printf("https://github.com/craigpeacock/LT8491\r\n");

	int opt;

	while ((opt = getopt(argc, argv, "p:a:?")) != -1) {
		switch (opt) {
			case 'p':
				devname = (char *)optarg;
				break;
			case 'a':
				i2caddr = (unsigned char) strtol((char *)optarg, NULL, 16);
				break;

			default:
				print_usage(basename(argv[0]));
				exit(1);
				break;
		}
	}

	printf("\r\nInitialising device at addr 0x%02X on %s \r\n", i2caddr, devname);

	hI2C = i2c_init(devname);
	lt8491_init(hI2C, i2caddr);

	struct TELEMETRY tele;

	do {

		lt8491_telemetry(hI2C, i2caddr, &tele);
		printf("PV Solar: %.02fV, %.02fA, %.02fW (%.02fW)\r\n", tele.vinr, tele.iin, tele.pin, tele.vinr*tele.iin);
		printf("Battery:  %.02fV, %.02fA, %.02fW (%.02fW)\r\n", tele.vbat, tele.iout, tele.pout, tele.vbat*tele.iout);
		printf("Efficiency: %.01f%% (%.01f%%)\r\n\r\n", tele.eff, (tele.vinr*tele.iin)/(tele.vbat*tele.iout)*100); 
		sleep(1);

	} while(1);
}

