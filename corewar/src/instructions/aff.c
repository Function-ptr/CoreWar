/*
** EPITECH PROJECT, 2023
** lld.c
** File description:
** lld
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


void aff(vm_t *vm, champion_t *champ)
{
    if (champ->op.nbr_args != 1) {
        wriet(2,"Erreur : Nombre incorrect d'arguments pour l'instruction aff\n", 61);
        return;
    }
    i32 register_index = vm->arena[(champ->address + 1) % MEM_SIZE] - 1;
    i32 register_value = champ->registers[register_index];

    register_value %= 256;
    if (register_value == 42) {
        write(1, "*\n", 2);
    }
}
