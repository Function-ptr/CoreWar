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
        parse_label,
        parse_mnemonic,
        parse_register,
        parse_direct,
        parse_indirect
    }; size_t num_funcs = sizeof(parse_funcs) / sizeof(parse_funcs[0]);
    tokenize_first_newline(&input, &tokens[current_token], &current_line,
        &current_token);
    for (; current_line < nb_of_line_in_file; current_line++)
        for (size_t i = 0; i < num_funcs; i++) {
            char ptr backup = input;
            input = parse_funcs[i](input, &tokens[current_token], current_line,
            &current_token);
            if (*input == ',')
                input++;
            if (input == NULL) {
                for (uint32_t x = 0; x < current_token; x++)
                    free_string(tokens[x].token);
                free(tokens);
                return (NULL);
            }
            if (current_token + 1 >= max_tokens) {
                max_tokens *= 2;
                token_t array tmp = realloc(tokens, sizeof(token_t) * max_tokens);
                if (!tmp) {
                    for (uint32_t x = 0; x < current_token; x++)
                        free_string(tokens[x].token);
                    free(tokens);
                    return (NULL);
                }
                tokens = tmp;
            }
            if (*input == '\n') {
                tokens[current_token].token = create_string("\n");
                tokens[current_token].type = TOKEN_NEWLINE;
                current_token++;
                input++;
                break;
            }
            if (backup != input && i > 1) i = 1;
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
