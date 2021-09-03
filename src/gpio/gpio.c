//
// Created by Ellen7ions on 2021/9/3.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "gpio.h"
#include "../def/mm.h"

GPIO *get_gpio() {
    return (GPIO*)malloc(sizeof(GPIO));
}

uint32_t gpio_top(GPIO *gpio, uint32_t addr, uint8_t wen, uint32_t wdata) {
    if ((addr & 0xffff) == 0xf000) {
        return gpio_led_update(gpio, wen, wdata);
    }
    return 0;
}

uint32_t gpio_led_update(GPIO *gpio, uint8_t wen, uint32_t wdata) {
    if (wen) {
        gpio->led = wdata & 0xffff;
    }
    return gpio->led;
}

void gpio_led_show(GPIO *gpio) {
    uint16_t i = 15;
    for (i; i >= 1; i--) {
        if (((gpio->led & (1 << i)) >> i) == 1) {
            printf("[*] ");
        } else {
            printf("[ ] ");
        }
    }
    printf("\n");
}