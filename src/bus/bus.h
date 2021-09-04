//
// Created by Ellen7ions on 2021/9/4.
//

#ifndef GEMINISIM_BUS_H
#define GEMINISIM_BUS_H

#include <stdint.h>

typedef struct Bus {
    uint32_t en;
    uint32_t wen;
    uint32_t addr;
    uint32_t wdata;
    uint32_t rdata;
} Bus;

#endif //GEMINISIM_BUS_H
