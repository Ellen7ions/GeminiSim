//
// Created by Ellen7ions on 2021/9/5.
//

#ifndef GEMINISIM_GEMINI_H
#define GEMINISIM_GEMINI_H

#include "cpu/core/core.h"
#include "soc/soc.h"

#include "context.h"

void gemini_run(SoC *soc, void(*hooks[])(SoC *soc), int hook_len);

#endif //GEMINISIM_GEMINI_H
