// Online C compiler to run C program online

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

struct row {
    char last_name[20];
    char first_name[20];
    char middle_name[20];
    int number;
    char services[14][8];
//     last_name:string;                                                                  // Фамилия владельца
// first_name:string;                                                                     // Имя владельца
// middle_name:string;                                                               // Отчество владельца
// number:phone;                                                                         // Номер телефона
// services:set of ['calls','sms','gprs','internet','s1','s2','s3',...,'s10'];
};

struct command{
    int command; // 0 - select, 1 - insert
    char* fileds; // first_name, last_name, number
    char* cond; //  ""
};

int pars_command(const char* command, int strlen){
 

}


void print_row(struct row r) {
    printf("row: %s %s %s\n", r.last_name, r.first_name, r.middle_name);
    printf("services: ");
    for (int i=0; i<14; i++)
        printf("%s ", r.services[i]);
    printf("\n");
}

 
void main()
{
    struct row r;
    printf("size of: %lu\n", sizeof(r));
    strcpy(r.first_name, "sdfsdfd");
    strcpy(r.last_name, "123123132");
    for (int i=0; i<14; i++)
        strcpy(r.services[i], "");
    strcpy(r.services[0], "calls");
    strcpy(r.services[1], "sms");
    strcpy(r.services[3], "gprs");
    // r.last_name = "3r234234";
    print_row(r);
    FILE *file = fopen("1.txt","w");
    fprintf(file, "out");
    fclose(file); 
    file = fopen("1.txt", "r");
    char line[255];
    fgets(line, 255, file);
    printf("read line: %s\n", line);
    fclose(file);

    int* mas = NULL;
    int N = 10;
    mas = (int*)malloc(sizeof(int) * N);

    if (mas != NULL) {
        for (int i=0; i < N; ++i) {
            mas[i] = i;
        }
    }

    free(mas);
 
    printf("hello world!");
    const char* str = "slfhdfskgjfdgk";
    printf("%s\n", str);
    return;
}