/*
** EPITECH PROJECT, 2022
** duplicate_option_error.c
** File description:
** print duplicate option error
*/

#include "corewar.h"

void duplicate_option_error(const char *option)
{
    write_void(2, option, my_strlen_const(option));
    write_void(2, ": duplicate option\n"
    "Try 'corewar -h' for more information.\n", 58);
}
