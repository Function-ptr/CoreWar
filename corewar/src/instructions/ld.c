/*
** EPITECH PROJECT, 2023
** ld.c
** File description:
** ld instruction
*/

#include "corewar.h"

static i16 get_ld_val_1(vm_t *vm, champion_t *champ, u8 tv1)
{
    i16 val1 = 0;
    if (tv1 == 1)
        val1 = (i16)champ->registers[vm->arena[(champ->address + 2) %
            MEM_SIZE] - 1];
    if (tv1 == 2)
        memmove_from_arena(&val1, vm->arena, (champ->address + 2) % MEM_SIZE,
            2);
    return val1;
}

void ld_inst(vm_t *vm, champion_t *champ)
{
    u8 coding_byte = vm->arena[(champ->address + 1) % MEM_SIZE];
    u8 tv1 = (coding_byte >> 6) & 3;
    i16 offsettv1 = (i16)(tv1 == 1 ? 1 : 2) + 2;
    i16 val1 = get_ld_val_1(vm, champ, tv1);
    u8 reg = vm->arena[(champ->address + offsettv1 + tv1) % MEM_SIZE];
    champ->registers[reg - 1] = val1;
    champ->carry = val1 == 0;
}
