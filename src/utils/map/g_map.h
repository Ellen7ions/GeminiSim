//
// Created by Ellen7ions on 2021/9/5.
//

#ifndef GEMINISIM_G_MAP_H
#define GEMINISIM_G_MAP_H

#include <stdint.h>
#include "g_pair.h"

typedef struct g_map_t {
    void (*g_map_set)(void *handler, g_pair_t *pair);

    void (*g_map_get)(void *handler, g_pair_t *pair);

    void (*g_map_remove)(void *handler, g_pair_t *pair);

    void (*g_map_free)(void *handler, g_pair_t *pair);
} g_map_t;

#endif //GEMINISIM_G_MAP_H
