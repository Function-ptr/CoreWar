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

void lfork_inst(vm_t *vm, champion_t *champ, options_t *options)
{
    i32 param = (i32)vm->arena[(champ->address + 1) % MEM_SIZE];
    i32 new_address = (champ->address + (param)) % MEM_SIZE;
    options->champions.champions = realloc(options->champions.champions,
        sizeof(champion_t) * (options->champions.len + 1));
    memmove_in_arena(vm->arena, new_address, champ->address,
        (u64)champ->len_body);
    champion_t new_champ;
    new_champ.number = champ->number;
    new_champ.address = new_champ.orig_addr = new_address;
    new_champ.name = champ->name;
    new_champ.hashmap_index = champ->hashmap_index;
    for (int i = 0; i < REG_NUMBER; i++)
        new_champ.registers[i] = champ->registers[i];
    new_champ.carry = champ->carry;
    options->champions.champions[options->champions.len] = new_champ;
    options->champions.len += 1;
    champ->address = (champ->address + 3) % MEM_SIZE;
}
