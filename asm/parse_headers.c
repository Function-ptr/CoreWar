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

int process_name(char **name)
{
    *name += 5;
    if ((**name != ' ' && **name != '\t') || *(*name + 1) != '"') {
        print_syntax_error_header("Name");
        return 0;
    }
    *name += 2;
    int nlen = get_len_to_newline_quote(*name);
    if (*(*name + nlen) != '"') {
        print_syntax_error_header("Name");
        return 0;
    }
    if (nlen > PROG_NAME_LENGTH) {
        nwwrite(2,
            "\033[1;31mError:\033[97m The program name is too long.\033[0m\n",
            54);
        return 0;
    }
    return nlen;
}

int process_comment(char **comment)
{
    *comment += 8;
    if (*comment && ((**comment != ' ' && **comment != '\t') ||
    *(*comment + 1) != '"')) {
        print_syntax_error_header("Comment");
        return 0;
    }
    *comment += 2;
    int clen = get_len_to_newline_quote(*comment);
    if (*comment && *(*comment + clen) != '"') {
        print_syntax_error_header("Comment");
        return 0;
    }
    if (clen > COMMENT_LENGTH) {
        nwwrite(2,
            "\033[1;31mError:\033[97m The comment is too long.\033[0m\n",
            49);
        return 0;
    }
    return clen;
}

header_t *create_and_fill_header(char ptr ptr end, char ptr comment,
    char ptr name, int nlen)
{
    header_t *header = my_calloc(1, sizeof(header_t), 0);
    if (!header) return NULL;
    my_memcpy(&header->magic, &cem, 4);
    my_memcpy(header->prog_name, name, (size_t)nlen);
    if (comment) {
        if (comment != *end) {
            nwwrite(2, COMAFNAME, 65);
            free(header);
            return NULL;
        }
        int clen = process_comment(&comment);
        my_memcpy(header->comment, comment, (size_t)clen);
        end += 11 + clen;
    } else
        nwwrite(2, NOCOM, 48);
    return header;
}

header_t *parse_header(string_t ptr string, char ptr ptr endptr,
    uint16_t ptr line_nb)
{
    char ptr end = string->str, ptr name = my_strstr(string->str, ".name");
    char ptr comment = my_strstr(string->str, ".comment");
    if (!name) {
        nwwrite(2, NONAME,43);
        return NULL;
    }
    for (; is_space(*end); ++end)
        *line_nb = *end == '\n' ? *line_nb + 1 : *line_nb;
    if (end != name) {
        nwwrite(2, NAMELINE1, 75);
        return NULL;
    }
    int nlen = process_name(&name);
    if (nlen == 0) return NULL;
    end += nlen + 8;
    for (; is_space(*end); ++end)
        *line_nb = *end == '\n' ? *line_nb + 1 : *line_nb;
    header_t *header = create_and_fill_header(&end, comment, name, nlen);
    *endptr = end;
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
