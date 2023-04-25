/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** Concatenates 2 strings
*/

int my_strlen(char *str);

char *my_strcat(char *dest, char const *src)
{
    int len = my_strlen(dest);
    int i = 0;
    while (src[i]) {
        dest[len + i] = src[i];
        i++;
    }
    dest[len + i] = '\0';
    return (dest);
}
