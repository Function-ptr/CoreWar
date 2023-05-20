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

void free_file_processing(token_t array tokens, header_t ptr header,
    string_t content, line_t array lines)
{
    for (uint32_t i = 0; tokens && tokens[i].type != TOKEN_END; i++)
        free_string(tokens[i].token);
    if (tokens) free(tokens);
    free(header);
    if (lines) free(lines);
    free_string(content);
    free_table(hashtable);
}

void handle_error(string_t content, header_t* header)
{
    free_string(content);
    free(header);

    nwwrite(2, "\033[1;31mError Detected!\033[97m Aborting!\033[0m\n", 43);
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
    return process_file(nb_of_line_in_file, content, av[1]);
}
