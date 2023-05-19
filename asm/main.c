/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "my.h"
#include "asm.h"
#include "parser.h"

void nwwrite(int fd, char array buf, size_t size)
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    write(fd, buf, size);
    #pragma GCC diagnostic pop
}

/**
void swap_uint32(uint32_t ptr little)
{
    *little = (*little >> 24) |
        ((*little << 8) & 0x00FF0000) |
        ((*little >> 8) & 0x0000FF00) |
        (*little << 24);
}
*/
void free_file_processing(token_t array tokens, header_t ptr header,
    string_t content)
{
    for (uint32_t i = 0; tokens[i].type != TOKEN_END; i++)
        free_string(tokens[i].token);
    free(tokens);
    free(header);
    free_string(content);
    free_table(hashtable);
}

void handle_error(string_t content, header_t* header)
{
    free_string(content);
    free(header);

    nwwrite(2, "\033[1;31mError Detected!\033[97m Aborting!\033[0m\n", 43);
}

int process_file(uint16_t nb_of_line_in_file, string_t content,
    header_t* header)
{
    char* end = NULL;
    uint16_t line_nb = 1;
    uint32_t nb_parsed_lines = 0;
    header = parse_header(&content, &end, &line_nb);
    if (!header) {
        handle_error(content, header);
        return 84;
    }
    init_hashtable();
    token_t array tokens = tokenize(end, line_nb, nb_of_line_in_file);
    if (!tokens) {
        handle_error(content, header);
        return 84;
    }
    line_t array lines = parser(tokens, nb_of_line_in_file, line_nb,
        &nb_parsed_lines);
    if (lines) free(lines);
    free_file_processing(tokens, header, content);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2) return 84;
    if (!my_strrchr(av[1], '.') || my_strcmp(my_strrchr(av[1], '.'), ".s"))
        return 84;
    uint16_t nb_of_line_in_file = 0;
    char* fcontent = read_s_file(av[1], &nb_of_line_in_file);
    if (!fcontent) {
        nwwrite(2, "\033[1;31mError Detected!\033[97m Aborting!\033[0m\n", 43);
        return 84;
    }
    string_t content = create_string(fcontent);
    free(fcontent);
    if (content.len == 0) {
        handle_error(content, NULL);
        return 84;
    }
    return process_file(nb_of_line_in_file, content, NULL);
}
