/*
** EPITECH PROJECT, 2023
** link_line.c
** File description:
** link tokens to form a line
*/
/*
 __  __        _                            ___            ___
|  \/  |      | |                          / _ \          / _ \.
| \  / | _ __ | |       ___   __ _   ___  | (_) |        | (_) |
| |\/| || '__|| |      / _ \ / _` | / _ \  > _ <          \__, |
| |  | || |   | |____ |  __/| (_| || (_) || (_) |           / /
|_|  |_||_|   |______| \___| \__, | \___/  \___/           /_/
                              __/ |               ______
                             |___/               |______|
*/
#include "parser.h"
#include "my.h"

void update_registers(line_t line, uint16_t ptr reg_bitmask, op_t *op,
    uint16_t line_nb)
{
    if (op->code == 2)
        update_register_usage(*line.params[1], reg_bitmask);
    if (op->code == 3) {
        register_unused(*line.params[0], *reg_bitmask, line_nb);
        update_register_usage(*line.params[1], reg_bitmask);
    }
    if (op->code > 3 && op->code < 12 && op->code != 9) {
        register_unused(*line.params[0], *reg_bitmask, line_nb);
        register_unused(*line.params[1], *reg_bitmask, line_nb);
        update_register_usage(*line.params[2], reg_bitmask);
    }
    if (op->code == 14) {
        register_unused(*line.params[0], *reg_bitmask, line_nb);
        register_unused(*line.params[1], *reg_bitmask, line_nb);
        update_register_usage(*line.params[2], reg_bitmask);
    }
    if (op->code == 13)
        update_register_usage(*line.params[1], reg_bitmask);
    if (op->code == 16)
        register_unused(*line.params[0], *reg_bitmask, line_nb);
}

void set_line_bytes(line_t *line)
{
    op_t *op = lookup(hashtable, line->mnemonic->token.str);
    int size = 1;
    if (!op) return;
    uint8_t c = (uint8_t)op->code;
    if (c != 9 && c != 1 && c != 12 && c != 15)
        size += 1;
    for (int i = 0; i < op->nbr_args; i++) {
        if (line->params[i]->type == TOKEN_REGISTER)
            ++size;
        if (line->params[i]->type == TOKEN_INDIRECT)
            size += 2;
        if (line->params[i]->type == TOKEN_DIRECT && c > 8 && c < 16 && c != 13)
            size += 2;
        else
            size += 4;
    }
    line->bytes_size = size;
}

bool check_params_validity(line_t line, op_t ptr op)
{
    for (int i = 0; i < op->nbr_args; i++) {
        if (!(line.params[i]->type & (uint)op->type[i]))
            return false;
    }
    return true;
}

