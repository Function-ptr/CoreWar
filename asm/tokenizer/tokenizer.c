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

void tokenize_first_newline(char ptr array input, token_t ptr token,
    uint16_t ptr line_nb, uint32_t ptr current_token)
{
    if (!input || !token) return;
    if (**input == '\n') {
        token->token = create_string("\n");
        token->type = TOKEN_NEWLINE;
        *current_token += 1;
        (*input)++;
        *line_nb += 1;
    }
}

token_t array tokenize(char array input, uint16_t current_line,
    uint16_t nb_of_line_in_file)
{
    token_t array tokens = malloc(sizeof(token_t) * nb_of_line_in_file * 5);
    uint32_t max_tokens = nb_of_line_in_file * 5, current_token = 0;
    if (!tokens) return (NULL);
    parse_func_t parse_funcs[] = {
        parse_label, parse_mnemonic, parse_register, parse_direct,
        parse_indirect
    };
    tokenize_first_newline(&input, &tokens[current_token], &current_line,
        &current_token);
    for (; current_line <= nb_of_line_in_file; current_line++) {
        for (uint8_t i = 0; i < 5; i++) {
            char ptr backup = input;
            input = parse_funcs[i](input, &tokens[current_token], current_line,
                &current_token);
            CHECK_TOKEN_AND_TOKENIZE_NEWLINE
        }
    }
    tokens[current_token].type = TOKEN_END;
    return tokens;
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
