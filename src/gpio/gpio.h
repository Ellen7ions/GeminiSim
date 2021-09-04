//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_GPIO_H
#define GEMINISIM_GPIO_H

#include <stdint.h>
#include "bus/bus.h"

/**
 *
 * (en)/addr/wen/wdata ----> select ----> led
 *
 */

typedef struct GPIO {
    uint16_t led;
} GPIO;

GPIO *get_gpio();

uint32_t gpio_top(GPIO *gpio, Bus *bus);

uint32_t gpio_led_update(GPIO *gpio, uint8_t wen, uint32_t wdata);

void gpio_led_show(GPIO *gpio);

#endif //GEMINISIM_GPIO_H
