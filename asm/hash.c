/*
** EPITECH PROJECT, 2023
** hash.c
** File description:
** hashing function
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

const char *keys[NUM_KEYS] = {"live", "ld", "st", "add", "sub", "and",
    "or", "xor", "zjmp", "ldi", "sti", "fork",
    "lld", "lldi", "lfork", "aff"};

unsigned long hash(const char *str)
{
    for (unsigned long i = 0; i < NUM_KEYS; ++i) {
        if (my_strcmp(keys[i], str) == 0)
            return i;
    }

    return TABLE_SIZE;
}

unsigned long hash_string(string_t str)
{
    char *dup = my_strndup(str.str, (int)str.len);
    for (unsigned long i = 0; i < NUM_KEYS; ++i) {
        if (my_strcmp(keys[i], dup) == 0) {
            free(dup);
            return i;
        }
    }
    free(dup);
    return TABLE_SIZE;
}

op_t ptr lookup_string(hash_table ptr table, string_t key)
{
    unsigned long index = hash_string(key);
    if (index == TABLE_SIZE) return NULL;
    Entry ptr bucket = table->buckets[index];
    char *dup = my_strndup(key.str, (int)key.len);
    while (bucket) {
        if (my_strcmp(bucket->key, dup) == 0) {
            free(dup);
            return bucket->value;
        }
        bucket = bucket->next;
    }
    free(dup);
    return NULL;
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
