//
// Created by Ellen7ions on 2021/9/6.
//

#include "g_pair.h"
#include <stdlib.h>

g_pair_t *g_pair(void *key, size_t size_k, void *value, size_t size_v) {
    g_pair_t *g_pair = (g_pair_t*) malloc(sizeof(g_pair_t));
    g_pair->key = key;
    g_pair->size_k = size_k;
    g_pair->value = value;
    g_pair->size_v = size_v;
    return g_pair;
}