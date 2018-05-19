#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "database.h"
#include "output.h"
#include "getch.h"

int main()
{
    setlocale(LC_ALL, (const char*)"ru.");

    FILE* file;
    char string[512];
    char tempstring[512];
    char filename[48];
    char nickname[24] = "";
    char* pos;
    int temp;

    int a = 0, b = 0, z = 0, i, x = 0;
    int filename_a = 0, nickname_a = 0, topic_a = 0;
    
    //qst* list[15];
    
    char button;
    int screen = 0;

    /*for(i = a; i <= b; i++){
			        now[i-a] = get_question(&file, i);
		        }*/

    while (1) {
        switch (screen) { //Экраны
        case 0:
            if (filename_a != 0) {
                if (nickname_a != 0) {
                    print_menu(0, nickname, filename);
                }
                else {
                    print_menu(0, NULL, filename);
                }
            }
            else {
                if (nickname_a != 0) {
                    print_menu(0, nickname, NULL);
                }
                else {
                    print_menu(0, NULL, NULL);
                }
            }
            button = enter_sym("1SCQ");
            switch (button) {
            case '1':
                screen = 1;
                break;
            case 'S':
                screen = 2;
                break;
            case 'C':
                screen = 3;
                break;
            case 'Q':
                printf("\n");
                exit(0);
                break;
            }
            break;
        case 1:
            i = 0;
            if ((filename_a == 0) || (nickname_a == 0)) {
                screen = 0;
                break;
            }
            if (topic_a != 0){
                print_menu(1, string, NULL);
            } else {
                print_menu(1, NULL, NULL);
            }
            while(i == 0){
                button = enter_sym("12TM");
                switch (button) {
                case '1':
                    if (topic_a == 1) {
                        i = 1;
                        screen = 9;
                    } else {
                        i = 0;
                    }
                    break;
                case '2':
                    if (topic_a == 1) {
                        i = 1;
                        screen = 9;
                    } else {
                        i = 0;
                    }
                    break;
                case 'T':
                    i = 1;
                    screen = 4;
                    break;
                case 'M':
                    i = 1;
                    screen = 0;
                    break;
                }
            }
            break;
        case 2:
            print_menu(2, "start", NULL);
            while (1) {
                fgets(filename, 48, stdin);
                if ((pos = strchr(filename, '\n')) != NULL) {
                    *pos = '\0';
                }
                temp = read_db(&file, filename);
                if (temp == -1) {
                    print_menu(2, "error", NULL);
                }
                else {
                    filename_a = 1;
                    break;
                }
            }
            screen = 0;
            break;
        case 3:
            if (nickname_a != 0) {
                print_menu(3, nickname, NULL);
                nickname_a = 0;
            }
            else {
                print_menu(3, NULL, NULL);
            }
            while ((strlen(nickname) < 3) || (nickname_a == 0)){
                fgets(nickname, 24, stdin);
                
                if ((pos = strchr(nickname, '\n')) != NULL) {
                    *pos = '\0';
                }
                
                if (strlen(nickname) < 3) {
                    print_menu(3, NULL, "error");
                } else {
                    nickname_a = 1;
                }
            }
            screen = 0;
            break;
        case 4:
            a = 0; b = 0; z = 0; x = 0;
            strcpy(tempstring,string);
            z = find_topic(&file, string, &a, &b);
            if (topic_a == 1) {
                print_menu(4, tempstring, string);
            }
            else {
                print_menu(4, NULL, string);
            }

            while(x == 0){
                button = enter_sym("SCM");
                switch (button) {
                case 'C':
                    if (z == -1){
                        a = 0;
                    } else {
                        a = b+1;
                    }
                    z = find_topic(&file, string, &a, &b);
                    if (topic_a == 1) {
                        print_menu(4, tempstring, string);
                    }
                    else {
                        print_menu(4, NULL, string);
                    }
                    
                    break;
                case 'S':
                    x = 1;
		            topic_a = 1;
                    screen = 1;
                    break;
                case 'M':
                    x = 1;
                    screen = 1;
                    break;
                }
	        }
            break;
        }
    }
    return 0;
}
