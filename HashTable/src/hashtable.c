#include "hashtable.h"

#include <stdlib.h>
#include <string.h>

struct hashtable *hashtable_init(size_t size, size_t (*hash)(char *key))
{
    if (size == 0 || hash == NULL)
    {
        return NULL;
    }

    struct hashtable *h = calloc(1, sizeof(struct hashtable));
    if (h == NULL)
    {
        return NULL;
    }

    h->size = size;
    h->hash = hash;
    h->items = calloc(size, sizeof(struct ht_item));
    for (size_t i = 0; i < size; i++)
    {
        h->items[i] = NULL;
    }
    return h;
}

int hashtable_insert(struct hashtable *ht, struct obj_and_free key,
                     struct obj_and_free value)
{
    if (ht == NULL || ht->hash == NULL || key.obj == NULL || value.obj == NULL)
    {
        return 0;
    }

    size_t pos = ht->hash(key.obj) % ht->size;
    struct ht_item *item = ht->items[pos];

    // If the item does not exist, we create it
    // Otherwise, we change its value
    if (hashtable_get(ht, key.obj) == NULL)
    {
        struct ht_item *new_item = calloc(1, sizeof(struct ht_item));
        new_item->key = key;
        new_item->value = value;
        new_item->next = item;
        ht->items[pos] = new_item;
        return 1;
    }

    // We iterate over the chained list to replace the value of the existing
    // item
    while (item != NULL)
    {
        if (strcmp(item->key.obj, key.obj) == 0)
        {
            item->value = value;
            return 1;
        }
        item = item->next;
    }
    return 0;
}

void *hashtable_get(struct hashtable *ht, char *key)
{
    if (hashtable_contains(ht, key) == 0)
    {
        return NULL;
    }

    struct ht_item *item = ht->items[ht->hash(key) % ht->size];

    while (item != NULL)
    {
        if (strcmp(item->key.obj, key) == 0)
        {
            return item->value.obj;
        }
        item = item->next;
    }
    return NULL;
}

int hashtable_contains(struct hashtable *ht, char *key)
{
    if (ht == NULL || ht->hash == NULL || key == NULL)
    {
        return 0;
    }

    struct ht_item *item = ht->items[ht->hash(key) % ht->size];

    while (item != NULL)
    {
        if (strcmp(item->key.obj, key) == 0)
        {
            return 1;
        }
        item = item->next;
    }
    return 0;
}

int hashtable_remove(struct hashtable *ht, char *key)
{
    if (ht == NULL || ht->hash == NULL || key == NULL)
    {
        return 0;
    }

    size_t pos = ht->hash(key) % ht->size;
    struct ht_item *item = ht->items[pos];
    struct ht_item *prev = item;

    while (item != NULL)
    {
        if (strcmp(item->key.obj, key) == 0)
        {
            // If the first element is the one to free,
            // we have to change the items[pos] element
            if (strcmp(item->key.obj, ht->items[pos]->key.obj) == 0)
            {
                ht->items[pos] = item->next;
            }
            else
            {
                prev->next = item->next;
            }

            // Frees the .obj of the key and the value if they exist
            if (item->key.free != NULL)
            {
                item->key.free(item->key.obj);
            }
            if (item->value.free != NULL)
            {
                item->value.free(item->value.obj);
            }
            free(item);
            return 1;
        }
        prev = item;
        item = item->next;
    }
    return 0;
}

void hashtable_del(struct hashtable *ht)
{
    if (ht == NULL)
    {
        return;
    }

    if (ht->items == NULL)
    {
        free(ht);
        return;
    }

    for (size_t i = 0; i < ht->size; i++)
    {
        struct ht_item *item = ht->items[i];

        while (item != NULL)
        {
            struct ht_item *prev = item;
            if (item->key.free != NULL)
            {
                item->key.free(item->key.obj);
            }
            if (item->value.free != NULL)
            {
                item->value.free(item->value.obj);
            }
            item = item->next;
            free(prev);
        }
    }
    free(ht->items);
    free(ht);
}
