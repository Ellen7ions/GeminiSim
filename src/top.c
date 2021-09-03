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

int main() {
    SoC soc;
    soc_init(&soc, 100, "inst.bin", "data.bin");
    soc_run(&soc);
    return 0;
}