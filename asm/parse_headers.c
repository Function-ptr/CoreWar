/*
** EPITECH PROJECT, 2023
** parse_headers.c
** File description:
** parse headers
*/
/*
 __  __        _                            ___            ___
|  \/  |      | |                          / _ \          / _ \.
| \  / | _ __ | |       ___   __ _   ___  | (_) |        | (_) |
| |\/| || '__|| |      / _ \ / _` | / _ \  > _ <          \__, |
| |  | || |   | |____ |  __/| (_| || (_) || (_) |           / /
|_|  |_||_|   |______| \___| \__, | \___/  \___/           /_/
                              __/ |               ______
                             |___/               |______|
*/
#include "asm.h"
#include "my.h"

const uint32_t cem = COREWAR_EM;

int get_len_to_newline_quote(char array str)
{
    if (str == NULL) return 0;
    int len = 0;
    for (; str && str[len] != 0 && str[len] != '\n' && str[len] != '"'; len++);
    return len;
}

bool too_long(int nlen, int clen)
{
    if (nlen > PROG_NAME_LENGTH) {
        nwwrite(2,
            "\033[1;31mError:\033[97m The program name is too long.\033[0m\n",
            54);
        return true;
    } if (clen > COMMENT_LENGTH) {
        nwwrite(2,
            "\033[1;31mError:\033[97m The comment is too long.\033[0m\n",
            49);
        return true;
    }
    return false;
}

void print_syntax_error_header(char *value)
{
    nwwrite(2, "\033[1;31mError: \033[97m", 20);
    nwwrite(2, value, (size_t)my_strlen(value));
    nwwrite(2, " syntax error.\n\033[0m", 20);
}

int *process_values(char **name, char **comment)
{
    *name += 5;
    if (*comment) *comment += 8;
    if ((**name != ' ' && **name != '\t') || *(*name + 1) != '"') {
        print_syntax_error_header("Name"); return NULL;
    } if (*comment && ((**comment != ' ' && **comment != '\t') ||
    *(*comment + 1) != '"')) {
        print_syntax_error_header("Comment"); return NULL;
    } *name += 2; if (*comment) *comment += 2;
    int nlen = get_len_to_newline_quote(*name);
    if (*(*name + nlen) != '"') {
        print_syntax_error_header("Name"); return NULL;
    } int clen = get_len_to_newline_quote(*comment);
    if (*comment && *(*comment + clen) != '"') {
        print_syntax_error_header("Comment"); return NULL;
    } if (too_long(nlen, clen)) return NULL;
    int *lengths = my_calloc(2, sizeof(int), 0);
    if (lengths == NULL) return NULL;
    lengths[0] = nlen; lengths[1] = clen;
    return lengths;
}

