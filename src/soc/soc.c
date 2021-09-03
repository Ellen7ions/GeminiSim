//
// Created by Ellen7ions on 2021/9/3.
//

#include "soc.h"

#define CPU         soc->cpu
#define INST_SRAM   soc->inst_sram
#define DATA_SRAM   soc->data_sram

void soc_init(SoC *soc, int32_t cycle_count, const char *inst_filename, const char *data_filename) {
    soc->cycle_count = cycle_count;
    soc->gpio = get_gpio();
    soc->inst_sram = get_inst_sram(inst_filename);
    soc->data_sram = get_data_sram(data_filename);
    soc->cpu = get_tinycpu();
}

void soc_run(SoC *soc) {
    int32_t cycle_i;
    InstBus *ibus;
    DataBus *dbus;
    IDBus *idbus;
    for (cycle_i; cycle_i < soc->cycle_count; cycle_i++) {
        CPU->core_fetch(CPU,ibus);
        inst_sram_proxy(INST_SRAM, ibus);
        idbus->inst = ibus->inst_rdata;
        CPU->core_decode(CPU, idbus);
        CPU->core_lsu(CPU, idbus, dbus);
        CPU->core_wb(CPUM idbus);
    }
}