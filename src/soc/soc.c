//
// Created by Ellen7ions on 2021/9/3.
//

#include <stdlib.h>

#include "soc.h"
#include "def/mm.h"

void soc_bus_top(SoC *soc, Bus *bus, uint32_t sram_sel) {
    if (IS_GPIO(bus->addr)) {
        gpio_top(soc->gpio, bus);
    } else {
        (sram_sel == 0) ? sram_top(soc->inst_sram, bus) : sram_top(soc->data_sram, bus);
    }
}

void soc_init(
        SoC *soc,
        int32_t cycle_count,
        Core *(*get_cpu)(void),
        const char *inst_filename,
        const char *data_filename
) {
    soc->cycle_count = cycle_count;
    soc->gpio = get_gpio();
    soc->inst_sram = get_inst_sram(inst_filename);
    soc->data_sram = get_data_sram(data_filename);
    soc->cpu = get_cpu();
    soc->ibus = (Bus *) malloc(sizeof(Bus));
    soc->ibus->wen = 0;
    soc->dbus = (Bus *) malloc(sizeof(Bus));
    soc->idbus = (IDBus *) malloc(sizeof(IDBus));
}

void soc_run(SoC *soc, void (*cpu_run)(SoC *soc, void (*hooks[])(SoC *soc), int hook_len)) {
    int32_t cycle_i;
    void (*hooks[])(SoC *soc) = {
            // monitor_top,
            show_gpio_led
    };
    for (cycle_i = 0; cycle_i < soc->cycle_count; cycle_i++) {
        cpu_run(soc, hooks, 1);
    }
}