header_t *parse_header(string_t *string)
{
    char *comment = my_strstr(string->str, ".comment");
    char *name = my_strstr(string->str, ".name");
    if (comment == NULL) {
        nwwrite(2, NOCOM, 48);
    } if (!name) {
        nwwrite(2, NONAME,43);
        return NULL;
    }
    int *lengths = process_values(&name, &comment);
    if (lengths == NULL) return NULL;
    header_t *header = my_calloc(1, sizeof(header_t), 0);
    if (!header) return NULL;
    my_memcpy(&header->magic, &cem, 4);
    my_memcpy(header->prog_name, name, (size_t)lengths[0]);
    my_memcpy(header->comment, comment, (size_t)lengths[1]);
    free(lengths);
    return header;
}
/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠉⠉⢉⠏⠻⣍⠑⢲⠢⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣻⣿⢟⣽⠿⠯⠛⡸⢹⠀⢹⠒⣊⡡⠜⠓⠢⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⡜⣿⣷⣽⠓⠀⢠⢂⣣⠋⠂⣾⠼⢌⠳⢄⢀⡠⠜⣣⡀⠀⠀
⠀⠀⠀⠀⠀⢠⢻⢱⣭⠷⠤⢅⠴⣡⡻⠃⠀⢠⠁⠀⢀⡱⠜⠍⢔⠊⠀⠹⡄⠀
⠀⠀⠀⠀⢀⣷⠌⠚⠷⠆⠠⠶⠭⢒⣁⠀⣤⠃⣀⢔⢋⡤⠊⠑⣄⠳⣄⠀⣧⠀
⠀⠀⠀⠀⠀⠑⠦⣀⡤⣄⠄⢄⣀⣠⣒⢦⡄⠩⠷⠦⠊⠀⠀⠀⠈⠣⡏⠢⣿⠀
⠀⠀⠀⠀⠀⠀⣸⢫⠟⣝⠞⣼⢲⡞⣞⠋⠋⠉⠋⠓⡄⠀⠀⠀⠀⠀⣨⠂⢸⡅
⠀⠀⠀⠀⠀⣰⠃⡨⠊⢀⡠⡌⢘⢇⠞⠀⠀⠀⠀⠂⠡⡄⠀⠀⢀⠞⢁⠔⢹⡇
⠀⠀⠀⠀⣰⣣⠞⢀⠔⢡⢢⠇⡘⠌⠀⠀⠀⠀⠀⠀⠠⡌⠢⡔⢁⡴⠁⠀⢸⠃
⠀⠀⠀⢠⠟⠁⠠⢊⠔⣡⢸⠀⠃⠁⠀⠀⠀⠀⠀⠀⠀⣯⠂⡀⢪⡀⠀⠀⢸⠀
⠀⢀⠔⣁⠐⠨⠀⠀⠈⠀⢄⠘⡀⠀⠈⢆⠀⠀⠀⠀⡠⢁⠜⠙⢦⠙⣦⠀⢸⠀
⡴⠁⠘⡁⣀⡡⠀⠀⠴⠒⠗⠋⠉⠉⡆⠀⠆⠄⠄⠘⠀⡎⠀⠀⠀⠑⢅⠑⢼⡀
⢯⣉⣓⠒⠒⠤⠤⣄⣀⣀⣀⣀⡀⠐⠁⠀⠀⠀⠒⠀⢀⡀⠀⠀⠀⠀⠀⠑⣌⣇
⠀⠈⢳⠄⠈⠀⠤⢄⣀⠀⢈⣉⡹⠯⡟⠁⠀⠀⠀⠀⢸⠀⠀⠂⠀⠀⡠⠚⣡⡿
⠀⢠⣋⣀⣀⣀⣀⠤⠭⢛⡩⠄⠒⠩⠂⢀⠄⠀⠀⠀⠈⢢⡀⠀⡠⠋⡩⠋⠀⢳
⠀⢹⠤⠬⠤⠬⠭⣉⣉⢃⠀⠀⣀⣀⠀⠁⠀⠀⠀⠀⡞⢺⡈⠋⡢⠊⠀⠀⠀⢸
⠀⠈⡆⠁⢀⠀⠀⠀⠉⠋⠉⠓⠂⠤⣀⡀⠀⠀⠀⠀⡧⠊⡠⠦⡈⠳⢄⠀⠀⠈
⠀⠀⢹⡜⠀⠁⠀⠀⠒⢤⡄⠤⠔⠶⠒⠛⠧⠀⠀⡼⡠⠊⠀⠀⠙⢦⡈⠳⡄⠀
⠀⠀⢸⠆⠀⠈⠀⠠⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⡜⢸⠀⠀⠀⠀⠀⠀⠑⢄⠈⢲
⠀⠀⢸⢀⠇⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⡄⠊⢠⠃⠀⠀⠀⠀⠀⠀⠀⠈⡢⣸
⠀⠀⠈⠳⣤⣄⡀⠀⠀⠀⠈⠉⠉⠁⠒⠁⠀⠠⣏⠀⠀⠀⠀⠀⠀⢀⣔⠾⡿⠃
⠀⠀⠀⠀⠉⠙⠛⠒⠤⠤⣤⣄⣀⣀⣀⣔⣢⣀⣉⣂⣀⣀⣠⠴⠿⠛⠋
*/
