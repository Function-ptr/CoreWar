/*
** EPITECH PROJECT, 2022
** dump_memory.c
** File description:
** dump memory
*/

#include "corewar.h"

void print_u8_as_hexa(u8 c) {
    u8 hex = (u8) ((c > 9) ? (c - 10) + 'A' : c + '0');
    write_void(1, &hex, 1);
}

void print_u32_as_hex(u32 nb)
{
    u8 *data = (u8 *) &nb;
    for (u32 i = 0; i < 4; i++) {
        print_u8_as_hexa(data[i]);
    }
}

void dump_memory(vm_t *vm)
{
    for (u32 i = 0; i < MEM_SIZE / 4; i++) {
        if (i % 8 == 0 && i != 0)
            write_void(1, "\n", 1);
        print_u32_as_hex(vm->arena[i]);
    }
    write_void(1, "\n", 1);
}
