/*
** EPITECH PROJECT, 2022
** usage.c
** File description:
** print usage message
*/

#include "corewar.h"

void usage_message(i32 fd)
{
    write(fd, "USAGE\n./corewar [-dump nbr_cycle] [[-n prog_number] "
    "[-a load_address] prog_name] ...\n", 85);
}
