/*
** EPITECH PROJECT, 2023
** lldi.c
** File description:
** lldi
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

i16 get_ldi_val_1(vm_t *vm, champion_t *champ, u8 tv1)
{
    i16 val1 = 0;
    if (tv1 == 1)
        val1 = (i16)champ->registers[vm->arena[(champ->address + 2) %
            MEM_SIZE] - 1];
    if (tv1 == 2)
        memmove_from_arena(&val1, vm->arena, (champ->address + 2) % MEM_SIZE,
            2);
    return val1;
}

void ldi_inst(vm_t *vm, champion_t *champ)
{
    u8 coding_byte = vm->arena[(champ->address + 1) % MEM_SIZE];
    u8 tv1 = (coding_byte >> 6) & 3, tv2 = (coding_byte >> 4) & 3;
    i16 val2 = 0, offsettv1 = (i16)(tv1 == 1 ? 1 : 2) + 2;
    i16 val1 = get_ldi_val_1(vm, champ, tv1);
    if (tv2 == 1) val2 = (i16)champ->registers[
        vm->arena[(champ->address + offsettv1) % MEM_SIZE] - 1];
    if (tv2 == 2) memmove_from_arena(&val2,
        vm->arena, (offsettv1 + champ->address) % MEM_SIZE, 2);
    u8 reg = vm->arena[(champ->address + offsettv1 + tv2) % MEM_SIZE];
    i32 val3 = 0;
    memmove_from_arena(&val3, vm->arena, (champ->address + val1) %
        MEM_SIZE, 4);
    val3 += val2;
    memmove_from_arena(champ->registers + (reg - 1), vm->arena,
        (i32)(champ->address + val3) % MEM_SIZE, REG_SIZE);
    if (champ->registers[reg - 1] == 0)
        champ->carry = 1;
}