//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_CORE_H
#define GEMINISIM_CORE_H

#include "cpu/regfile.h"

typedef struct Core {
    RegFile *regfile;
    uint32_t pc;

} Core;

#endif //GEMINISIM_CORE_H
