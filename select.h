#include "list.h"


void select(struct node* head, int n, const char* fields) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }

    const char* del_serv = ",";
    char tmp[1024];
    strcpy(tmp, fields);
    char* service = strtok(tmp, del_serv);
    int i = 0;
    char flds[10][30];

    while (service) {
        strcpy(flds[i], service);
        service = strtok(NULL, del_serv);
        i++;
    }

    for (int j=0; j<i; j++) {
        if (strcmp(flds[j], "last_name") == 0) 
            printf("%s=%s ", flds[j], head->data.last_name);
        if (strcmp(flds[j], "first_name") == 0) 
            printf("%s=%s ", flds[j], head->data.first_name);
        if (strcmp(flds[j], "middle_name") == 0) 
            printf("%s=%s ", flds[j], head->data.middle_name);
        if (strcmp(flds[j], "number") == 0) 
            printf("%s=%s ", flds[j], head->data.number);   
        if (strcmp(flds[j], "services") == 0) {
            printf("%s=[", flds[j]);
            int first=1;
            for (int k = 0; k < MAX_SERVICES; k++) {                
                if (head->data.services[k][0] != '\0') {
                    if (first == 1) {
                        printf("%s", head->data.services[k]);
                        first = 0;
                    }
                    else
                        printf(",%s", head->data.services[k]);
                } else {
                    break;
                }
            }         
            printf("] ");
        }           
    }

    printf("\n");
}