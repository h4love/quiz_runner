typedef struct question {
    char* query; //Вопрос
    char* a[4]; //Ответы
    int right; //Номер правильного
} qst;

int read_db(FILE**, char*);
int next_str(FILE**, char*, int);
int find_topic(FILE**, char*, int*, int*);
qst* get_question(FILE**, int);
int sym_count(char*, char);
