/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

void vm_run_champion(champion_t *champion, options_t *options)
{
    return;
}

void champions_loop(options_t *options, vm_t *vm, u32 cycle)
{
    for (u32 i = 0; i < options->champions.len; i++) {
        if (cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE) {
            vm_run_champion(&options->champions.champions[i], options);
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
    u8 registers[REG_NUMBER];
    u32 alive_hashmap[options->champions.len];
    for (u32 i = 0; i < REG_NUMBER; i++)
        registers[i] = 0;
    for (u32 i = 0; i < options->champions.len; i++)
        alive_hashmap[i] = 0;
    vm_t vm = {.registers = registers, .alive_hashmap = alive_hashmap};
    u32 cycle = 0;
    while (true) {
        if (is_everyone_dead(&vm, cycle))
            break;
        champions_loop(options, &vm, cycle);
    }
}
