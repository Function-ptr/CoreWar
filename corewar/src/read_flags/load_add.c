/*
** EPITECH PROJECT, 2022
** load_add.c
** File description:
** read load_address option
*/

#include "corewar.h"

function_status_t read_load_add_flag(i32 argc, const char **argv, i32 *argi, options_t *options)
{
    if (my_strcmp(argv[*argi], LOAD_ADD_FLAG) != 0)
        return FAILURE;
    if (*argi + 1 >= argc) {
        missing_operand_error(LOAD_ADD_FLAG);
        return ERROR;
    }
    if (options->champions.len >= MAX_CHAMPIONS) {
        too_many_champions_error();
        return ERROR;
    }
    if (*argi + 2 >= argc) {
        missing_operand_error(LOAD_ADD_FLAG);
        return ERROR;
    }
    i32 input_add = str_to_unsigned_i32(argv[++(*argi)]);
    if (input_add == -1 || input_add % MEM_SIZE != 0) {
        invalid_operand_error(LOAD_ADD_FLAG);
        return ERROR;
    }
    for (u32 i = 0; i < options->champions.len; i++) {
        if (options->champions.champions[i].address == input_add) {
            duplicate_load_add_error(LOAD_ADD_FLAG);
            return ERROR;
        }
    }
    options->champions.champions[options->champions.len].address = input_add;
    return SUCCESS;
}
