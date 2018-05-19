#include <stdio.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

void rs()
{
    char* reset = "\033[0m";
    printf("%s", reset);
}

void print_header()
{
    char* gbold = "\033[38;48;1;214m";
    char* yellow = "\033[38;5;220m";
    char* gold = "\033[38;5;214m";

    clear();
    printf("\n\n%s    ████████  ██    ██  ██  ████████", yellow);
    printf("\n    ██    ██  ██    ██  ██        ██");
    printf("\n    ██    ██  ██    ██  ██      ██");
    printf("\n%s    ████  ██  ██    ██  ██    ██", gold);
    printf("\n    ████████  ████  ██  ██  ██");
    printf("\n          ██  ████████  ██  ████████");
    printf("\n");
    printf("\n    %s████%s██%s  R  U  N  N  E  R  %s██%s████\n", gold, yellow, gbold, yellow, gold);
}

void print_menu(int screen, char* arg1, char* arg2)
{
    char* button = "\033[0;48;5;233;38;5;15m";
    char* text = "\033[0;49;38;5;214m";
    char* subtext = "\033[0;49;38;5;248m";
    char* red = "\033[0;49;38;5;196m";
    char* gbold = "\033[1;49;39m";

    print_header();

    switch (screen) {
    case 0:
        if (arg1 != NULL) {
            printf("\n    %sИгрок: %s%s\n", gbold, text, arg1);
        }
        else {
            printf("\n    %sИгрок не выбран\n", red);
        }

        if (arg2 != NULL) {
            printf("    %sСловарь: %s%s\n", gbold, text, arg2);
        }
        else {
            printf("    %sСловарь не выбран\n", red);
        }

        printf("\n       %s 1 %s  Начать игру\n", button, gbold);
        printf("\n       %s S %s  Выбрать словарь\n", button, gbold);
        printf("\n       %s C %s  Выбрать игрока\n", button, gbold);
        printf("\n       %s Q %s  Выход\n\n       ", button, gbold);
        rs();
        break;
    case 1:
        if (arg1 != NULL) {
            printf("\n    %sТема: %s%s\n", gbold, text, arg1);
        }
        else {
            printf("\n    %sТема не выбрана\n", red);
        }

        printf("    %sEasy - 8 вопр. Hard - 15 вопр.\n", subtext);

        printf("\n       %s 1 %s  Easy\n", button, gbold);
        printf("\n       %s 2 %s  Hard\n", button, gbold);
        printf("\n       %s T %s  Выбрать тему\n", button, gbold);
        printf("\n       %s M %s  Главное меню\n\n       ", button, gbold);
        rs();
        break;
    case 2:
        if (strcmp(arg1, "start") >= 0) {
            printf("\n    %sВведите адрес словаря:\n\n       ", gbold);
        }
        else {
            printf("\n    %sФайл не найден, повторите\n\n       ", red);
        }
        rs();
        break;
    case 3:
        if (arg1 != NULL) {
            printf("\n    %sВведите новый никнейм\n", gbold);
            printf("    %sСейчас ваш ник: %s\n\n       ", subtext, arg1);
            rs();
        }
        else {
            if (arg2 == NULL) {
                printf("\n    %sВведите никнейм:\n\n       ", gbold);
            }
            else {
                printf("\n    %sПопробуйте другой ник\n\n       ", red);
                rs();
            }
        }

        rs();
        break;
    case 4:
        if (arg1 != NULL) {
            printf("\n    %sСейчас ваша тема: %s\n", gbold, arg1);
	        printf("    %sИспользуйте %s C %s для переключения\n", subtext,button,subtext);
            printf("    %sНажмите %s S %s для выбора темы \n", subtext,button,subtext);
            printf("\n    %s%s", text,arg2);
            
        }
        else {
            printf("\n    %sВыберите тему\n\n", gbold);
            printf("    %sИспользуйте %s C %s для переключения\n", subtext,button,subtext);
            printf("    %sНажмите %s S %s для выбора темы \n", subtext,button,subtext);
            printf("\n    %s%s", text,arg2);
        }
        rs();
        break;
    }
}

