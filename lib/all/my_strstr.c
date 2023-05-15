/*
** EPITECH PROJECT, 2022
** my_strstr.c
** File description:
** Reproduce the behiavor of the strstr function
*/

#include <stddef.h>

int is_needle(char *str, char const *to_find)
{
    for (int i = 0; str[i] != '\0' && to_find[i] != '\0'; i++) {
        if (str[i] != to_find[i])
            return (0);
    }
    return (1);
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;

    if (to_find == NULL || *to_find == 0)
        return (str);
    for (; str[i] != '\0'; i++) {
        int test = is_needle(&str[i], to_find);
        if (test)
            return (&str[i]);
    }
    return (NULL);
}
