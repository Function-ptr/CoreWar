/*
** EPITECH PROJECT, 2023
** tokenizer.h
** File description:
** tokenizer
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

#ifndef COREWAR_TOKENIZER_H
    #define COREWAR_TOKENIZER_H

    #include <stdint.h>
    #include <unistd.h>
    #include <stddef.h>
    #include "string.h"
    #include "op.h"

    typedef enum {
        TOKEN_MNEMONIC,
        TOKEN_REGISTER,
        TOKEN_DIRECT,
        TOKEN_INDIRECT,
        TOKEN_COMMA,
        TOKEN_NEWLINE,
        TOKEN_LABEL,
        TOKEN_UNKNOWN
    } token_type_t;

    typedef struct {
        token_type_t type;
        string_t token;
    } token_t;

    char* parse_label(char *input, token_t *token, uint16_t line_nb,
        uint16_t *current_token);
    char* parse_register(char *input, token_t *token, uint16_t line_nb);
    char* parse_direct(char *input, token_t *token, uint16_t line_nb);
    char* parse_indirect(char *input, token_t *token, uint16_t line_nb);
    char* parse_mnemonic(char *input, token_t *token, uint16_t line_nb);
    char* parse_comma(char *input, token_t *token, uint16_t line_nb);
    char* parse_newline(char *input, token_t *token, uint16_t line_nb);
    void print_syntax_error(char *input, uint16_t line_nb);

#endif //COREWAR_TOKENIZER_H

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
