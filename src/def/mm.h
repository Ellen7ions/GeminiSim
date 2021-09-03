//
// Created by Ellen7ions on 2021/9/3.
//

/**
 * memory mapping
 */

#ifndef GEMINISIM_MM_H
#define GEMINISIM_MM_H

// GPIO LED 0xbfaf_f000
#define LED_ADDR    0xf000

#define GPIO_MASK   0xffff0000
#define IS_GPIO(x)  ((x & GPIO_MASK) == 0xbfaf0000)



#endif //GEMINISIM_MM_H
