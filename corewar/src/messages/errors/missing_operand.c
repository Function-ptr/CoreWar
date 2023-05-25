/*
** EPITECH PROJECT, 2022
** missing_operand.c
** File description:
** print missing operand error
*/

#include "corewar.h"

void missing_operand_error(const char *option)
{
    write_void(2, option, my_strlen_const(option));
    write_void(2, ": missing operand\n"
    "Try 'corewar -h' for more information.\n", 57);
}
