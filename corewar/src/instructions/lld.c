/*
** EPITECH PROJECT, 2023
** lld.c
** File description:
** lld instruction
*/

#include "corewar.h"

i32 get_lld_val_1(vm_t *vm, champion_t *champ, u8 tv1)
{
    i32 val1 = 0;
    if (tv1 == 2)
        memmove_from_arena(&val1, vm->arena, (champ->address + 2) % MEM_SIZE,
            4);
    if (tv1 == 3) {
        i16 off = 0;
        memmove_from_arena(&off, vm->arena, (champ->address + 2) % MEM_SIZE, 2);
        memmove_from_arena(&val1, vm->arena,
            mod(champ->address + off, MEM_SIZE), 4);
    }
    swap_uint32((u32*)&val1);
    return val1;
}

void lld_inst(vm_t *vm, champion_t *champ)
{
    u8 coding_byte = vm->arena[(champ->address + 1) % MEM_SIZE];
    u8 tv1 = (coding_byte >> 6) & 3;
    i16 offsettv1 = (i16)(tv1 == 2 ? 4 : 2) + 2;
    i32 val1 = get_lld_val_1(vm, champ, tv1);
    u8 reg = vm->arena[(champ->address + offsettv1) % MEM_SIZE];
    memmove_from_arena(champ->registers + (reg - 1), vm->arena,
        mod(champ->address + val1, MEM_SIZE), REG_SIZE);
    champ->carry = champ->registers[reg - 1] == 0;
    champ->address = mod(champ->address + offsettv1 + 1, MEM_SIZE);
}
