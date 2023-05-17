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
        TOKEN_NEWLINE,
        TOKEN_LABEL
    } token_type_t;

    typedef struct {
        token_type_t type;
        string_t token;
    } token_t;

    char array parse_label(char array input, token_t ptr token,
        uint16_t line_nb, uint16_t ptr current_token);
    char array parse_register(char array input, token_t ptr token,
        uint16_t line_nb, uint16_t ptr current_token);
    char array parse_direct(char array input, token_t ptr token,
        uint16_t line_nb, uint16_t ptr current_token);
    char array parse_indirect(char array input, token_t ptr token,
        uint16_t line_nb, uint16_t ptr current_token);
    char array parse_mnemonic(char array input, token_t ptr token,
        uint16_t line_nb, uint16_t ptr current_token);
    void print_syntax_error(char array input, uint16_t line_nb);
    void print_instruction_error(char *input, uint16_t line_nb);
    token_t array tokenize(char array input, uint16_t current_line,
        uint16_t nb_of_line_in_file);

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
