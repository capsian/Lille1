#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "interprete/hashmap.h"
#include "interprete/environnement.h"
#include "utils.h"

void table_create(size_t size) {

    sprintf(tmp_log,"table_create ... enter: size:%ld",size);
    mlog(tmp_log,2,0);
    /*mlog("table_create1: display env :",2,0);
    display_env();
    display_stack();*/

    struct hmap_s* table = malloc(sizeof(struct hmap_s));
    assert(table != NULL);

    table->htab = (struct hsearch_data){0};
    hcreate_r(size*1.5, &table->htab);
    table->size = size;
    table->bos_local = tos;
    table->next = NULL;

    if (env_global == NULL) {
        env_global = table;
        env_local = env_global;
    }
    else {
        table->next = env_local;
        env_local = table;
    }
}

void destroy_entries_stack(struct hmap_s* tab) {

    struct value_s *tmp = NULL;

    while (tos != tab->bos_local) {
        mlog(" ... destroy_entries_stack ...",2,0);

        tmp = pop_stack();

        if (tmp != NULL)
            free(tmp);
    }
}

void table_destroy(struct hmap_s* table) {

    mlog("table_destroy enter ....", 2,0);

    assert(table != NULL);
    assert(env_global != NULL);

    struct hmap_s* iter = env_local;
    struct hmap_s* last;

    /* check if is the first one */
    if (env_local == table) {
        env_local = env_local->next;
    }else{

        while (iter != NULL) {

            if (iter == table) {
                last->next = iter->next;
                break;
            }

            last = iter;
            iter = iter->next;
        }
    }
    destroy_entries_stack(table);
    hdestroy_r(&table->htab);
    free(table);
    return;
}

int table_add(struct hmap_s* table, char* key, void* data) {

    sprintf(tmp_log, "table_add().... offset = %ld, key:%s, env=%p", (long int) data, key, (void*) table);
    mlog(tmp_log,2,0);

    unsigned n = 0;
    ENTRY e, *ep;

    e.key = key;
    e.data = data;
    n = hsearch_r(e, ENTER, &ep, &table->htab);

    return n;
}

long int table_get(char* key) {

    sprintf(tmp_log, "table_get().... enter, searching for key:%s", key);
    mlog(tmp_log,2,0);
    display_stack();
    display_env();

    unsigned n = 0;
    ENTRY e, *ep;

    e.key = key;

    assert(env_local != NULL);
    assert(env_global != NULL);

    /* FOUND THE KEY IN ENV_LOCAL */
    if ((n = hsearch_r(e, FIND, &ep, &env_local->htab)) != 0) {
        mlog("table_get().... in env_local",2,0);
    }
    /* FOUND IN THE GOLBAL_ENV */
    else if ((n = hsearch_r(e, FIND, &ep, &env_global->htab)) != 0) {
        mlog("table_get().... in env_global",2,0);
    }

    /* SHOULD NEVER HAPPEN */
    if (!n)
        mlog("table_get().... SHOULD NEVER HAPPEN !!! NOT FOUND IN ENV_LOCAL && ENV_GOBAL !!",0,1);


    sprintf(tmp_log, "table_get().... ep->data:%ld", (long int) ep->data);
    mlog(tmp_log,2,0);

    return (long int) ep->data;
}