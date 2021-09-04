//
// Created by Ellen7ions on 2021/9/4.
//

#ifndef GEMINISIM_MONITOR_H
#define GEMINISIM_MONITOR_H

#include "conf.h"

#include "cpu/regfile.h"
#include "cpu/cpubus.h"
#include "soc/soc.h"

void show_regfile(RegFile *regfile);

void show_trace_signals(IDBus *idbus);

void monitor_top(SoC* soc);

#endif //GEMINISIM_MONITOR_H
