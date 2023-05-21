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
#include "my.h"

void swap_uint32(uint32_t ptr little)
{
    *little = (*little >> 24) |
        ((*little << 8) & 0x00FF0000) |
        ((*little >> 8) & 0x0000FF00) |
        (*little << 24);
}

int64_t write_header_to_file(header_t *header, int fd)
{
    uint32_t bsize = (uint32_t)header->prog_size;
    swap_uint32(&bsize);
    header->prog_size = (int)bsize;
    return write(fd, header, sizeof(header_t));
}

uint8_t get_line_coding_byte(line_t line)
{
    op_t *op = lookup_string(hashtable, line.mnemonic->token);
    if (op == NULL)
        return 0;
    if (op->code == 1 || op->code == 9 || op->code == 12 || op->code == 15)
        return 0;
    uint8_t coding_byte = 0;
    for (int i = 0, dec = 3; i < op->nbr_args; i++, dec--) {
        char c = 0;
        if (line.params[i]->type == TOKEN_REGISTER) c = 1;
        if (line.params[i]->type == TOKEN_DIRECT) c = 2;
        if (line.params[i]->type == TOKEN_INDIRECT) c = 3;
        coding_byte |= (uint8_t)(c << (2 * dec));
    }
    return coding_byte;
}

void write_lines_to_buffer(line_t array lines, string_t ptr buffer,
    uint32_t nb_lines)
{
    for (uint32_t i = 0; i < nb_lines; i++) {
        translate_mnemonic(lines[i].mnemonic, buffer);
        uint8_t coding_byte = get_line_coding_byte(lines[i]);
        if (coding_byte)
            buffer->str[buffer->len++] = (char)coding_byte;
        translate_params(lines[i], buffer);
    }
}

int8_t write_buffer_to_file(char array filename, string_t buffer,
    header_t ptr header)
{
    char ptr slash = my_strrchr(filename, '/');
    if (slash != NULL)
        filename = slash + 1;
    uint16_t file_len = (uint16_t) my_strlen(filename);
    char out_filename[file_len + 3];
    my_memset(out_filename, file_len + 3, 0);
    my_memcpy(out_filename, filename, file_len - 1);
    my_memcpy(out_filename + file_len - 1, "cor", 3);
    int fd = open(out_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) return -1;
    if (write_header_to_file(header, fd) != sizeof(header_t)) return -1;
    if (write(fd, buffer.str, buffer.len) != (int64_t)buffer.len)
        return -1;
    if (close(fd) == -1) return -1;
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
