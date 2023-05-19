/*
** EPITECH PROJECT, 2022
** read_flags.c
** File description:
** read command line options
*/

#include "corewar.h"

void update_prog_address_and_nbs(options_t *options)
{
    i32 prog_nb = 1;
    i32 prog_address = 0;
    
    for (u32 champion = 0; champion < options->champions.len; champion++) {
        if (options->champions.champions[champion].number == -1) {
            options->champions.champions[champion].number = prog_nb++;
        }
        // TODO: give an adress to the champion if it doesn't have one.
        // Champions need to be as far away from each other as possible.
    }
}

void read_flags(i32 argc, const char **argv, options_t *options)
{
    function_status_t (*argument_functions[])
        (i32, const char **, i32 *, options_t *) = {
        &read_dump_flag,
        &read_prog_nb_flag,
        &read_load_add_flag,
        &read_champion_file
    };
    for (i32 argi = 1; argi < argc; argi++) {
        function_status_t status = FAILURE;
        for (u32 i = 0; i < 4 && status == FAILURE; i++)
            status = argument_functions[i](argc, argv, &argi, options);
        if (status == ERROR) {
            options->valid = false;
            return;
        }
    }
    if (options->champions.len < 2) {
        not_enough_champions_error();
        options->valid = false;
        return;
    }
    update_prog_address_and_nbs(options);
}
