//
// Created by Ellen7ions on 2021/9/3.
//

/*
 *
 *          cpu
 *           |
 *bus   -------------
 *     |    |       |
 *   gpio  i-ram  d-ram
 *
 */
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "soc/soc.h"
#include "cpu/tiny_kern/tiny_cpu.h"

#include "utils/list/g_list.h"
#include "utils/map/g_map.h"
#include "utils/map/g_pair.h"
#include "utils/hashmap/g_hashmap.h"

void test_soc() {
    SoC soc;
    soc_init(
            &soc,
            15,
            get_tinycpu,
            "./software/test1/trace.bin",
            "./software/test1/disk.bin"
    );
    soc_run(&soc, tinycpu_run);
}

void test_g_list() {
    g_list_t *list = g_list();
    int i;
    for (i = 0; i < 5; i++) g_list_add(list, 0, &i, sizeof(i));
    while (list->length) {
        for (i = 0; i < list->length; i++) printf("%d ", *(int *) g_list_get(list, i));
        g_list_remove(list, -1);
        printf("\n");
    }
    g_list_free(list);
}

void hashmap_show(void *data) {
    g_pair_t *pair = (g_pair_t *) data;
    if (data != NULL) {
        printf("{key = %s, value = %d}", (char *) pair->key, *((int *) pair->value));
    } else {
        printf("[x]");
    }
}

char *str_random() {
    // srand((unsigned) time(NULL));
    char *s = (char *) malloc(7);
    for (int i = 0; i < 6; i++) {
        int r = rand() % 26;
        *(s + i) = r + 'a';
    }
    *(s + 7) = '\0';
    return s;
}

void test_g_hashmap(int epoch) {
    g_hashmap_t *hashmap = g_hashmap(5);
    int *a;
    g_pair_t *pair;

    int i;
    for (i = 0; i < epoch; i++) {
        a = (int *) malloc(sizeof(int));
        *a = i;
        pair = g_pair(str_random(), 7, a, sizeof(int));
        g_hashmap_set(hashmap, pair);
    }

    g_hashmap_show(hashmap, hashmap_show);

    g_hashmap_free(hashmap);
}

int main() {
    // test_g_list();
    test_g_hashmap(200);
    return 0;
}