//
// Created by Ellen7ions on 2021/9/3.
//
#include "stdlib.h"

#include "../../def/utils.h"
#include "tiny_cpu.h"

Core *get_tinycpu() {
    Core *tinycpu = (Core*)malloc(sizeof(Core));
    tinycpu->core_fetch     = tinycpu_fetch;
    tinycpu->core_decode    = tinycpu_decode;
    tinycpu->core_exe       = tinycpu_exe;
    tinycpu->core_lsu       = tinycpu_lsu;
    tinycpu->core_wb        = tinycpu_wb;
    return tinycpu;
}

void tinycpu_fetch(Core *core, InstBus *ibus) {
    ibus->inst_en = 1;
    ibus->inst_addr = core->pc;
}

void tinycpu_decode(Core *core, IDBus *idbus) {
    uint32_t op_code = SLICE(idbus->inst, 31, 26);
    uint32_t func_code = SLICE(idbus->inst, 5, 0);
    uint32_t rs = SLICE(idbus->inst, 25, 21);
    uint32_t rt = SLICE(idbus->inst, 20, 16);
    uint32_t rd = SLICE(idbus->inst, 15, 11);

    idbus->src_a = rs;
    idbus->src_b = rt;
    idbus->w_reg_addr = rd;
    idbus->alu_op_code = ALU_SEL_ADD;
    idbus->lsu_en = 0;
    idbus->lsu_wen = 0;
    idbus->lsu_wdata = 0;
}

void tinycpu_exe(Core *core, IDBus *idbus) {
    idbus->alu_result = alu_cal(idbus->alu_op_code, idbus->src_a, idbus->src_b);
}

void tinycpu_lsu(Core *core, IDBus *idbus, DataBus *dbus) {
    dbus->data_en = idbus->lsu_en;
    dbus->data_wen = idbus->lsu_wen;
    dbus->data_addr = idbus->alu_result;
    dbus->data_wdata = idbus->lsu_wdata;
}

void tinycpu_wb(Core *core, IDBus *idbus) {
    if (idbus->w_reg_en) {
        if (idbus->lsu_en && idbus->lsu_wen == 0) {
            core->regfile[idbus->w_reg_addr] = idbus->lsu_rdata;
        } else {
            core->regfile[idbus->w_reg_addr] = idbus->alu_result;
        }
    }
}