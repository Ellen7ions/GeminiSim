//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_SRAM_H
#define GEMINISIM_SRAM_H

#include <stdio.h>
#include "../cpu/cpubus.h"
#include "bus/bus.h"

// 64 line --> 64 * 4 = 256B
#define SRAM_SIZE 64

typedef struct SRAM {
    FILE *file;
} SRAM;

SRAM *get_inst_sram(const char *filename);

SRAM *get_data_sram(const char *filename);

void init_sram(SRAM *sram, const char *filename, const char *);

void init_inst_sram(SRAM *sram, const char *filename);

void init_data_sram(SRAM *sram, const char *filename);

uint32_t sram_read(SRAM *sram, uint32_t addr);

void sram_write(SRAM *sram, uint32_t addr, uint32_t wdata);

void sram_top(SRAM *sram, Bus *bus);

#endif //GEMINISIM_SRAM_H
