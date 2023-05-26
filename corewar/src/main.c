/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

options_t build_options(champion_t *champions)
{
    options_t options = {
        .valid = true,
        .dump = -1,
        .champions = {
            .len = 0,
            .champions = champions
        }
    };
    return options;
}

i32 main(i32 argc, const char **argv)
{
    if (error_handling(argc) == 84) return 84;
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
        champions[i] = (champion_t) {-1, -1, NULL, op_tab[16], 0};
    options_t options = build_options(champions);
    read_flags(argc, argv, &options);
    if (!options.valid)
        return 1;
    vm_run(&options);
    return (0);
}
