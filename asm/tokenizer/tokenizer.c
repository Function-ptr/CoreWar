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
    } tokens[current_token].type = TOKEN_END; return tokens;
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
