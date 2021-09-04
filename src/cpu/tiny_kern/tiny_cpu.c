//
// Created by Ellen7ions on 2021/9/3.
//
#include "stdlib.h"

#include "../../def/utils.h"
#include "tiny_cpu.h"
#include "cpu/alu/alu.h"

#define CPU         soc->cpu
#define IBUS        soc->ibus
#define DBUS        soc->dbus
#define IDBUS       soc->idbus

Core *get_tinycpu() {
    Core *tinycpu = (Core *) malloc(sizeof(Core));
    tinycpu->regfile = (RegFile *) malloc(sizeof(RegFile));
    tinycpu->regfile->regs = (uint32_t *) malloc(32 * sizeof(uint32_t));
    int i;
    for (i = 0; i < 32; i++) tinycpu->regfile->regs[i] = 0;
    tinycpu->pc = 0xbfc00000;
    return tinycpu;
}

void tinycpu_run(SoC *soc, void(*hooks[])(SoC *soc), int hook_len) {
    tinycpu_fetch(CPU, IDBUS, IBUS);
    soc_bus_top(soc, IBUS, 0);
    IDBUS->inst = IBUS->rdata;
    tinycpu_decode(CPU, IDBUS);
    tinycpu_exe(CPU, IDBUS);
    tinycpu_lsu(CPU, IDBUS, DBUS);
    soc_bus_top(soc, DBUS, 1);
    IDBUS->lsu_rdata = DBUS->rdata;
    tinycpu_wb(CPU, IDBUS);
    int i;
    for (i = 0; i < hook_len; i++) hooks[i](soc);
}

void tinycpu_fetch(Core *core, IDBus *idbus, Bus *ibus) {
    ibus->en = 1;
    ibus->addr = core->pc;
    idbus->pc = core->pc;
    core->pc = core->pc + 4;
}

void tinycpu_decode(Core *core, IDBus *idbus) {
    uint32_t op_code = SLICE_OP  (idbus->inst);
    uint32_t func_code = SLICE_FUNC(idbus->inst);
    uint32_t rs = SLICE_RS  (idbus->inst);
    uint32_t rt = SLICE_RT  (idbus->inst);
    uint32_t rd = SLICE_RD  (idbus->inst);
    uint32_t ext_imme = SLICE_IMME(idbus->inst);

    idbus->rs_data = core->regfile->regs[rs];
    idbus->rt_data = core->regfile->regs[rt];

    idbus->src_a = idbus->rs_data;
    idbus->src_b = (op_code == SPECIAL_OP_CODE) ? idbus->rt_data : (op_code == ADDIU_OP_CODE || op_code == LW_OP_CODE ||
                                                                    op_code == SW_OP_CODE || op_code == LUI_OP_CODE)
                                                                   ? ext_imme : 0;

    idbus->w_reg_en = (op_code == SPECIAL_OP_CODE) ||
                      (op_code == ADDIU_OP_CODE || op_code == LW_OP_CODE || op_code == LUI_OP_CODE);
    idbus->w_reg_addr = (op_code == SPECIAL_OP_CODE) ? rd : (op_code == ADDIU_OP_CODE || op_code == LW_OP_CODE ||
                                                             op_code == LUI_OP_CODE) ? rt
                                                                                     : 0;

    idbus->alu_op_code = (op_code == SPECIAL_OP_CODE && (func_code == ADD_FUNCT || func_code == ADDU_FUNCT) ||
                          op_code == ADDIU_OP_CODE || op_code == LW_OP_CODE || op_code == SW_OP_CODE)
                         ? ALU_SEL_ADD : (op_code == LUI_OP_CODE) ? ALU_SEL_LUI : 0;
    idbus->lsu_en = (op_code == LW_OP_CODE || op_code == SW_OP_CODE);
    idbus->lsu_wen = (op_code == SW_OP_CODE);
    idbus->lsu_wdata = idbus->rt_data;
}

void tinycpu_exe(Core *core, IDBus *idbus) {
    idbus->alu_result = alu_cal(idbus->alu_op_code, idbus->src_a, idbus->src_b);
}

void tinycpu_lsu(Core *core, IDBus *idbus, Bus *dbus) {
    dbus->en = idbus->lsu_en;
    dbus->wen = idbus->lsu_wen;
    dbus->addr = idbus->alu_result;
    dbus->wdata = idbus->lsu_wdata;
}

void tinycpu_wb(Core *core, IDBus *idbus) {
    if (idbus->w_reg_en) {
        if (idbus->lsu_en && idbus->lsu_wen == 0) {
            core->regfile->regs[idbus->w_reg_addr] = idbus->lsu_rdata;
        } else if (idbus->w_reg_addr != 0) {
            core->regfile->regs[idbus->w_reg_addr] = idbus->alu_result;
        }
    }
}