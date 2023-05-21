/*
** EPITECH PROJECT, 2023
** translate_line.c
** File description:
** translate line to hex
*/
/*
 _____               __      __
|  __ \              \ \    / /
| |__) |  __ _  ___   \ \  / /   ___   __ _   __ _  _ __
|  ___/  / _` |/ __|   \ \/ /   / _ \ / _` | / _` || '_ \
| |     | (_| |\__ \    \  /   |  __/| (_| || (_| || | | |
|_|      \__,_||___/     \/     \___| \__, | \__,_||_| |_|
                                       __/ |
                                      |___/
*/

#include "asm.h"
#include "my.h"

void translate_mnemonic(token_t ptr mnemonic, string_t ptr buffer)
{
    op_t *op = lookup_string(hashtable, mnemonic->token);
    if (op == NULL) return;
    buffer->str[buffer->len++] = op->code;
}

void translate_register(token_t ptr param, string_t ptr buffer)
{
    char str[3] = {0};
    my_memcpy(str, param->token.str + 1, param->token.len - 1);
    buffer->str[buffer->len++] = (int8_t)my_strtol(str, NULL, 10);
}

void translate_direct(token_t ptr param, string_t ptr buffer, token_t ptr inst)
{
    op_t *op = lookup_string(hashtable, inst->token);
    if (op == NULL) return;
    char code = op->code;
    uint8_t nb_bytes = code >= 9 && code <= 15 && code != 13 ? 2 : 4;
    char str[6] = {0};
    my_memcpy(str, param->token.str, param->token.len);
    if (str[0] != ':') {
        int32_t value = (int32_t) my_strtol(str, NULL, 10);
        for (int j = 0; j < nb_bytes; j++)
            buffer->str[buffer->len++] = (int8_t)
                (value >> (8 * (nb_bytes - j - 1)));
    } else {
        if (nb_bytes == 4) my_revstr(str + 1);
        if (nb_bytes == 2) {
            char tmp = str[1]; str[1] = str[2]; str[2] = tmp;
        }
        my_memcpy(buffer->str + buffer->len, str + 1, param->token.len - 1);
        buffer->len += param->token.len - 1;
    }
}

void translate_indirect(token_t ptr param, string_t ptr buffer)
{
    char str[6] = {0};
    my_memcpy(str, param->token.str, param->token.len);
    if (str[0] != ':') {
        int16_t value = (int16_t) my_strtol(str, NULL, 10);
        buffer->str[buffer->len++] = (int8_t)(value >> 8);
        buffer->str[buffer->len++] = (int8_t)value;
    } else {
        buffer->str[buffer->len++] = str[2];
        buffer->str[buffer->len++] = str[1];
    }
}

void translate_params(line_t line, string_t ptr buffer)
{
    token_t ptr array params = line.params;
    for (int i = 0; i < 4 && params[i] != NULL; i++) {
        if (params[i]->type == TOKEN_REGISTER) {
            translate_register(params[i], buffer);
            continue;
        }
        if (params[i]->type == TOKEN_INDIRECT) {
            translate_indirect(params[i], buffer);
            continue;
        }
        if (params[i]->type == TOKEN_DIRECT)
            translate_direct(params[i], buffer, line.mnemonic);
    }
}
/*
─▄▀▀▀▀▄─█──█────▄▀▀█─▄▀▀▀▀▄─█▀▀▄
─█────█─█──█────█────█────█─█──█
─█────█─█▀▀█────█─▄▄─█────█─█──█
─▀▄▄▄▄▀─█──█────▀▄▄█─▀▄▄▄▄▀─█▄▄▀

─────────▄██████▀▀▀▀▀▀▄
─────▄█████████▄───────▀▀▄▄
──▄█████████████───────────▀▀▄
▄██████████████─▄▀───▀▄─▀▄▄▄──▀▄
███████████████──▄▀─▀▄▄▄▄▄▄────█
█████████████████▀█──▄█▄▄▄──────█
███████████──█▀█──▀▄─█─█─█───────█
████████████████───▀█─▀██▄▄──────█
█████████████████──▄─▀█▄─────▄───█
█████████████████▀███▀▀─▀▄────█──█
████████████████──────────█──▄▀──█
████████████████▄▀▀▀▀▀▀▄──█──────█
████████████████▀▀▀▀▀▀▀▄──█──────█
▀████████████████▀▀▀▀▀▀──────────█
──███████████████▀▀─────█──────▄▀
──▀█████████████────────█────▄▀
────▀████████████▄───▄▄█▀─▄█▀
──────▀████████████▀▀▀──▄███
──────████████████████████─█
─────████████████████████──█
────████████████████████───█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████▄▄▄▄▄█

─────────────█─────█─█──█─█───█
─────────────█─────█─█──█─▀█─█▀
─────────────█─▄█▄─█─█▀▀█──▀█▀
─────────────██▀─▀██─█──█───█
*/
