//
// Created by Ellen7ions on 2021/9/5.
//

#include "g_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

g_list_t *g_list() {
    g_list_t *list = (g_list_t *) malloc(sizeof(g_list_t));
    list->length = 0;
    list->head = (g_node_t *) malloc(sizeof(g_node_t));
    list->tail = (g_node_t *) malloc(sizeof(g_node_t));
    list->head->next = list->tail;
    list->head->prev = NULL;
    list->tail->prev = list->head;
    list->tail->next = NULL;
    list->head->data = NULL;
    list->tail->data = NULL;
    return list;
}

void g_list_show(g_list_t *list, void(*show)(void *data)) {
    g_node_t *pointer = list->head->next;
    while (pointer != list->tail) {
        show(pointer->data);
        printf("->");
        pointer = pointer->next;
    }
    printf("\n");
}

// uint32_t g_list_find(g_list_t *g_list, void *data, size_t size) {
//     g_node_t *pointer = g_list->head;
//     while (pointer != g_list->tail && (memcmp(data, pointer->data, size) != 0)) {
//         pointer = pointer->next;
//     }
//     return pointer != NULL;
// }

g_node_t *g_list_locate(g_list_t *g_list, int index) {
    g_node_t *pointer;
    int count;
    if (index >= 0) {
        pointer = g_list->head;
        count = -1;
        while (count != index) {
            pointer = pointer->next;
            count++;
        }
        if (pointer == NULL) return NULL;
    } else {
        pointer = g_list->tail;
        count = 0;
        while (count != index) {
            pointer = pointer->prev;
            count--;
        }
        if (pointer == NULL) return NULL;
    }
    return pointer;
}

/**
 * [4, 1, 3, 2, 0, 9]
 *  0, 1, 2, 3, 4, 5
 *  -6,-5,-4,-3,-2,-1
 * @param g_list
 * @param index
 * @return
 */
void *g_list_get(g_list_t *g_list, int index) {
    g_node_t *pointer;
    pointer = g_list_locate(g_list, index);
    return pointer == NULL ? NULL : pointer->data;
}

void g_list_add(g_list_t *g_list, int index, void *data, size_t size) {
    if (data == NULL) {
        return;
    }
    g_node_t *pointer;
    pointer = g_list_locate(g_list, index);
    if (pointer != NULL) {
        g_list->length++;
        void *dup_data = malloc(size);
        // printf("!\n");
        memcpy(dup_data, data, size);
        g_node_t *new_node = (g_node_t *) malloc(sizeof(g_node_t));
        new_node->prev = pointer->prev;
        new_node->next = pointer;
        pointer->prev = new_node;
        new_node->prev->next = new_node;
        new_node->data = dup_data;
        new_node->size = size;
    }
}

void g_list_remove(g_list_t *g_list, int index) {
    g_node_t *pointer = g_list_locate(g_list, index);
    if (pointer != NULL) {
        g_list->length--;

        pointer->prev->next = pointer->next;
        pointer->next->prev = pointer->prev;
        free(pointer);
    }
}

void g_list_free(g_list_t *g_list) {
    g_node_t *pointer = g_list->head;
    while (pointer->next != g_list->tail) {
        g_node_t *temp = pointer->next;
        pointer->next = pointer->next->next;
        free(temp);
    }
    free(g_list->head);
    free(g_list->tail);
    // free(g_list);
}