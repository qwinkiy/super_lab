// Online C compiler to run C program online

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX_SERVICES 14
#define SERVICE_NAME_LENGTH 8

struct row {
    char last_name[20];
    char first_name[20];
    char middle_name[20];
    char number[15];
    char services[MAX_SERVICES][SERVICE_NAME_LENGTH];
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

int read_db();

 
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
    // print_row(r);

    read_db();    

    return;
}

int read_db() {

    FILE* file = fopen("DB.csv", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char buffer[1024];
    struct row clients[100];
    int num_clients = 0;

    // Чтение заголовка
    fgets(buffer, sizeof(buffer), file);

    // Чтение строк
    while (fgets(buffer, sizeof(buffer), file)) {
        // Разбиение строки на поля
        const char* delim = ";";

        char* last_name = strtok(buffer, delim);
        char* first_name = strtok(NULL, delim);
        char* middle_name = strtok(NULL, delim);
        char* number_str = strtok(NULL, delim);
        char* services_str = strtok(NULL, "\n");

        // Заполнение структуры клиента
        if (1 || last_name && first_name && middle_name && number_str && services_str) 
        {
            strcpy(clients[num_clients].last_name, last_name);
            strcpy(clients[num_clients].first_name, first_name);
            strcpy(clients[num_clients].middle_name, middle_name);
            strcpy(clients[num_clients].number, number_str);

            // Разбиение списка услуг на отдельные названия
            const char* del_serv = " ";
            char* service = strtok(services_str, del_serv);
            int i = 0;
            while (service && i < MAX_SERVICES) {
                strncpy(clients[num_clients].services[i], service, SERVICE_NAME_LENGTH);
                service = strtok(NULL, del_serv);
                i++;
            }

            num_clients++;
        }
    }

    // Вывод информации о клиентах
    for (int i = 0; i < num_clients; i++) {
        // printf("%s\n", clients[i].number);
        printf("%s %s %s, номер: %s, услуги:", clients[i].last_name, clients[i].first_name, clients[i].middle_name, clients[i].number);
        for (int j = 0; j < MAX_SERVICES; j++) {
            if (clients[i].services[j][0] != '\0') {
                printf(" %s", clients[i].services[j]);
            } else {
                break;
            }
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}