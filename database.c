#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <locale.h>
#include "database.h"

/*Чтение базы данных и вывод в файл
Возвращает -1 при ошибке и 0 при успешном чтении
Пример использования: read_db(&file, filename)*/

int read_db(FILE** file, char* filename)
{
    *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    else {
        return 0;
    }
}

/*Переключение строки и вывод в параметр string 
Возвращает -1 при конце файла, в других случаях возвращает номер строки (i + 1)
Пример использования: i = get_str(&file, string, i)*/

int next_str(FILE** file, char string[512], int i)
{
    char* temp;
    char tempstr[512];

    temp = fgets(tempstr, 512, *file);
    if (temp == NULL) {
        return -1;
    }
    else {
        char* pos;
        if ((pos = strchr(tempstr, '\n')) != NULL) {
            *pos = '\0';
        }
        strcpy(string, tempstr);
        return i + 1;
    }
}

/*Ищет название темы и номера строк с диапазоном вопросов 
Возвращает -1 при ошибке и 0 при успешном выполнении
В параметр char* string записывается название темы, в int* start начало вопросов по теме, в int* end конец строк с вопросами
Пример использования: find_topic(&file, string, &a, &b)*/

int find_topic(FILE** file, char* string, int* start, int* end)
{
    fseek(*file, 0, SEEK_SET); //Перемотка в начало файла
    int i = 0, j, li, equal = 0;
    char str[512];
    char pattern[] = "<.*>"; //Маска регулярного выражения
    setlocale(LC_ALL, (const char*)"ru."); //Кириллические символы

    while (equal < 2) {
        i = next_str(file, str, i);
        if (i == -1) {
            if (equal == 1) {
                *end = li - 1;
                *start = *start + 1;
            }
            break;
        }
        pcre* re; //Переменная для результата компиляции
        int options = 0; //Опции компиляции
        int erroffset;
        const char* error;

        re = pcre_compile((char*)pattern, options, &error, &erroffset, NULL); //Компилируем регулярное выражение с маской

        if (re) {
            int count = 0;
            int ovector[30]; //Задаём массив для символов
            count = pcre_exec(re, NULL, (char*)str, strlen(str), 0, 0, ovector, 30); //Проверяем на соответствие маске
            if (count) {
                for (int c = 0; c < 2 * count; c += 2) {
                    if (ovector[c] >= 0) {
                        if (equal == 1) { //Конец строк с вопросами
                            *end = i - 2;
                            *start = *start + 1;
                            equal = 2;
                            break;
                        }
                        if ((*start == (i - 1)) && (equal == 0)) { //Начало строк с вопросами
                            char temp[ovector[c + 1]];
                            for (j = 1; j < ovector[c + 1] - 1; j++) {
                                temp[j - 1] = str[j];
                            }
                            temp[ovector[c + 1] - 2] = '\0';
                            strcpy(string, temp); //Записываем название темы
                            equal = 1;
                        }
                    }
                }
            }
        }
        pcre_free((void*)re); //Высвобождаем занятую ранее память

        li = i;
    }

    if (equal == 2) {
        return 0;
    }
    else {
        return -1;
    }
}

/*Функция для вывода строк с вопросами в структуру qst
Возвращает NULL при ошибке или адрес при успешном выполнении
Параметр FILE** file принимает на вход файл с вопросами, int line указывает на строку с вопросом
Пример использования: qst* now = get_question(&file, i)*/

qst* get_question(FILE** file, int line)
{
    fseek(*file, 0, SEEK_SET); //Отматываем файл в начало
    char str[512]; //Строка
    int i = -1, index;
    qst* p = malloc(sizeof(qst));

    while (i != line) { //Пересчёт линий
        i = next_str(file, str, i);
        if (i == -1) {
            break;
        }
    }

    if (i != -1) { //Если линия найдена
        int temp = sym_count(str, '|');
        if (temp == 5) {
            int id = 0;
            int size = 0;
            int step = 0;

            //Вопрос

            while (str[size + step] != '|') {
                size++;
            }
            p->query = malloc((size) * sizeof(char));
            while (id < size) {
                p->query[id] = str[id + step];
                id++;
            }
            p->query[id] = '\0';
            step = size + 1;
            id = 0;
            size = 0;

            //Ответы

            for (index = 0; index < 4; index++) {
                while (str[size + step] != '|') {
                    size++;
                }
                p->a[index] = malloc((size + 1) * sizeof(char));
                while (id < size) {
                    p->a[index][id] = str[id + step];
                    id++;
                }
                p->a[index][id] = '\0';
                step = step + size + 1;
                id = 0;
                size = 0;
            }

            //Номер правильного ответа

            p->right = str[step] - 48;

            return p;
        }
        else { //Линия не соответствует формату
            return NULL;
        }
    }
    else { //Если линию найти не удалось
        return NULL;
    }
}

/*Функция для подсчёта кол-ва символов в строке
Возвращает число символов
Параметр char* origin - строка для поиска, char sym - искомый символ
Пример использования: int temp = sym_count(str, '|')*/

int sym_count(char* origin, char sym)
{
    int i = 0, count = 0;
    while (origin[i] != '\0') {
        if (origin[i] == sym) {
            count++;
        }
        i++;
    }
    return count;
}
