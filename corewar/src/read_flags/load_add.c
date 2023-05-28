/*
** EPITECH PROJECT, 2022
** load_add.c
** File description:
** read load_address option
*/

#include "corewar.h"

bool is_error_read_load_add_flag(i32 argc, i32 *argi, options_t *options)
{
    if (*argi + 1 >= argc) {
        missing_operand_error(LOAD_ADD_FLAG);
        return true;
    }
    if (options->champions.len >= MAX_CHAMPIONS) {
        too_many_champions_error();
        return true;
    }
    if (*argi + 2 >= argc) {
        missing_operand_error(LOAD_ADD_FLAG);
        return true;
    }
    return false;
}

function_status_t read_load_add_flag(i32 argc, const char **argv,
    i32 *argi, options_t *options)
{
    if (my_strcmp(argv[*argi], LOAD_ADD_FLAG) != 0)
        return FAILURE;

    if (is_error_read_load_add_flag(argc, argi, options))
        return ERROR;

    i32 input_add = str_to_unsigned_i32(argv[++(*argi)]);
    if (input_add == -1 || MEM_SIZE / input_add * input_add != MEM_SIZE) {
        invalid_operand_error(LOAD_ADD_FLAG);
        return true;
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
