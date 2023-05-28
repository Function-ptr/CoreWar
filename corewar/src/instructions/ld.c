/*
** EPITECH PROJECT, 2023
** ld.c
** File description:
** ld instruction
*/

#include "corewar.h"

void ld_inst(vm_t *vm, champion_t *champ)
{
    u8 coding_byte = vm->arena[(champ->address + 1) % MEM_SIZE];
    u8 tv1 = (coding_byte >> 6) & 3;
    i16 val2 = 0, offsettv1 = (i16)(tv1 == 1 ? 1 : 2) + 2;
}