/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "../include/my.h"

int error_handling(int ac)
{
    if (ac < 3 || ac > 5) {
        my_printf("Error: Wrong number of arguments\n");
        return (84);
    }
    return (0);
}