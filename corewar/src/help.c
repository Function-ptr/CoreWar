/*
** EPITECH PROJECT, 2022
** help.c
** File description:
** -h flag
*/

#include "../include/my.h"
#include "../include/utils.h"

int help(char **av)
{
    if (av[1] != NULL && strcmp(av[1], "-h") == 0) {
        my_printf("USAGE\n./corewar [-dump nbr_cycle] [[-n prog_number] ");
        my_printf("[-a load_address] prog_name] ...\nDESCRIPTION\n-dump nbr");
        my_printf("_cycle dumps the memory after the nbr_cycle execution ");
        my_printf("(if the round isn’t already over) with the following ");
        my_printf("format: 32 bytes/line in hexadecimal (A0BCDEFE1DD3...)\n");
        my_printf("-n prog_number sets the next program’s number. By ");
        my_printf("default, the first free number in the parameter order\n");
        my_printf("-a load_address sets the next program’s loading address.");
        my_printf(" When no address isspecified, optimize the addresses so ");
        my_printf("that the processes are as far away from each other as ");
        my_printf("possible. The addresses are MEM_SIZE modulo.\n");
        return (1);
    }
    return (0);
}