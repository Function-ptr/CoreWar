/*
** EPITECH PROJECT, 2022
** invalid_operand.c
** File description:
** print invalid operand error
*/

#include "corewar.h"

void invalid_operand_error(const char *option)
{
    write_void(2, option, my_strlen_const(option));
    write_void(2, ": invalid operand\n"
    "Try 'corewar -h' for more information.\n", 57);
}
