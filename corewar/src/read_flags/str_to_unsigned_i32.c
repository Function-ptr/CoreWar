/*
** EPITECH PROJECT, 2022
** str_to_unsigned_i32.c
** File description:
** str to unsigned i32. -1 if error
*/

#include "corewar.h"

i32 str_to_unsigned_i32(const char *str)
{
    i32 result = 0;
    for (u32 i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result *= 10;
        result += str[i] - '0';
    }
    return result;
}
