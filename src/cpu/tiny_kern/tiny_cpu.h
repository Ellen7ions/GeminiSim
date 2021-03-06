//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_TINY_CPU_H
#define GEMINISIM_TINY_CPU_H

#include "stdint.h"
#include "../regfile.h"
#include "../cpubus.h"
#include "../core/core.h"
#include "soc/soc.h"
#include "def/mips.h"

Core *get_tinycpu();

void tinycpu_run(SoC *soc, void(*hooks[])(SoC *soc), int hook_len);

void tinycpu_fetch(Core *core, IDBus *idbus, Bus *ibus);

void tinycpu_decode(Core *core, IDBus *idbus);

void tinycpu_exe(Core *core, IDBus *idbus);

void tinycpu_lsu(Core *core, IDBus *idbus, Bus *dbus);

void tinycpu_wb(Core *core, IDBus *idbus);

#endif //GEMINISIM_TINY_CPU_H
