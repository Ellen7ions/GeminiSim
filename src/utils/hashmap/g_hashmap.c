//
// Created by Ellen7ions on 2021/9/5.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils/hashmap/g_hashmap.h"

g_hashmap_t *g_hashmap(size_t length) {
    g_hashmap_t *hashmap = (g_hashmap_t *) malloc(sizeof(g_hashmap_t));
    hashmap->length = length;
    hashmap->hash_table = (g_list_t **) malloc(sizeof(g_list_t *) * length);
    int i;
    for (i = 0; i < hashmap->length; i++) {
        hashmap->hash_table[i] = g_list();
    }
    return hashmap;
}

void g_hashmap_show(g_hashmap_t *hashmap, void (*show)(void *data)) {
    int i;
    for (i = 0; i < hashmap->length; i++) {
        printf("[table %d, len = %zu]: ", i, hashmap->hash_table[i]->length);
        g_list_show(*(hashmap->hash_table + i), show);
    }
}

uint32_t g_hashmap_hash(g_hashmap_t *hashmap, const uint8_t *s, size_t len) {
    uint32_t sum = 0;
    int i;
    for (i = 0; i < len; i++) sum = (sum * 17 + s[i]) % hashmap->length;
    return sum;
}

static g_pair_t *g_list_find(g_list_t *list, void *key, size_t size_k) {
    g_node_t *pointer = list->head;
    while (pointer != list->tail) {
        g_pair_t *pair = (g_pair_t *) pointer->data;
        if (pair != NULL && memcmp(pair->key, key, size_k) == 0) {
            return pair;
        }
        pointer = pointer->next;
    }
    return NULL;
}

void g_hashmap_set(g_hashmap_t *hashmap, g_pair_t *pair) {
    uint32_t hashcode = g_hashmap_hash(hashmap, pair->key, pair->size_k);
    g_list_t *list = *(hashmap->hash_table + hashcode);
    g_pair_t *pair1 = g_list_find(list, pair->key, pair->size_k);
    if (pair1 != NULL) {
        pair1->value = pair->value;
        pair1->size_v = pair->size_v;
        return;
    }
    g_list_add(list, list->length, pair, sizeof(g_pair_t));
}

int g_hashmap_get(g_hashmap_t *hashmap, g_pair_t *pair) {
    uint32_t hashcode = g_hashmap_hash(hashmap, pair->key, pair->size_k);
    g_list_t *list = hashmap->hash_table[hashcode];
    g_pair_t *pair_res = g_list_find(list, pair->key, pair->size_k);
    if (pair_res != NULL) {
        pair->value = pair_res->value;
        pair->size_v = pair_res->size_v;
        return 1;
    }
    return 0;
}

static g_pair_t *g_list_find_and_remove(g_list_t *list, void *key, size_t size_k) {
    g_node_t *pointer = list->head;
    while (pointer != list->tail) {
        g_pair_t *pair = (g_pair_t *) pointer->data;
        if (memcmp(pair->key, key, size_k) == 0) {
            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            free(pointer);
            return pair;
        }
        pointer = pointer->next;
    }
    return NULL;
}

void g_hashmap_remove(g_hashmap_t *hashmap, g_pair_t *pair) {
    uint32_t hashcode = g_hashmap_hash(hashmap, pair->key, pair->size_k);
    g_list_t *list = hashmap->hash_table[hashcode];
    g_list_find_and_remove(list, pair->key, pair->size_k);
}

void g_hashmap_free(g_hashmap_t *hashmap) {
    int i;
    for (i = 0; i < hashmap->length; i++) g_list_free(*(hashmap->hash_table + i));
    free(hashmap->hash_table);
}