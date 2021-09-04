//
// Created by Ellen7ions on 2021/9/4.
//

#include <stdio.h>
#include "monitor.h"

#define SHOW_HEX(NAME, VALUE) printf("%s\t=\t0x%08x\n", #NAME, VALUE);

#define show_line_default() show_line(32)

static void show_line(int len) {
    int i;
    for (i = 0; i < len; i++) printf("=");
    printf("\n");
}

void show_regfile(RegFile *regfile) {
    show_line_default();
    int i;
    for (i = 0; i < 32; i++) printf("$%d\t=\t0x%x\n", i, regfile->regs[i]);
    show_line_default();
}

void show_trace_signals(IDBus *idbus) {
    show_line_default();
    SHOW_HEX(pc, idbus->pc);
    SHOW_HEX(inst, idbus->inst);
    show_line_default();
}

void show_gpio_led(SoC *soc) {
    show_line_default();
    gpio_led_show(soc->gpio);
    show_line_default();
}

void monitor_top(SoC *soc) {
#ifdef DEBUG_SHOW_TRACE
    show_trace_signals(soc->idbus);
#endif

#ifdef DEBUG_SHOW_REGFILE
    show_regfile(soc->cpu->regfile);
#endif
}