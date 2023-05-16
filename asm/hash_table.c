/*
** EPITECH PROJECT, 2023
** hasmap.c
** File description:
** hash table
*/
/*
 _____               __      __
|  __ \              \ \    / /
| |__) |  __ _  ___   \ \  / /   ___   __ _   __ _  _ __
|  ___/  / _` |/ __|   \ \/ /   / _ \ / _` | / _` || '_ \
| |     | (_| |\__ \    \  /   |  __/| (_| || (_| || | | |
|_|      \__,_||___/     \/     \___| \__, | \__,_||_| |_|
                                       __/ |
                                      |___/
*/

#include "asm.h"
#include "my.h"

hash_table *create_table(void)
{
    hash_table *table = malloc(sizeof(hash_table));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void insert(hash_table *const table, const char *const key,
    const op_t *const value)
{
    unsigned long index = hash(key);
    Entry *entry = malloc(sizeof(Entry));
    if (!entry)
        return;
    entry->key = my_strdup(key);
    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
}

op_t* lookup(hash_table *const table, const char *const key)
{
    unsigned long index = hash(key);
    Entry *bucket = table->buckets[index];
    while (bucket) {
        if (my_strcmp(bucket->key, key) == 0) {
            return bucket->value;
        }
        bucket = bucket->next;
    }
    return NULL;
}

void delete(hash_table *const table, const char *const key)
{
    unsigned long index = hash(key);
    Entry *bucket = table->buckets[index];
    Entry *prev = NULL;

    while (bucket) {
        if (my_strcmp(bucket->key, key) != 0) {
            prev = bucket;
            bucket = bucket->next;
            continue;
        }

        if (prev) {
            prev->next = bucket->next;
        } else {
            table->buckets[index] = bucket->next;
        }

        free(bucket->key); free(bucket);
        return;
    }
}

void free_table(hash_table *const table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *bucket = table->buckets[i];
        while (bucket) {
            Entry *next = bucket->next;
            free(bucket->key);
            free(bucket);
            bucket = next;
        }
    }
    free(table);
}

/*
─▄▀▀▀▀▄─█──█────▄▀▀█─▄▀▀▀▀▄─█▀▀▄
─█────█─█──█────█────█────█─█──█
─█────█─█▀▀█────█─▄▄─█────█─█──█
─▀▄▄▄▄▀─█──█────▀▄▄█─▀▄▄▄▄▀─█▄▄▀

─────────▄██████▀▀▀▀▀▀▄
─────▄█████████▄───────▀▀▄▄
──▄█████████████───────────▀▀▄
▄██████████████─▄▀───▀▄─▀▄▄▄──▀▄
███████████████──▄▀─▀▄▄▄▄▄▄────█
█████████████████▀█──▄█▄▄▄──────█
███████████──█▀█──▀▄─█─█─█───────█
████████████████───▀█─▀██▄▄──────█
█████████████████──▄─▀█▄─────▄───█
█████████████████▀███▀▀─▀▄────█──█
████████████████──────────█──▄▀──█
████████████████▄▀▀▀▀▀▀▄──█──────█
████████████████▀▀▀▀▀▀▀▄──█──────█
▀████████████████▀▀▀▀▀▀──────────█
──███████████████▀▀─────█──────▄▀
──▀█████████████────────█────▄▀
────▀████████████▄───▄▄█▀─▄█▀
──────▀████████████▀▀▀──▄███
──────████████████████████─█
─────████████████████████──█
────████████████████████───█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████▄▄▄▄▄█

─────────────█─────█─█──█─█───█
─────────────█─────█─█──█─▀█─█▀
─────────────█─▄█▄─█─█▀▀█──▀█▀
─────────────██▀─▀██─█──█───█
*/
