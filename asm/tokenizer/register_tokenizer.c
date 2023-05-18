/*
** EPITECH PROJECT, 2023
** register_tokenizer.c
** File description:
** register tokenizer
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

bool detect_register_syntax_error(char ptr ptr end, char array input,
    uint16_t line_nb)
{
    if (*(*end - 1) != ' ' && *(*end - 1) != ',' && !(*(*end + 1) >= '0'
        && *(*end + 1) <= '9')) {
        print_syntax_error(input, line_nb);
        return (true);
    }
    *end += 1;
    uint nb_register = (uint)my_strtol(*end, NULL, 10);
    if (nb_register < 1 || nb_register > REG_NUMBER) {
        print_syntax_error(input, line_nb);
        return true;
    }
    if ((*(*end + 1) >= '0' && *(*end + 1) <= '9'))
        *end += 1;
    return false;
}

char* parse_register(char array input, token_t ptr token, uint16_t line_nb,
    uint32_t array current_token)
{
    char ptr end = input;
    if (!input || !token) return (NULL);
    while (*end && *end != REG_CHAR && *end != '\n') end++;
    if (*end != REG_CHAR) return (input);
    if (detect_register_syntax_error(&end, input, line_nb)) return NULL;
    char temp[end - input + 1];
    my_memcpy(temp, input, (size_t) (end - input));
    temp[end - input] = '\0';
    token->token = create_string(temp);
    if (token->token.len == 0) return (NULL);
    token->type = TOKEN_REGISTER;
    *current_token += 1;
    return (++end);
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
