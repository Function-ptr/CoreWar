/*
** EPITECH PROJECT, 2023
** tokenizer.c
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

#include "tokenizer.h"
#include "my.h"

#define CHECK_TOKEN_AND_TOKENIZE_NEWLINE \
    if (input == NULL) { \
        free(tokens); \
        return (NULL); \
    } \
    if (current_token + 1 >= max_tokens) { \
        max_tokens *= 2; \
        token_t array tmp = realloc(tokens, sizeof(token_t) * max_tokens); \
        if (!tmp) { \
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
        continue; \
    }

token_t array tokenize(char array input, uint16_t current_line,
    uint16_t nb_of_line_in_file)
{
    token_t array tokens = malloc(sizeof(token_t) * nb_of_line_in_file * 5);
    uint32_t max_tokens = nb_of_line_in_file * 5, current_token = 0;
    if (!tokens) return (NULL);
    for (; current_line < nb_of_line_in_file; current_line++) {
        input = parse_label(input, &tokens[current_token], current_line,
            &current_token);
        CHECK_TOKEN_AND_TOKENIZE_NEWLINE
        input = parse_mnemonic(input, &tokens[current_token],current_line,
            &current_token);
        CHECK_TOKEN_AND_TOKENIZE_NEWLINE
        input = parse_register(input, &tokens[current_token], current_line,
            &current_token);
        CHECK_TOKEN_AND_TOKENIZE_NEWLINE
        input = parse_direct(input, &tokens[current_token], current_line,
            &current_token);
        CHECK_TOKEN_AND_TOKENIZE_NEWLINE
        input = parse_indirect(input, &tokens[current_token], current_line,
            &current_token);
        CHECK_TOKEN_AND_TOKENIZE_NEWLINE
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
