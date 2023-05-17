/*
** EPITECH PROJECT, 2023
** read_file.c
** File description:
** read .s file
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

void purge_spaces(char *buff, uint64_t len)
{
    char *name = my_strstr(buff, NAME_CMD_STRING);
    char *command = my_strstr(buff, COMMENT_CMD_STRING);
    int nb_spaces = 0;
    if (name) {
        name += my_strlen(NAME_CMD_STRING);
        while (name[1] == ' ' || name[1] == '\t')
            my_memmove(name, name + 1, (size_t)my_strlen(name));
        return;
    } if (command) {
        command += my_strlen(COMMENT_CMD_STRING);
        while (command[1] == ' ' || command[1] == '\t')
            my_memmove(command, command + 1, (size_t)my_strlen(command));
        return;
    } for (uint64_t i = 0; i < len; i++)
        nb_spaces = buff[i] == ' ' ? nb_spaces + 1 : nb_spaces;
    while (nb_spaces > 1) {
        char *pos = my_strrchr(buff, ' ');
        my_memmove(pos, pos + 1, (size_t)my_strlen(pos));
        nb_spaces--;
    }
}

void clean_labels(char *buff, uint64_t *len)
{
    if (my_strstr(buff, NAME_CMD_STRING) || my_strstr(buff, COMMENT_CMD_STRING))
        return;
    char *pos = my_strchr(buff, LABEL_CHAR);
    while (pos) {
        if (pos == buff)
            break;
        if (*(pos - 1) == '%')
            break;
        while (my_strchr(" \t", *(pos + 1)))
            my_memmove(pos + 1, pos + 2, (size_t)my_strlen(pos + 1));
        *len = (uint64_t)my_strlen(buff);
        pos = my_strchr(pos + 1, LABEL_CHAR);
    }
}

char *process_line(char *buff, char **file_content, uint64_t file_len)
{
    if (my_strchr(buff, COMMENT_CHAR)) {
        char *comm = my_strchr(buff, COMMENT_CHAR);
        for (; comm != buff && (*(comm - 1) == ' ' || *(comm - 1) ==
        COMMENT_CHAR); comm--);
        *comm = '\n';
        my_memset(comm + 1, (size_t)my_strlen(comm + 1), 0);
    }
    while (is_space(*buff))
        my_memmove(buff, buff + 1, (size_t) my_strlen(buff));
    uint64_t len = (uint64_t)my_strlen(buff);
    clean_labels(buff, &len);
    purge_spaces(buff, len);
    char *tmp = realloc(*file_content, len + file_len + 1 * sizeof(char));
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wanalyzer-malloc-leak"
    if (!tmp && *file_content)
        free(*file_content);
    *file_content = tmp;
    return buff;

}

char *read_s_file(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        nwwrite(2, "Error in function open: No such file or directory.\n", 51);
        return NULL;
    }
    char *file_content = NULL, *buff = NULL, *obuff = NULL;
    uint64_t file_len = 0, s = 0;
    while (getline(&obuff, &s, f) != -1) {
        buff = process_line(obuff, &file_content, file_len);
        if (!file_content) {
            free(obuff); fclose(f);
            return NULL;
        }
        my_strcpy(file_content + file_len, buff);
        file_len += (uint64_t)my_strlen(buff);
        free(obuff);
        obuff = buff = NULL;
    } free(obuff);
    fclose(f);
    return file_content;
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
