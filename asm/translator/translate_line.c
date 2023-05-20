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

void translate_mnemonic(token_t ptr mnemonic, string_t buffer)
{
    buffer.str[buffer.len++] = lookup_string(hashtable, mnemonic->token)->code;
}

void translate_params(token_t ptr params[4], string_t ptr buffer)
{
    for (int i = 0; i < 4 && params[i] != NULL; i++) {
        if (params[i]->type == TOKEN_REGISTER) {
            char str[3] = {0};
            my_memcpy(str, params[i]->token.str + 1,
                params[i]->token.len - 1);
            buffer->str[buffer->len++] = (int8_t)my_strtol(str, NULL, 10);
            continue;
        }
        if (params[i]->type == TOKEN_INDIRECT) {
            char str[6] = {0};
            my_memcpy(str, params[i]->token.str, params[i]->token.len);
            if (str[0] != ':') {
                int16_t value = (int16_t) my_strtol(str, NULL, 10);
                buffer->str[buffer->len++] = (int8_t)(value >> 8);
                buffer->str[buffer->len++] = (int8_t)value;
            } else {
                buffer->str[buffer->len++] = str[1];
                buffer->str[buffer->len++] = str[2];
            }
            continue;
        }
        if (params[i]->type == TOKEN_DIRECT) {
            char code = lookup_string(hashtable, params[i]->token)->code;
            uint8_t nb_bytes = code >= 9 && code <= 15 && code != 13 ? 2 : 4;
            char str[6] = {0};
            my_memcpy(str, params[i]->token.str, params[i]->token.len);
            if (str[0] == ':') {
                int32_t value = (int32_t) my_strtol(str, NULL, 10);
                for (int j = 0; j < nb_bytes; j++)
                    buffer->str[buffer->len++] = (int8_t)
                        (value >> (8 * (nb_bytes - j - 1)));
            } else {
                my_memcpy(buffer->str + buffer->len, str + 1,
                          params[i]->token.len - 1);
                buffer->len += params[i]->token.len - 1;
            }
        }
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
