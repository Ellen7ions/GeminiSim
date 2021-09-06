//
// Created by Ellen7ions on 2021/9/5.
//

#ifndef GEMINISIM_G_LIST_H
#define GEMINISIM_G_LIST_H

#include <stdint.h>

typedef struct g_node_t {
    struct g_node_t *next;
    struct g_node_t *prev;
    void *data;
    size_t size;
} g_node_t;

typedef struct g_list_t {
    g_node_t *head;
    g_node_t *tail;
    size_t length;
} g_list_t;

g_list_t *g_list();

void g_list_show(g_list_t* list, void (*show)(void* data));

g_node_t *g_list_locate(g_list_t *g_list, int index);

// uint32_t g_list_find(g_list_t *g_list, void *data, size_t size);

void *g_list_get(g_list_t *g_list, int index);

void g_list_add(g_list_t *g_list, int index, void *data, size_t size);

void g_list_remove(g_list_t *g_list, int index);

void g_list_free(g_list_t *g_list);

#endif //GEMINISIM_G_LIST_H
