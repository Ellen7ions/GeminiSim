//
// Created by Ellen7ions on 2021/9/6.
//

#ifndef GEMINISIM_G_PAIR_H
#define GEMINISIM_G_PAIR_H

#include <stdint.h>

typedef struct g_pair_t {
    void *key;
    size_t size_k;
    void *value;
    size_t size_v;
} g_pair_t;

g_pair_t *g_pair(void *key, size_t size_k, void *value, size_t size_v);

#endif //GEMINISIM_G_PAIR_H
