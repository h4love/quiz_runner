#include <ctype.h>
#include <stdio.h>

//Функция для проверки правильности введённого никнейма
//Условие - только буквы латинского алфавита
int name_verification()
{
    int k=0;
    int c=0;
    int ctr = 0; // счетчик символов в строке
  
    char str[20] = "Fa"; // символьная строка
    printf ("Введите Никнейм, используя только буквы латинского алфавита: ");
    scanf("%s", str);
 
    while ( str[ctr] )  // пока не конец строки
    {
      if ( isalpha(str[ctr]) ) // если текущий символ строки буква
          k=1; // Символ - буква
      else
          c=1; // Символ - не буква
      ctr++; // инкремент счётчика
    } // конец while

 
    return c;
}
/* для проверки работоспособности функции 
 в оригинальном main можно сделать также
int main ()
{
int s;
s = name_verification();
if (s == 1)
printf ("Данные введены некоректно\n");
else printf ("Данные введены коректно\n");
return 0;
}*/

//реализовать запись имени в текстовый файл


