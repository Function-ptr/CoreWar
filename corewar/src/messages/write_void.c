/*
** EPITECH PROJECT, 2022
** write_void.c
** File description:
** write functions that returns void
*/

#include "corewar.h"

void write_void(int fd, const void *buf, size_t n)
{
    write(fd, buf, n);
}
