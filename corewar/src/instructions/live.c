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
    swap_uint32((u32*)&champ_number);
    if (champ_number != champ->number)
        return;
    vm->alive_hashmap[champ->hashmap_index] = 1;
    write_void(1, "The player ", 11);
    my_put_nbr_do(champ->number);
    write_void(1, "(", 1);
    write_void(1, champ->name, (u64)my_strlen((char*)(champ->name)));
    write_void(1, ") is alive.\n", 12);
}
