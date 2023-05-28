/*
** EPITECH PROJECT, 2023
** live.c
** File description:
** live instruction
*/

#include "corewar.h"

void live_inst(vm_t *vm, champion_t *champ)
{
    i32 champ_number;
    memmove_from_arena(&champ_number, vm->arena,
        (champ->address + 1) % MEM_SIZE, 4);
    if (champ_number == champ->number)
        vm->alive_hashmap[champ->hashmap_index] = 1;
}
