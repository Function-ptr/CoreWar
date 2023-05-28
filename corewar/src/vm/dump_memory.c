/*
** EPITECH PROJECT, 2022
** dump_memory.c
** File description:
** dump memory
*/

#include "corewar.h"

void print_u8_as_hexa(u8 c)
{
    u8 hex = (u8) ((c > 9) ? (c - 10) + 'A' : c + '0');
    write_void(1, &hex, 1);
}

void dump_memory(vm_t *vm)
{
    for (u32 i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0 && i != 0)
            write_void(1, "\n", 1);
        print_u8_as_hexa(vm->arena[i]);
    }
    write_void(1, "\n\n", 2);
}
