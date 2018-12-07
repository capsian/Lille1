#ifndef HASHMAP_H
#define HASHMAP_H

#include <search.h>

struct hmap_s {
    struct hsearch_data htab;
    size_t size;
    unsigned int bos_local;

    struct hmap_s* next;
};


void table_create(size_t size);
void table_destroy(struct hmap_s* table);
int table_add(struct hmap_s* table, char* key, void* data);
long int table_get(char* key);


#endif
