//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_CPUBUS_H
#define GEMINISIM_CPUBUS_H

#include "stdint.h"

typedef struct InstBus {
    uint32_t inst_en;
    uint32_t inst_addr;
    uint32_t inst_rdata;
} InstBus;

typedef struct DataBus {
    uint32_t data_en;
    uint32_t data_wen;
    uint32_t data_addr;
    uint32_t data_wdata;
    uint32_t data_rdata;
} DataBus;

typedef struct IDBus {
    uint32_t pc;
    uint32_t inst;

    uint32_t rs_data;
    uint32_t rt_data;

    uint32_t src_a;
    uint32_t src_b;
    uint32_t alu_result;

    uint32_t alu_op_code;
    uint32_t w_reg_en;
    uint32_t w_reg_addr;
    uint32_t lsu_en;
    uint32_t lsu_wen;
    uint32_t lsu_wdata;
    uint32_t lsu_rdata;
} IDBus;

#endif //GEMINISIM_CPUBUS_H
