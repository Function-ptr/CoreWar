/*
** EPITECH PROJECT, 2023
** process_file.c
** File description:
** process .s file
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

header_t ptr get_header(string_t ptr content, char ptr ptr end,
    uint32_t ptr line_nb)
{
    header_t ptr header = parse_header(content, end, (uint16_t*)line_nb);
    if (!header) {
        free_file_processing(NULL, header, *content, NULL);
        return NULL;
    }
    return header;
}

token_t array get_tokens(char *end, uint32_t ptr array line_data, header_t
*header,
    string_t content)
{
    uint16_t line_nb = (uint16_t)*line_data[1];
    uint16_t nb_of_line_in_file = (uint16_t)*line_data[0];
    token_t array tokens = tokenize(end, line_nb, nb_of_line_in_file);
    if (!tokens) {
        free_file_processing(tokens, header, content, NULL);
        return NULL;
    }
    return tokens;
}

line_t array get_lines(uint32_t ptr array data, header_t *header,
    token_t array tokens, string_t content)
{
    uint16_t line_nb = (uint16_t)*data[1];
    uint16_t nb_of_line_in_file = (uint16_t)*data[0];
    uint32_t ptr nb_parsed_lines = data[2], ptr body_size = data[3];
    line_t array lines = parser(tokens, nb_of_line_in_file, line_nb,
    nb_parsed_lines);
    if (!lines) {
        free_file_processing(tokens, header, content, lines);
        return NULL;
    }
    for (uint32_t i = 0; i < *nb_parsed_lines; i++)
        *body_size += lines[i].bytes_size;
    return lines;
}

bool write_content_to_file(uint32_t ptr array data, header_t *header,
    line_t array lines, char *file_name)
{
    uint32_t nb_parsed_lines = *data[2], body_size = *data[3];
    string_t output; output.len = 0;
    header->prog_size = (int)body_size;
    output.str = my_calloc(body_size, sizeof(char), 0);
    write_lines_to_buffer(lines, &output, nb_parsed_lines);
    if (write_buffer_to_file(file_name, output, header) == -1) {
        free_string(output);
        return true;
    }
    free_string(output);
    return false;
}

int process_file(uint32_t nb_line_file, string_t content, char* file_name)
{
    char* end = NULL;
    uint32_t line_nb = 1, nb_p_lines, body_size;
    uint32_t ptr data[4] = {&nb_line_file, &line_nb, &nb_p_lines, &body_size};
    init_hashtable();
    header_t ptr header = get_header(&content, &end, &line_nb);
    if (!header)
        return 84;
    token_t array tokens = get_tokens(end, data, header, content);
    if (!tokens)
        return 84;
    line_t array lines = get_lines(data, header, tokens, content);
    if (!lines)
        return 84;
    bool status = write_content_to_file(data, header, lines, file_name);
    free_file_processing(tokens, header, content, lines);
    if (status)
        return 84;
    return 0;
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
