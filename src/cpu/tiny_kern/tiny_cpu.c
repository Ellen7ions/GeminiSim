//
// Created by Ellen7ions on 2021/9/3.
//
#include "stdlib.h"

#include "../../def/utils.h"
#include "tiny_cpu.h"

#define CPU         soc->cpu
#define IBUS        soc->ibus
#define DBUS        soc->dbus
#define IDBUS       soc->idbus
#define INST_SRAM   soc->inst_sram
#define DATA_SRAM   soc->data_sram

Core *get_tinycpu() {
    Core *tinycpu = (Core *) malloc(sizeof(Core));
    tinycpu->regfile = (RegFile *) malloc(sizeof(RegFile));
    tinycpu->regfile->regs = (uint32_t *) malloc(32 * sizeof(uint32_t));
    int i;
    for (i = 0; i < 32; i++) tinycpu->regfile->regs[i] = 0;
    tinycpu->pc = 0xbfc00000;
    return tinycpu;
}

void tinycpu_run(SoC *soc, void(*hook)(SoC *soc)) {
    tinycpu_fetch(CPU, IDBUS, IBUS);
    inst_sram_proxy(INST_SRAM, IBUS);
    IDBUS->inst = IBUS->inst_rdata;
    tinycpu_decode(CPU, IDBUS);
    tinycpu_exe(CPU, IDBUS);
    tinycpu_lsu(CPU, IDBUS, DBUS);
    tinycpu_wb(CPU, IDBUS);
    hook(soc);
}

void tinycpu_fetch(Core *core, IDBus *idbus, InstBus *ibus) {
    ibus->inst_en = 1;
    ibus->inst_addr = core->pc;
    idbus->pc = core->pc;
    core->pc = core->pc + 4;
}

void tinycpu_decode(Core *core, IDBus *idbus) {
    uint32_t op_code = SLICE_OP(idbus->inst);
    uint32_t func_code = SLICE_FUNC(idbus->inst);
    uint32_t rs = SLICE_RS(idbus->inst);
    uint32_t rt = SLICE_RT(idbus->inst);
    uint32_t rd = SLICE_RD(idbus->inst);
    uint32_t ext_imme = SLICE_IMME(idbus->inst);

    idbus->rs_data = core->regfile->regs[rs];
    idbus->rt_data = core->regfile->regs[rt];

    idbus->src_a = idbus->rs_data;
    idbus->src_b = (op_code == SPECIAL_OP_CODE) ? idbus->rt_data : (op_code == ADDIU_OP_CODE) ? ext_imme : 0;

    idbus->w_reg_en = (op_code == SPECIAL_OP_CODE) || (op_code == ADDIU_OP_CODE);
    idbus->w_reg_addr = (op_code == SPECIAL_OP_CODE) ? rd : (op_code == ADDIU_OP_CODE) ? rt : 0;

    idbus->alu_op_code = (op_code == SPECIAL_OP_CODE && (func_code == ADD_FUNCT || func_code == ADDU_FUNCT) ||
                          op_code == ADDIU_OP_CODE)
                         ? ALU_SEL_ADD : 0;
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
            core->regfile->regs[idbus->w_reg_addr] = idbus->lsu_rdata;
        } else {
            core->regfile->regs[idbus->w_reg_addr] = idbus->alu_result;
        }
    }
}