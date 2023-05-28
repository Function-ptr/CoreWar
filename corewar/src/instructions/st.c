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
        vm->arena[mod(champ->address + off, MEM_SIZE)] = (uint8_t) (val1 >> 24);
        vm->arena[mod(champ->address + off + 1, MEM_SIZE)] =
            (uint8_t) (val1 >> 16);
        vm->arena[mod(champ->address + off + 2, MEM_SIZE)] =
            (uint8_t) (val1 >> 8);
        vm->arena[mod(champ->address + off + 3, MEM_SIZE)] =
            (uint8_t) val1;
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
