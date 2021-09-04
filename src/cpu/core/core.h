//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_CORE_H
#define GEMINISIM_CORE_H

#include "cpu/regfile.h"
#include "../cpubus.h"
#include "../alu/alu.h"

typedef struct Core {
    RegFile *regfile;
    uint32_t pc;

    // void (*core_fetch)(struct Core *core, IDBus *idbus, InstBus *ibus);
    //
    // void (*core_decode)(struct Core *core, IDBus *idbus);
    //
    // void (*core_exe)(struct Core *core, IDBus *idbus);
    //
    // void (*core_lsu)(struct Core *core, IDBus *idbus, DataBus *dbus);
    //
    // void (*core_wb)(struct Core *core, IDBus *idbus);
} Core;

#endif //GEMINISIM_CORE_H
