/*
** EPITECH PROJECT, 2022
** my_strlen_const.c
** File description:
** my_strlen_const
*/

#include "corewar.h"

u64 my_strlen_const(const char *str)
{
    u64 i = 0;
    for (; str[i]; i++);
    return i;
}
