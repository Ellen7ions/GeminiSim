//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_SOC_H
#define GEMINISIM_SOC_H


#include "gpio/gpio.h"
#include "sram/sram.h"
#include "cpu/core/core.h"
#include "cpu/tiny_kern/tiny_cpu.h"

typedef struct SoC {
    int32_t cycle_count;

    GPIO *gpio;

    SRAM *inst_sram;

    SRAM *data_sram;

    Core *cpu;

} SoC;

void soc_init(SoC *soc, int32_t cycle_count, const char *inst_filename, const char *data_filename);

void soc_run(SoC *soc);

#endif //GEMINISIM_SOC_H