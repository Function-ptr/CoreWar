/*
** EPITECH PROJECT, 2022
** help_message.c
** File description:
** print help message
*/

#include "corewar.h"

void help_message(void)
{
    usage_message(1);

    write_void(1, "DESCRIPTION\n"
    "-dump nbr_cycle dumps the memory after the nbr_cycle execution "
    "(if the round isn't\n"
    "already over) with the following format: 32 bytes/line\n"
    "in hexadecimal (A0BCDEFE1DD3...)\n"
    "-n prog_number sets the next program's number. By default, the first "
    "free number\n"
    "in the parameter order\n"
    "-a load_address sets the next program's loading address. "
    "When no address is\n"
    "specified, optimize the addresses so that the processes are as far\n"
    "away from each other as possible. The addresses are MEM_SIZE modulo.\n",
    499);
}
