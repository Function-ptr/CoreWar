/*
** EPITECH PROJECT, 2023
** aff.c
** File description:
** aff
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


void aff_inst(vm_t *vm, champion_t *champ)
{
    i32 register_index = vm->arena[(champ->address + 1) % MEM_SIZE] - 1;
    i32 register_value = champ->registers[register_index];
    register_value %= 256;
    char c = (char)register_value;
    write_void(1, &c, 1);
    champ->address = mod(champ->address + 2, MEM_SIZE);
}
