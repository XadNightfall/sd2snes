/* sd2snes - SD card based universal cartridge for the SNES
   Copyright (C) 2009-2010 Maximilian Rehkopf <otakon@gmx.net>
   uC firmware portion

   Inspired by and based on code from sd2iec, written by Ingo Korb et al.
   See sdcard.c|h, config.h.

   FAT file system access based on code by ChaN, Jim Brain, Ingo Korb,
   see ff.c|h.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License only.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   fpga_spi.h: functions for SPI ctrl, SRAM interfacing and feature configuration
*/

#ifndef _FPGA_SPI_H
#define _FPGA_SPI_H

#include <arm/NXP/LPC17xx/LPC17xx.h>
#include "bits.h"

#define FPGA_SS_BIT	16
#define FPGA_SS_REG	LPC_GPIO0

#define FPGA_SELECT()	do {FPGA_TX_SYNC(); BITBAND(FPGA_SS_REG->FIOCLR, FPGA_SS_BIT) = 1;} while (0)
#define FPGA_SELECT_ASYNC()	do {BITBAND(FPGA_SS_REG->FIOCLR, FPGA_SS_BIT) = 1;} while (0)
#define FPGA_DESELECT()	do {FPGA_TX_SYNC(); BITBAND(FPGA_SS_REG->FIOSET, FPGA_SS_BIT) = 1;} while (0)
#define FPGA_DESELECT_ASYNC()	do {BITBAND(FPGA_SS_REG->FIOSET, FPGA_SS_BIT) = 1;} while (0)

#define FPGA_TX_SYNC()     spi_tx_sync()
#define FPGA_TX_BYTE(x)    spi_tx_byte(x)
#define FPGA_RX_BYTE()     spi_rx_byte()
#define FPGA_TXRX_BYTE(x)  spi_txrx_byte(x)
#define FPGA_TX_BLOCK(x,y) spi_tx_block(x,y)
#define FPGA_RX_BLOCK(x,y) spi_rx_block(x,y)

#define FPGA_SPI_FAST()    spi_set_speed(SPI_SPEED_FPGA_FAST)
#define FPGA_SPI_SLOW()    spi_set_speed(SPI_SPEED_FPGA_SLOW)

void fpga_spi_init(void);
uint8_t fpga_test(void);
uint16_t fpga_status(void);
void spi_fpga(void);
void spi_sd(void);
void spi_none(void);
void set_mcu_addr(uint32_t);
void set_dac_addr(uint16_t);
void set_dac_vol(uint8_t);
void dac_play(void);
void dac_pause(void);
void dac_reset(void);
void msu_reset(uint16_t);
void set_msu_addr(uint16_t);
void set_msu_status(uint8_t set, uint8_t reset);
void set_saveram_mask(uint32_t);
void set_rom_mask(uint32_t);
void set_mapper(uint8_t val);
void fpga_sddma(uint8_t tgt, uint8_t partial);
void fpga_set_sddma_range(uint16_t start, uint16_t end);
uint8_t get_msu_volume(void);
uint16_t get_msu_track(void);
uint32_t get_msu_offset(void);
uint32_t get_snes_sysclk(void);
void set_bsx_regs(uint8_t set, uint8_t reset);
void set_fpga_time(uint64_t time);
void fpga_reset_srtc_state(void);

#endif
