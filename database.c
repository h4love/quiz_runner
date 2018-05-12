#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Чтение базы данных и вывод в файл
Возвращает -1 при ошибке и 0 при успешном чтении
Пример использования: read_db(&file, filename)*/

int read_db(FILE** file, char* filename)
{
	*file = fopen(filename, "r");
	if (file == NULL){

		return -1;
	} else {
		return 0;
	}
}

/*Переключение строки и вывод в параметр string 
Возвращает -1 при конце файла, в других случаях возвращает номер строки (index + 1)
Пример использования: i = get_str(&file, string, i)*/

int next_str(FILE** file, char string[512], int i)
{
	char *temp;
	char tempstr[512];
	
	temp = fgets(tempstr, 512, *file);
	if (temp == NULL){
		return -1;
	} else {
		char *pos;
		if ((pos=strchr(tempstr, '\n')) != NULL){
   			*pos = '\0';
		}
		strcpy(string, tempstr);
		return i+1;
	}
}
