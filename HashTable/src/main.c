#include <stdio.h>

#include "hashtable.h"

size_t hash(char *str)
{
    size_t hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void print_key_pair(struct hashtable *ht, char *key)
{
    if (hashtable_contains(ht, key))
    {
        printf("Key: %s -> Value: %s\n", key, (char *)hashtable_get(ht, key));
    }
}

int main(void)
{
    struct hashtable *ht = hashtable_init(5, hash);
    if (!ht)
    {
        return 1;
    }
    struct obj_and_free key = { .obj = "MySuperKey", .free = NULL };
    struct obj_and_free value = { .obj = "ILoveC", .free = NULL };

    struct obj_and_free key2 = { .obj = "AAAAAA", .free = NULL };
    struct obj_and_free value2 = { .obj = "bbb", .free = NULL };

    struct obj_and_free key3 = { .obj = "AAAAAA", .free = NULL };
    struct obj_and_free value3 = { .obj = "555", .free = NULL };

    struct obj_and_free key4 = { .obj = NULL, .free = NULL };
    struct obj_and_free value4 = { .obj = NULL, .free = NULL };

    if (!hashtable_insert(ht, key, value))
    {
        free(ht);
        return 1;
    }

    if (!hashtable_insert(ht, key2, value2))
    {
        hashtable_del(ht);
        return 1;
    }

    /*if (!hashtable_insert(ht, key4, value4))
    {
        hashtable_del(ht);
        return 1;
    }*/

    print_key_pair(ht, "MySuperKey");
    print_key_pair(ht, "AAAAAA");
    if (!hashtable_insert(ht, key3, value3))
    {
        hashtable_del(ht);
        return 1;
    }
    print_key_pair(ht, "MySuperKey");
    print_key_pair(ht, "AAAAAA");
    hashtable_remove(ht, "MySuperKey");
    print_key_pair(ht, "MySuperKey");

    hashtable_del(ht);
    return 0;
}
