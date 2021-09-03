//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_CORE_H
#define GEMINISIM_CORE_H

#include "../cpubus.h"
#include "../alu/alu.h"

typedef struct Core {
    RegFile *regfile;
    uint32_t pc;

    void (*core_fetch)(Core *core, InstBus *ibus);

    void (*core_decode)(Core *core, IDBus *idbus);

    void (*core_exe)(Core *core, IDBus *idbus);

    void (*core_lsu)(Core *core, IDBus *idbus, DataBus *dbus);

    void (*core_wb)(Core *core, IDBus *idbus);
} Core;

#endif //GEMINISIM_CORE_H
