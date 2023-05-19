/*
** EPITECH PROJECT, 2022
** champion_file.c
** File description:
** read champion_file name option
*/

#include "corewar.h"

function_status_t read_champion_file(__attribute__((unused)) i32 argc,
    const char **argv, i32 *argi, options_t *options)
{
    if (options->champions.len >= MAX_CHAMPIONS) {
        too_many_champions_error();
        return ERROR;
    }

    options->champions.champions[options->champions.len++].name = argv[(*argi)];
    return SUCCESS;
}
