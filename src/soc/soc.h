//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_SOC_H
#define GEMINISIM_SOC_H


#include "gpio/gpio.h"
#include "sram/sram.h"
#include "cpu/core/core.h"
#include "bus/bus.h"

typedef struct SoC {
    int32_t cycle_count;

    GPIO *gpio;

    SRAM *inst_sram;

    SRAM *data_sram;

    Core *cpu;

    Bus *ibus;
    Bus *dbus;
    IDBus *idbus;

} SoC;

void soc_bus_top(SoC *soc, Bus *bus, uint32_t sram_sel);

void soc_init(
        SoC *soc,
        int32_t cycle_count,
        Core *(*get_cpu)(void),
        const char *inst_filename,
        const char *data_filename
);

void soc_run(SoC *soc, void (*cpu_run)(SoC *soc, void (*hooks[])(SoC *soc), int hook_len));

extern void monitor_top(SoC *soc);

extern void show_gpio_led(SoC *soc);

#endif //GEMINISIM_SOC_H
