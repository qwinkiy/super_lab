#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define MAX_SERVICES 14
#define SERVICE_NAME_LENGTH 8

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

            insert_back(&head, clients[num_clients]);
            
            num_clients++;
        }
    }

    // print_list(head);

    fclose(file);
    return head;
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
    // print_row(r);

    struct node* head = read_db();  
    print_list(head);

    delete_node(&head, 1);
    printf("\nAfter deleting\n");

    print_list(head);

    struct row temp = {"Hello", "World", "!", "89173456789", {"s1","s2","s333"}};
    insert_back(&head, temp);

    printf("\nAfter inserting\n");

    print_list(head);

    return;
}

