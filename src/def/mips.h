//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_MIPS_H
#define GEMINISIM_MIPS_H

#define ZERO    0	/* wired zero */
#define AT	    1	/* assembler temp  - uppercase because of ".set at" */
#define V0	    2	/* return value */
#define V1	    3
#define A0	    4	/* argument registers */
#define A1	    5
#define A2	    6
#define A3	    7
#define T0	    8	/* caller saved */
#define T1	    9
#define T2	    10
#define T3	    11
#define T4	    12
#define T5	    13
#define T6	    14
#define T7	    15
#define S0	    16	/* callee saved */
#define S1	    17
#define S2	    18
#define S3	    19
#define S4	    20
#define S5	    21
#define S6	    22
#define S7	    23
#define T8	    24	/* caller saved */
#define T9	    25
#define Jp	    25	/* PIC jump register */
#define K0	    26	/* kernel scratch */
#define K1	    27
#define GP	    28	/* global pointer */
#define SP	    29	/* stack pointer */
#define FP	    30	/* frame pointer */
#define S8	    30	/* same like fp! */
#define RA	    31	/* return address */

#define ADDIU_OP_CODE   0b001001
#define SPECIAL_OP_CODE 0b000000

#define ADD_FUNCT       0b100000
#define ADDU_FUNCT      0b100001
#define SUB_FUNCT       0b100010


#endif //GEMINISIM_MIPS_H
