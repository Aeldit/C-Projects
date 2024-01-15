#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

struct obj_and_free
{
    void *obj;
    void (*free)(void *obj);
};

struct ht_item
{
    struct obj_and_free key;
    struct obj_and_free value;
    struct ht_item *next;
};

struct hashtable
{
    struct ht_item **items;
    size_t size;
    size_t (*hash)(char *key);
};

struct hashtable *hashtable_init(size_t size, size_t (*hash)(char *key));
void hashtable_del(struct hashtable *ht);
int hashtable_insert(struct hashtable *ht, struct obj_and_free key,
                     struct obj_and_free value);
int hashtable_remove(struct hashtable *ht, char *key);
void *hashtable_get(struct hashtable *ht, char *key);
int hashtable_contains(struct hashtable *ht, char *key);

#endif /* !HASHTABLE_H */
