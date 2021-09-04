//
// Created by Ellen7ions on 2021/9/3.
//

/*
 *
 *          cpu
 *           |
 *bus   -------------
 *     |    |       |
 *   gpio  i-ram  d-ram
 *
 */

#include "stdio.h"

#include "soc/soc.h"
#include "debug/monitor.h"

int main() {
    SoC soc;
    soc_init(&soc, 5, "./software/test1/trace.bin", "data.bin");
    soc_run(&soc, monitor_top);
    return 0;
}