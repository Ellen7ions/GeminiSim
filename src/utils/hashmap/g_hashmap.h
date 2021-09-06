//
// Created by Ellen7ions on 2021/9/5.
//

#ifndef GEMINISIM_G_HASHMAP_H
#define GEMINISIM_G_HASHMAP_H

#include "utils/map/g_map.h"
#include "utils/list/g_list.h"

typedef struct g_hashmap {
    g_list_t **hash_table;
    size_t length;
} g_hashmap_t;

g_hashmap_t *g_hashmap(size_t length);

void g_hashmap_show(g_hashmap_t *hashmap, void (*show)(void *data));

uint32_t g_hashmap_hash(g_hashmap_t *hashmap, const uint8_t *s, size_t len);

void g_hashmap_set(g_hashmap_t *hashmap, g_pair_t *pair);

int g_hashmap_get(g_hashmap_t *hashmap, g_pair_t *pair);

void g_hashmap_remove(g_hashmap_t *hashmap, g_pair_t *pair);

void g_hashmap_free(g_hashmap_t *hashmap);

#endif //GEMINISIM_G_HASHMAP_H
