/*
** EPITECH PROJECT, 2023
** my_powf.c
** File description:
** powf implementation
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
#include <stdbool.h>

float my_powf(float x, int y)
{
    float result = 1.f;
    bool negative = y < 0;
    if (negative)
        y = -y;
    while (y > 0) {
        if (y % 2 == 1)
            result *= x;
        x *= x;
        y /= 2;
    }
    return negative ? 1.f / result : result;
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
