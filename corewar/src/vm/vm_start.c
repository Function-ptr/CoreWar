/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "corewar.h"

void champion_cycles_loop(options_t *options, u32 cham)
{
    for (u32 i = 0; i < REG_NUMBER; i++) {
        if (1) {
            options->champions.champions[cham].op_cooldown =
                op_tab[i].nbr_cycles;
            break;
        }
    }
}

void run_instruction(vm_t *vm, options_t *options, u8 i,
    const instruction_t instruction[16])
{
    if (vm->arena[options->champions.champions[i].address] == 12) {
        fork_inst(vm, &options->champions.champions[i], options);
        return;
    }
    if (vm->arena[options->champions.champions[i].address] == 15) {
        lfork_inst(vm, &options->champions.champions[i], options);
        return;
    }
    instruction[vm->arena[options->champions.champions[i].address] - 1](vm,
        &options->champions.champions[i]);
}

void vm_run_champion(options_t *options, vm_t *vm,
    const instruction_t instruction[16])
{
    for (u32 i = 0; i < options->champions.len; i++) {
        if (options->champions.champions[i].number == 0)
            continue;
        if (options->champions.champions[i].op_cooldown == 0) {
            run_instruction(vm, options, (u8) i, instruction);
            champion_cycles_loop(options , i);
        } else
            options->champions.champions[i].op_cooldown -= 1;
    }
}

void remove_dead_champions(champions_list_t *list, vm_t *vm)
{
    for (u32 i = 0; i < list->len; i++)
        if (list->champions[i].number &&
        vm->alive_hashmap[list->champions[i].hashmap_index] == 0)
            list->champions[i].number = 0;
}

bool run_all_champions_and_cycle(options_t *options, vm_t *vm,
    u32 *cycles_data[4], const instruction_t instruction[16])
{
    u32 *live_cycle = cycles_data[0], *nb_lives = cycles_data[1],
    *cycles_to_die = cycles_data[2], *cycle = cycles_data[3];
    for (u32 i = 0; i < options->champions.len; i++)
        vm_run_champion(options, vm, instruction);
    (*cycle) += 1;
    *live_cycle += 1;
    if (*live_cycle == *cycles_to_die) {
        if (*nb_lives >= NBR_LIVE)
            *cycles_to_die -= CYCLE_DELTA;
        remove_dead_champions(&options->champions, vm);
        *live_cycle = 0;
        *nb_lives += 1;
        return true;
    }
    return false;
}

bool champions_loop(options_t *options, vm_t *vm, u32 *cycle,
    const instruction_t instruction[16])
{
    static u32 live_cycle = 0, nb_lives = 0, cycles_to_die = CYCLE_TO_DIE;
    u32 *c_data[4] = {&live_cycle, &nb_lives, &cycles_to_die, cycle};
    if (!run_all_champions_and_cycle(options, vm, c_data, instruction))
        return false;
    static i8 last_min_alive = 0;
    i8 alive = 0, min_alive_index = -1;
    for (u32 i = 0; i < (sizeof(vm->alive_hashmap) / sizeof(u32)); i++) {
        if (vm->alive_hashmap[i] && min_alive_index == -1)
            min_alive_index = (i8)i;
        alive += vm->alive_hashmap[i] == 1 ? 1 : 0;
    } if (alive <= 1) {
        if (!alive)
            min_alive_index = last_min_alive;
        my_printf(WIN_MESSAGE);
        return true;
    }
    last_min_alive = min_alive_index;
    return false;
}

void vm_run(options_t *options)
{
    const instruction_t instruction[16] = {live_inst, ld_inst, st_inst,
        add_inst, sub_inst, and_inst, or_inst, xor_inst, zjmp_inst, ldi_inst,
        sti_inst, NULL, lld_inst, lldi_inst, NULL, aff_inst
    };
    u32 alive_hashmap[options->champions.len];
    u8 arena[MEM_SIZE] = {0};
    for (u32 i = 0; i < options->champions.len; i++) {
        alive_hashmap[i] = 0;
        options->champions.champions[i].registers[0] = options->champions
            .champions->number;
    } vm_t vm = {alive_hashmap, arena};
    champion_body_t *bodies = NULL;
    load_champs_to_arena(&vm, options, bodies);
    u32 cycle = 0;
    while (true) {
        if (champions_loop(options, &vm, &cycle, instruction))
            break;
        if (options->dump == -2 || (i32) cycle == options->dump)
            dump_memory(&vm);
    }
}

/*
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢰⣦⡀⠄⢀⣀⣀⡀⠄⠄⢀⣤⡀⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣻⣿⣿⣿⣿⣿⣿⣷⣶⣾⣿⡇⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠜⠛⠛⠛⠿⣿⣿⣿⣿⣯⣭⣽⣿⣦⣤⣤⣤⣤⣤⣄⣀
⠄⠄⠄⢀⣠⠄⠄⠄⠄⠎⠉⠁⠄⠐⢭⣿⣷⣿⣋⠈⢉⣿⣿⠿⠋⣉⠁⠄⠉⠛
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⢄⣀⣠⢦⣾⣿⣿⣝⣿⣿⣿⣿⣿⠾⠿⠿⠿⠶⢶⣿
⣶⡄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠧⠈⣾⣿⣿⡿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠄
⠛⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⠃⠄⠄⠉⠉⣙⣿⡻⣿⣿⠇⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢰⣦⣤⡦⠶⢶⣾⣿⣿⣿⡿⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠙⠓⠶⠾⠿⠿⣿⠏⠁⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣠⢰⣿⣿⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
*/
