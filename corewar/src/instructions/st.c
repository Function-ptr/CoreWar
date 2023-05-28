/*
** EPITECH PROJECT, 2023
** st.c
** File description:
** st instruction
*/

#include "corewar.h"

static void change_value(vm_t *vm, champion_t *champ, i32 val1, u8 tv2)
{
    if (tv2 == 3) {
        i16 off = 0;
        memmove_from_arena(&off, vm->arena, (champ->address + 3) % MEM_SIZE, 2);
        swap_uint16((u16*)&off);
        swap_uint32((u32*)&val1);
        memmove_to_arena(vm->arena, &val1,
            mod(champ->address + off, MEM_SIZE), 4);
        champ->address = mod(champ->address + 5, MEM_SIZE);
    }
}

void st_inst(vm_t *vm, champion_t *champ)
{
    u8 coding_byte = vm->arena[(champ->address + 1) % MEM_SIZE];
    u8 reg1 = vm->arena[(champ->address + 2) % MEM_SIZE];
    i32 val1 = champ->registers[reg1 - 1];
    u8 tv2 = (coding_byte >> 4) & 3;
    if (tv2 == 1) {
        u8 reg2 = vm->arena[(champ->address + 3) % MEM_SIZE];
        champ->registers[reg2 - 1] = val1;
        return;
    }
    change_value(vm, champ, val1, tv2);
}
