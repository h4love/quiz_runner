#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <ctype.h>

//Реализация getch() из conio.h
char getch()
{
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

//Ввод символа по маске
char enter_sym(char* mask)
{
    char result;
    do {
        result = toupper(getch());
    } while (!strchr(mask, result));
    return result;
}
