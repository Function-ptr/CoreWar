/*
** EPITECH PROJECT, 2022
** prog_nb.c
** File description:
** read prog_number option
*/

#include "corewar.h"

bool is_error_prog_nb_flag(i32 argc, const char **argv,
    i32 *argi, options_t *options)
{
    if (*argi + 1 >= argc) {
        missing_operand_error(PROG_NB_FLAG);
        return true;
    }
    if (options->champions.len >= MAX_CHAMPIONS) {
        too_many_champions_error();
        return true;
    }
    if (*argi + 2 >= argc) {
        missing_operand_error(PROG_NB_FLAG);
        return true;
    }
    if ((options->champions.champions[options->champions.len].number =
        str_to_unsigned_i32(argv[++(*argi)])) <= 0) {
        invalid_operand_error(PROG_NB_FLAG);
        return true;
    }
    return false;
}

function_status_t read_prog_nb_flag(i32 argc, const char **argv,
    i32 *argi, options_t *options)
{
    if (my_strcmp(argv[*argi], PROG_NB_FLAG) != 0)
        return FAILURE;

    if (is_error_prog_nb_flag(argc, argv, argi, options))
        return ERROR;

    for (u32 i = 0; i < options->champions.len; i++) {
        if (options->champions.champions[i].number ==
            options->champions.champions[options->champions.len].number) {
            duplicate_prog_nb_error(PROG_NB_FLAG);
            return ERROR;
        }
    }

    return SUCCESS;
}
