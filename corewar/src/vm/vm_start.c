/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

void vm_run_champion(options_t *options)
{
    if (options->champions.champions[0].op_cycle == 0) {
        // TODO: run champion op
    } else {
        options->champions.champions[0].op_cycle -= 1;
    }
}

void champions_loop(options_t *options, vm_t *vm, u32 cycle)
{
    for (u32 i = 0; i < options->champions.len; i++) {
        if (cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE) {
            vm_run_champion(options);
        }
    }
}

bool is_everyone_dead(vm_t *vm, u32 cycle)
{
    for (u32 i = 0; i < MAX_CHAMPIONS; i++)
        if (cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE)
            return false;
    return true;
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
        if (is_everyone_dead(&vm, cycle))
            break;
        champions_loop(options, &vm, cycle);
        cycle += 1;
    }
}
