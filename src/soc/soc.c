//
// Created by Ellen7ions on 2021/9/3.
//

#include <stdlib.h>
#include "soc.h"

#define CPU         soc->cpu
#define IBUS        soc->ibus
#define DBUS        soc->dbus
#define IDBUS       soc->idbus
#define INST_SRAM   soc->inst_sram
#define DATA_SRAM   soc->data_sram

void soc_init(SoC *soc, int32_t cycle_count, const char *inst_filename, const char *data_filename) {
    soc->cycle_count = cycle_count;
    soc->gpio = get_gpio();
    soc->inst_sram = get_inst_sram(inst_filename);
    soc->data_sram = get_data_sram(data_filename);
    soc->cpu = get_tinycpu();
    soc->ibus = (InstBus *) malloc(sizeof(InstBus));
    soc->dbus = (DataBus *) malloc(sizeof(DataBus));
    soc->idbus = (IDBus *) malloc(sizeof(IDBus));
}

void soc_run(SoC *soc, void (*hook)(SoC *soc)) {
    int32_t cycle_i;

    for (cycle_i = 0; cycle_i < soc->cycle_count; cycle_i++) {
        CPU->core_fetch(CPU, IDBUS, IBUS);
        inst_sram_proxy(INST_SRAM, IBUS);
        IDBUS->inst = IBUS->inst_rdata;
        CPU->core_decode(CPU, IDBUS);
        CPU->core_exe(CPU, IDBUS);
        CPU->core_lsu(CPU, IDBUS, DBUS);
        CPU->core_wb(CPU, IDBUS);
        hook(soc);
    }
}