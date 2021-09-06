//
// Created by Ellen7ions on 2021/9/5.
//

#include <stdlib.h>

#include "core.h"

Core *get_core() {
    Core *cpu = (Core *) malloc(sizeof(Core));
    cpu->regfile = (RegFile *) malloc(sizeof(RegFile));
    cpu->regfile->regs = (uint32_t *) malloc(32 * sizeof(uint32_t));
    int i;
    for (i = 0; i < 32; i++) cpu->regfile->regs[i] = 0;
    cpu->pc = 0xbfc00000;
    return cpu;
}