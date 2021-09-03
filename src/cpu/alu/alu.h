//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_ALU_H
#define GEMINISIM_ALU_H

#include "stdint.h"

#define ALU_SEL_NOP     0
#define ALU_SEL_ADD     1
#define ALU_SEL_SUB     2
#define ALU_SEL_SLT     3
#define ALU_SEL_SLTU    4
#define ALU_SEL_DIV     5
#define ALU_SEL_DIVU    6
#define ALU_SEL_MULT    7
#define ALU_SEL_MULTU   8
#define ALU_SEL_AND     9
#define ALU_SEL_MUL     10
#define ALU_SEL_NOR     54
#define ALU_SEL_OR      56
#define ALU_SEL_XOR     57
#define ALU_SEL_SLL     58
#define ALU_SEL_SRA     59
#define ALU_SEL_SRL     60
#define ALU_SEL_LUI     61
#define ALU_SEL_MTHI    62
#define ALU_SEL_MTLO    63

uint32_t alu_cal(uint32_t alu_op_code, uint32_t src_a, uint32_t src_b);

#endif //GEMINISIM_ALU_H
