/*
** EPITECH PROJECT, 2022
** dump.c
** File description:
** read dump option
*/

#include "corewar.h"

function_status_t read_dump_flag(i32 argc, const char **argv,
    i32 *argi, options_t *options)
{
    if (my_strcmp(argv[*argi], DUMP_FLAG) != 0)
        return FAILURE;
    if (*argi + 1 >= argc) {
        missing_operand_error(DUMP_FLAG);
        return ERROR;
    }
    if (options->dump != -1) {
        duplicate_option_error(DUMP_FLAG);
        return ERROR;
    }
    options->dump = str_to_unsigned_i32(argv[++(*argi)]);
    if (options->dump == -1) {
        invalid_operand_error(DUMP_FLAG);
        return ERROR;
    }
    return SUCCESS;
}
