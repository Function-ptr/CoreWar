/*
** EPITECH PROJECT, 2023
** fork.c
** File description:
** fork
*/
/*
⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡫⡝⣜⢜⢜⢜⠝⡝⡜⣜⢜⢝⠿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⢏⢮⢺⡸⡔⣇⢗⢵⢹⣘⢜⢆⢧⢣⡫⡜⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⡿⡹⡸⡪⣃⢇⠧⢣⠳⣑⠥⣓⢌⢧⢳⢕⢕⠣⡃⡻⢿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⡹⡸⡍⠎⢖⢕⢝⠱⠙⠢⣋⣢⢓⠜⣎⢕⠑⠱⡱⡱⡑⣿⣿⣿
⣿⣿⣿⣿⣿⢧⢳⢹⡸⡹⡜⡪⣃⡁⡐⠗⢸⣿⣷⢱⢱⡇⠕⠰⢺⡷⢗⣿⣿⣿
⣿⣿⣿⣿⡿⡸⡪⣣⢳⡹⡜⣎⢖⢕⢕⢕⡹⡸⡰⡱⣕⡊⣒⡢⡣⢅⢿⣿⣿⣿
⣿⣿⣿⣿⢣⡣⡫⡎⡖⡪⡺⡸⣪⢣⡫⢎⢎⢮⢪⡣⣣⢳⢢⡣⣫⢣⢇⢻⣿⣿
⣿⣿⣿⣟⢕⢵⢹⢜⢔⠅⠪⠡⡃⡳⠱⢣⠫⡎⣇⢏⢮⡪⣣⢫⡪⢎⢅⣽⣿⣿
⣿⣿⣯⣿⣧⡳⡱⣣⢳⡱⢥⡑⡔⠌⡊⢌⠜⡐⡂⡑⡐⡂⡢⢑⠨⡂⢪⣿⣿⣿
⣿⡏⠿⣿⣿⣿⣎⡮⡪⡎⣇⢧⢣⡳⡸⢤⢡⢂⣊⣐⣁⣊⣐⢡⢌⢎⣿⣿⣿⣿
⡿⠄⠄⠄⠉⠛⢿⣿⣷⣭⣎⣎⠧⡳⡹⡜⣎⢮⢲⡸⡔⡎⣎⢎⢮⠈⠛⢿⣿⣿
⡇⠄⠄⠄⠄⠄⠄⠄⠙⠻⢿⣿⣿⠗⠃⠁⠑⠑⠑⠑⠑⠉⠈⠊⢻⠄⠄⠄⠻⣿
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠻⣄⢀⡀⣤⣤⢤⣤⢄⣀⠄⠄⠄⠄⠄⠄⠄⠘
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠁⠄⠹⣿⢗⡟⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠑⢿⣫⡟⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
*/

#include "corewar.h"

void fork_inst(vm_t *vm, champion_t *champ, options_t *options)
{
    i32 param = (i32)vm->arena[(champ->address + 1) % MEM_SIZE];
    i32 new_address = (champ->address + (param % IDX_MOD)) % MEM_SIZE;
    options->champions.champions = realloc(options->champions.champions,
        sizeof(champion_t) * (options->champions.len + 1));
    vm->alive_hashmap = realloc(vm->alive_hashmap,
        sizeof(u32) * (options->champions.len + 1));
    memmove_in_arena(vm->arena, new_address, champ->address,
        (u64)champ->len_body);
    champion_t new_champ;
    new_champ.number = champ->number;
    new_champ.address = new_champ.orig_addr = new_address;
    new_champ.name = champ->name;
    new_champ.hashmap_index = (u8)options->champions.len;
    for (int i = 0; i < REG_NUMBER; i++)
        new_champ.registers[i] = champ->registers[i];
    new_champ.carry = champ->carry;
    new_champ.op = champ->op;
    new_champ.op_cycle = champ->op_cycle;
    options->champions.champions[options->champions.len] = new_champ;
    options->champions.len += 1;
}
