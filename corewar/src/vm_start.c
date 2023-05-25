/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

void vm_run_champion(champion_t *champion, options_t *options)
{
    // TODO: implement op and cooldown for the champion
}

void champions_loop(champions_list_t *champions, options_t *options)
{
    for (u32 i = 0; i < champions->len; i++) {
        if (champions->champions[i].alive)
            vm_run_champion(&champions->champions[i], options);
    }
}

int vm_run(options_t *options)
{
    while (options->champions.len > 0) {
        champions_loop(&options->champions, options);
    }
}