line_t link_line(token_t array tokens, uint16_t ptr reg_bitmask,
    uint32_t ptr current_token, uint16_t nb_line)
{
    line_t line = {NULL, {NULL}, 0}, failure = {NULL, {NULL}, 0};
    for (; tokens[*current_token].type != TOKEN_MNEMONIC; *current_token += 1);
    line.mnemonic = &tokens[*current_token];
    op_t *op = lookup(hashtable, line.mnemonic->token.str);
    if (!op) return failure;
    int args_counter = 0;
    for (uint i = 1; tokens[*current_token + i].type != TOKEN_NEWLINE; i++)
        args_counter++;
    if (args_counter != op->nbr_args) {
        print_invalid_nb_args_error(nb_line, *line.mnemonic); return failure;
    } *current_token += 1;
    for (int i = 0; i < op->nbr_args; i++, *current_token += 1)
        line.params[i] = &tokens[*current_token];
    if (!check_params_validity(line, op)) {
        print_invalid_args_error(nb_line, *line.mnemonic); return failure;
    } update_registers(line, reg_bitmask, op, nb_line);
    set_line_bytes(&line);
    return line;
}
/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠉⠉⢉⠏⠻⣍⠑⢲⠢⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣻⣿⢟⣽⠿⠯⠛⡸⢹⠀⢹⠒⣊⡡⠜⠓⠢⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⡜⣿⣷⣽⠓⠀⢠⢂⣣⠋⠂⣾⠼⢌⠳⢄⢀⡠⠜⣣⡀⠀⠀
⠀⠀⠀⠀⠀⢠⢻⢱⣭⠷⠤⢅⠴⣡⡻⠃⠀⢠⠁⠀⢀⡱⠜⠍⢔⠊⠀⠹⡄⠀
⠀⠀⠀⠀⢀⣷⠌⠚⠷⠆⠠⠶⠭⢒⣁⠀⣤⠃⣀⢔⢋⡤⠊⠑⣄⠳⣄⠀⣧⠀
⠀⠀⠀⠀⠀⠑⠦⣀⡤⣄⠄⢄⣀⣠⣒⢦⡄⠩⠷⠦⠊⠀⠀⠀⠈⠣⡏⠢⣿⠀
⠀⠀⠀⠀⠀⠀⣸⢫⠟⣝⠞⣼⢲⡞⣞⠋⠋⠉⠋⠓⡄⠀⠀⠀⠀⠀⣨⠂⢸⡅
⠀⠀⠀⠀⠀⣰⠃⡨⠊⢀⡠⡌⢘⢇⠞⠀⠀⠀⠀⠂⠡⡄⠀⠀⢀⠞⢁⠔⢹⡇
⠀⠀⠀⠀⣰⣣⠞⢀⠔⢡⢢⠇⡘⠌⠀⠀⠀⠀⠀⠀⠠⡌⠢⡔⢁⡴⠁⠀⢸⠃
⠀⠀⠀⢠⠟⠁⠠⢊⠔⣡⢸⠀⠃⠁⠀⠀⠀⠀⠀⠀⠀⣯⠂⡀⢪⡀⠀⠀⢸⠀
⠀⢀⠔⣁⠐⠨⠀⠀⠈⠀⢄⠘⡀⠀⠈⢆⠀⠀⠀⠀⡠⢁⠜⠙⢦⠙⣦⠀⢸⠀
⡴⠁⠘⡁⣀⡡⠀⠀⠴⠒⠗⠋⠉⠉⡆⠀⠆⠄⠄⠘⠀⡎⠀⠀⠀⠑⢅⠑⢼⡀
⢯⣉⣓⠒⠒⠤⠤⣄⣀⣀⣀⣀⡀⠐⠁⠀⠀⠀⠒⠀⢀⡀⠀⠀⠀⠀⠀⠑⣌⣇
⠀⠈⢳⠄⠈⠀⠤⢄⣀⠀⢈⣉⡹⠯⡟⠁⠀⠀⠀⠀⢸⠀⠀⠂⠀⠀⡠⠚⣡⡿
⠀⢠⣋⣀⣀⣀⣀⠤⠭⢛⡩⠄⠒⠩⠂⢀⠄⠀⠀⠀⠈⢢⡀⠀⡠⠋⡩⠋⠀⢳
⠀⢹⠤⠬⠤⠬⠭⣉⣉⢃⠀⠀⣀⣀⠀⠁⠀⠀⠀⠀⡞⢺⡈⠋⡢⠊⠀⠀⠀⢸
⠀⠈⡆⠁⢀⠀⠀⠀⠉⠋⠉⠓⠂⠤⣀⡀⠀⠀⠀⠀⡧⠊⡠⠦⡈⠳⢄⠀⠀⠈
⠀⠀⢹⡜⠀⠁⠀⠀⠒⢤⡄⠤⠔⠶⠒⠛⠧⠀⠀⡼⡠⠊⠀⠀⠙⢦⡈⠳⡄⠀
⠀⠀⢸⠆⠀⠈⠀⠠⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⡜⢸⠀⠀⠀⠀⠀⠀⠑⢄⠈⢲
⠀⠀⢸⢀⠇⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⡄⠊⢠⠃⠀⠀⠀⠀⠀⠀⠀⠈⡢⣸
⠀⠀⠈⠳⣤⣄⡀⠀⠀⠀⠈⠉⠉⠁⠒⠁⠀⠠⣏⠀⠀⠀⠀⠀⠀⢀⣔⠾⡿⠃
⠀⠀⠀⠀⠉⠙⠛⠒⠤⠤⣤⣄⣀⣀⣀⣔⣢⣀⣉⣂⣀⣀⣠⠴⠿⠛⠋
*/
