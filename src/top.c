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
#include "soc/soc.h"
#include "cpu/tiny_kern/tiny_cpu.h"

int main() {
    SoC soc;
    soc_init(
            &soc,
            15,
            get_tinycpu,
            "./software/test1/trace.bin",
            "./software/test1/disk.bin"
    );
    soc_run(&soc, tinycpu_run);
    return 0;
}