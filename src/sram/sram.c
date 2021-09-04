//
// Created by Ellen7ions on 2021/9/3.
//

#include "stdlib.h"

#include "stdio.h"
#include "sram.h"

SRAM *get_inst_sram(const char *filename) {
    SRAM *inst_sram = (SRAM *) malloc(sizeof(SRAM));
    init_inst_sram(inst_sram, filename);
    return inst_sram;
}

SRAM *get_data_sram(const char *filename) {
    SRAM *inst_sram = (SRAM *) malloc(sizeof(SRAM));
    init_data_sram(inst_sram, filename);
    return inst_sram;
}

void init_sram(SRAM *sram, const char *filename, const char *mode) {
    sram->file = fopen(filename, mode);
}

void init_inst_sram(SRAM *sram, const char *filename) {
    init_sram(sram, filename, "rb");
}

void init_data_sram(SRAM *sram, const char *filename) {
    init_sram(sram, filename, "rb+");
}

uint32_t sram_read(SRAM *sram, uint32_t addr) {
    uint32_t result;
    uint32_t _addr = addr & 0xfc;
    rewind(sram->file);
    fseek(sram->file, _addr, SEEK_SET);
    fread(&result, sizeof(result), 1, sram->file);
    return result;
}

void sram_write(SRAM *sram, uint32_t addr, uint32_t wdata) {
    uint32_t _addr = addr & 0xfc;
    rewind(sram->file);
    fseek(sram->file, _addr, SEEK_CUR);
    fwrite(&wdata, sizeof(wdata), 1, sram->file);
}

void sram_top(SRAM *sram, Bus *bus) {
    if (bus->en) {
        if (bus->wen) {
            sram_write(sram, bus->addr, bus->wdata);
        } else {
            bus->rdata = sram_read(sram, bus->addr);
        }
    }
}