//
// Created by Ellen7ions on 2021/9/3.
//

#include "alu.h"

uint32_t alu_cal(uint32_t alu_op_code, uint32_t src_a, uint32_t src_b) {
    uint32_t result;
    switch (alu_op_code) {
        case ALU_SEL_ADD:
            result = src_a + src_b;
            break;
        case ALU_SEL_SUB:
            result = src_a - src_b;
            break;
        case ALU_SEL_SLT:
            result = (int) src_a < (int) src_b ? 1 : 0;
            break;
        case ALU_SEL_SLTU:
            result = src_a < src_b ? 1 : 0;
            break;
        case ALU_SEL_AND:
            result = src_a & src_b;
            break;
        case ALU_SEL_NOR:
            result = ~(src_a | src_b);
            break;
        case ALU_SEL_OR:
            result = src_a | src_b;
            break;
        case ALU_SEL_XOR:
            result = src_a ^ src_b;
            break;
        case ALU_SEL_SLL:
            result = src_a << src_b;
            break;
        case ALU_SEL_SRA:
            result = (int) src_a >> (int) src_b;
            break;
        case ALU_SEL_SRL:
            result = src_a >> src_b;
            break;
        case ALU_SEL_LUI:
            result = src_b << 16;
            break;
    }
    return result;
}