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

    #define CHECK_TOKEN_AND_TOKENIZE_NEWLINE \
        if (input == NULL) { \
            for (uint32_t x = 0; x < current_token; x++) \
                free_string(tokens[i].token); \
            free(tokens); \
            return (NULL); \
        } \
        if (current_token + 1 >= max_tokens) { \
            max_tokens *= 2; \
            token_t array tmp = realloc(tokens, sizeof(token_t) * max_tokens); \
            if (!tmp) {                      \
                for (uint32_t x = 0; x < current_token; x++) \
                    free_string(tokens[i].token); \
                free(tokens); \
                return (NULL); \
            } \
            tokens = tmp; \
        } \
        if (*input == '\n') { \
            tokens[current_token].token = create_string("\n"); \
            tokens[current_token].type = TOKEN_NEWLINE; \
            current_token++; \
            input++; \
            break; \
        }

    typedef enum {
        TOKEN_MNEMONIC,
        TOKEN_REGISTER,
        TOKEN_DIRECT,
        TOKEN_INDIRECT,
        TOKEN_NEWLINE,
        TOKEN_LABEL,
        TOKEN_END
    } token_type_t;

    typedef struct {
        token_type_t type;
        string_t token;
    } token_t;

    typedef char* (*parse_func_t) (char *, token_t *, uint16_t, uint32_t*);

    char array parse_label(char array input, token_t ptr token,
        uint16_t line_nb, uint32_t ptr current_token);
    char array parse_register(char array input, token_t ptr token,
        uint16_t line_nb, uint32_t ptr current_token);
    char array parse_direct(char array input, token_t ptr token,
        uint16_t line_nb, uint32_t ptr current_token);
    char array parse_indirect(char array input, token_t ptr token,
        uint16_t line_nb, uint32_t ptr current_token);
    char array parse_mnemonic(char array input, token_t ptr token,
        uint16_t line_nb, uint32_t ptr current_token);
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
