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
        if (my_strcmp(options->champions.champions[cham].op.mnemonique,
            op_tab[i].mnemonique) == 0) {
            options->champions.champions[cham].op_cycle = op_tab[i].nbr_cycles;
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
        if (options->champions.champions[i].op_cycle == 0) {
            champion_cycles_loop(options , i);
        } else {
            options->champions.champions[i].op_cycle -= 1;
        }
        run_instruction(vm, options, (u8) i, instruction);
    }
}

bool champions_loop(options_t *options, vm_t *vm, u32 *cycle,
const instruction_t instruction[16])
{
    for (u32 i = 0; i < options->champions.len; i++)
        if (*cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE)
            vm_run_champion(options, vm, instruction);
    (*cycle) += 1;
    u32 min_alive_age = vm->alive_hashmap[0], min_alive_index = 0, alive = 0;
    for (u32 i = 0; i < options->champions.len; i++)
        if (vm->alive_hashmap[i] < min_alive_age)
            min_alive_age = vm->alive_hashmap[min_alive_index = i];
    if (*cycle - min_alive_age >= CYCLE_TO_DIE) {
        my_printf(WIN_MESSAGE);
        return true;
    }
    for (u32 i = 0; i < options->champions.len; i++)
        alive += (*cycle - vm->alive_hashmap[i] < CYCLE_TO_DIE) ? 1 : 0;
    if (alive == 1) {
        my_printf(WIN_MESSAGE);
        return true;
    }
    return false;
}

void vm_run(options_t *options)
{
    const instruction_t instruction[16] = {live_inst, ld_inst, st_inst,
        add_inst, sub_inst, and_inst, or_inst, xor_inst, zjmp_inst, ldi_inst,
        sti_inst, NULL, lld_inst, lldi_inst, NULL, aff_inst
    };
    u32 *alive_hashmap[options->champions.len];
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
