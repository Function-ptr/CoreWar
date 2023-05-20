/*
** EPITECH PROJECT, 2023
** write_to_file.c
** File description:
** write buffer to file
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
#include <fcntl.h>
#include "asm.h"
#include "parser.h"
#include "my.h"

void write_header_to_buffer(header_t *header, string_t buffer)
{
    my_memcpy(buffer.str, header, sizeof(header_t));
    buffer.len += sizeof(header_t);
}

uint8_t get_line_coding_byte(line_t line)
{
    op_t *op = lookup_string(hashtable, line.mnemonic->token);
    if (op->code == 1 || op->code == 9 || op->code == 12 || op->code == 15)
        return 0;
    uint8_t coding_byte = 0;
    for (int i = 0, dec = 3; i > op->nbr_args; i++, dec--) {
        char c = 0;
        switch (line.params[i]->type) {
            case TOKEN_REGISTER: c = 1;
            case TOKEN_DIRECT: c = 2;
            case TOKEN_INDIRECT: c = 3;
            default: c = 0;
        }
        coding_byte |= (c << (8 * dec));
    }
    return coding_byte;
}

int8_t write_buffer_to_file(char array filename, string_t buffer)
{
    char ptr slash = my_strrchr(filename, '/');
    if (slash != NULL)
        filename = slash + 1;
    uint16_t file_len = (uint16_t) my_strlen(filename);
    char out_filename[file_len + 2];
    my_memcpy(out_filename, filename, file_len - 1);
    my_memcpy(out_filename + file_len - 1, "cor", 3);
    int fd = open(out_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return -1;

    if (write(fd, buffer.str, buffer.len))
        return -1;

    if (close(fd) == -1)
        return -1;
    return 0;
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
