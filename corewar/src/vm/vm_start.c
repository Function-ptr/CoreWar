/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

void champion_cycles_loop(options_t *options, u32 cham)
{
    for (u32 i = 0; i < REG_NUMBER; i++) {
        if (my_strcmp(options->champions.champions[cham].op.mnemonique,
            op_tab[i].mnemonique) == 0) {
            options->champions.champions[cham].op_cycle = op_tab[i].nbr_cycles;
            break;
        }
    }
}

void vm_run_champion(options_t *options)
{
    for (u32 i = 0; i < options->champions.len; i++) {
        if (options->champions.champions[i].op_cycle == 0) {
            champion_cycles_loop(options , i);
        } else {
            options->champions.champions[i].op_cycle -= 1;
        }
    }
}

bool champions_loop(options_t *options, vm_t *vm, u32 *cycle)
{
    for (u32 i = 0; i < options->champions.len; i++)
        if (*cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE)
            vm_run_champion(options);
    (*cycle) += 1;
    u32 min_alive_age = vm->alive_hashmap[0], min_alive_index = 0, alive = 0;
    for (u32 i = 0; i < options->champions.len; i++)
        if (vm->alive_hashmap[i] < min_alive_age)
            min_alive_age = vm->alive_hashmap[min_alive_index = i];
    if (*cycle - min_alive_age >= CYCLE_TO_DIE) {
        my_printf(WIN_MESSAGE);
        return true;
    }
    for (u32 i = 0; i < options->champions.len; i++)
        alive += (*cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE) ? 1 : 0;
    if (alive == 1) {
        my_printf(WIN_MESSAGE);
        return true;
    }
    return false;
}

void vm_run(options_t *options)
{
    u32 registers[REG_NUMBER];
    u32 alive_hashmap[options->champions.len];
    u32 arena[MEM_SIZE / 4];
    for (u32 i = 0; i < REG_NUMBER; i++)
        registers[i] = 0;
    for (u32 i = 0; i < options->champions.len; i++)
        alive_hashmap[i] = 0;
    for (u32 i = 0; i < MEM_SIZE / 4; i++)
        arena[i] = 0;
    vm_t vm = {registers, alive_hashmap, arena};
    u32 cycle = 0;
    while (true) {
        if (champions_loop(options, &vm, &cycle)) {
            break;
        }
        if (options->dump == -2 || (i32) cycle == options->dump) {
            dump_memory(&vm);
        }
    }
}
