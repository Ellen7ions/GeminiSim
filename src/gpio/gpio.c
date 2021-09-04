//
// Created by Ellen7ions on 2021/9/3.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "gpio.h"

GPIO *get_gpio() {
    GPIO * gpio = (GPIO*)malloc(sizeof(GPIO));
    gpio->led = 0;
    return gpio;
}

uint32_t gpio_top(GPIO *gpio, Bus *bus) {
    if ((bus->addr & 0xffff) == 0xf000) {
        return gpio_led_update(gpio, bus->wen, bus->wdata);
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
    int32_t i = 15;
    for (i; i >= 0; i--) {
        if (((gpio->led & (1 << i)) >> i) == 1) {
            printf("[*] ");
        } else {
            printf("[ ] ");
        }
    }
    printf("\n");
}