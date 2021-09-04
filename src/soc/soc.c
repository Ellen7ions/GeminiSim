//
// Created by Ellen7ions on 2021/9/3.
//

#include <stdlib.h>
#include "soc.h"

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
    soc->ibus = (InstBus *) malloc(sizeof(InstBus));
    soc->dbus = (DataBus *) malloc(sizeof(DataBus));
    soc->idbus = (IDBus *) malloc(sizeof(IDBus));
}

void soc_run(SoC *soc, void (*cpu_run)(SoC *soc, void (*hook)(SoC *soc))) {
    int32_t cycle_i;

    for (cycle_i = 0; cycle_i < soc->cycle_count; cycle_i++) {
        cpu_run(soc, monitor_top);
    }
}