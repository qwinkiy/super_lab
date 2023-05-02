#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "select.h"
#include "read.h"
#include "filter.h"

struct node* read_db() {

    FILE* file = fopen("DB.csv", "r");
    if (!file) {
        printf("Error opening file\n");
        return NULL;
    }

    char buffer[1024];
    struct row clients[100];
    int num_clients = 0;

    int db_size = -1;
    while (fgets(buffer, sizeof(buffer), file)) {
        db_size++;
    }

    printf("число строк %d\n", db_size);
    fclose(file);

    file = fopen("DB.csv", "r");
    
    // Чтение заголовка
    fgets(buffer, sizeof(buffer), file);

    struct node* head = NULL;

    // Чтение строк
    while (fgets(buffer, sizeof(buffer), file)) {
        // Разбиение строки на поля
        const char* delim = ";";

        char* last_name = strtok(buffer, delim);
        char* first_name = strtok(NULL, delim);
        char* middle_name = strtok(NULL, delim);
        char* number_str = strtok(NULL, delim);
        char* discount_str = strtok(NULL, delim);
        char* bonus_str = strtok(NULL, delim);
        char* services_str = strtok(NULL, "\n");

        // Заполнение структуры клиента
        if (1 || last_name && first_name && middle_name && number_str && services_str) 
        {
            strcpy(clients[num_clients].last_name, last_name);
            strcpy(clients[num_clients].first_name, first_name);
            strcpy(clients[num_clients].middle_name, middle_name);
            strcpy(clients[num_clients].number, number_str);
            clients[num_clients].discount_id = atoi(discount_str);
            clients[num_clients].bonus_id  = atoi(bonus_str);

            // Разбиение списка услуг на отдельные названия
            const char* del_serv = " ";
            char* service = strtok(services_str, del_serv);
            int i = 0;
            while (service && i < MAX_SERVICES) {
                strncpy(clients[num_clients].services[i], service, SERVICE_NAME_LENGTH);
                service = strtok(NULL, del_serv);
                i++;
            }

            insert_back(&head, clients[num_clients]);
            
            num_clients++;
        }
    }

    fclose(file);
    return head;
}
 
void main()
{
    struct node* head = read_db();  
    print_list(head);

    delete_node(&head, 1);
    printf("\nAfter deleting\n");

    print_list(head);

    struct row temp = {"last", "FIRST", "middle", "89173456789", {"s1","s2","s333"}};
    insert_back(&head, temp);

    printf("\nAfter inserting\n");

    print_list(head);

    printf("\n\nOne node\n");

    head = read_command(head);


    // Не поднимать!
    free_list(head);
    print_mem();

    return;
}

// last first middle
// last: Dolgov first: Ivan mid: Vovkin, номер 89173456778, дисконт: 1, бонус: 1, услуги: calls sms gprs internets1 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10
// last: Vologin first: Artem mid: Ufydarovich, номер 89881122333, дисконт: 3, бонус: 3, услуги: calls sms
// last: Ivanov first: Artem mid: Ufydarovich, номер 88005553535, дисконт: 3, бонус: 3, услуги: calls sms
// last: last first: FIRST mid: middle, номер 89173456789, дисконт: 0, бонус: 0, услуги: s1 s2 s333

