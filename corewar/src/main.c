/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

i32 main(i32 argc, const char **argv)
{
    if (argc == 1) {
        usage_message(2);
        return 1;
    }
    if (my_strcmp(argv[1], "-h") == 0) {
        help_message();
        return 0;
    }
    champion_t champions[MAX_CHAMPIONS];
    for (i32 i = 0; i < MAX_CHAMPIONS; i++)
        champions[i] = (champion_t) {-1, -1, NULL};
    options_t options = (options_t) {true, -1, (champions_list_t) {0, champions}};
    read_flags(argc, argv, &options);
    if (options.valid == false)
        return 1;

    return (0);
}
