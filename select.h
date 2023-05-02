#pragma once
#include "mem_calc.h"
#include "list.h"
#include "filter.h"


void exec_select(struct node* head, const char* cond, const char* fields) {
    struct node* hd = head;

    while (hd != NULL) {
        if (filter(cond, hd->data) == 1){ 
            printf("-exec select: ");

            const char* del_serv = ",";
            char tmp[1024];
            strcpy(tmp, fields);
            char* service = strtok(tmp, del_serv);
            char flds[10][30];

            int i = 0;
            while (service) {
                strcpy(flds[i], service);
                service = strtok(NULL, del_serv);
                i++;
            }

            for (int j=0; j<i; j++) {
                if (strcmp(flds[j], "last_name") == 0) 
                    printf("%s=%s ", flds[j], hd->data.last_name);
                if (strcmp(flds[j], "first_name") == 0) 
                    printf("%s=%s ", flds[j], hd->data.first_name);
                if (strcmp(flds[j], "middle_name") == 0) 
                    printf("%s=%s ", flds[j], hd->data.middle_name);
                if (strcmp(flds[j], "number") == 0) 
                    printf("%s=%s ", flds[j], hd->data.number);   
                if (strcmp(flds[j], "bonus_id") == 0) 
                    printf("%s=%d ", flds[j], hd->data.bonus_id); 
                if (strcmp(flds[j], "discount_id") == 0) 
                    printf("%s=%d ", flds[j], hd->data.discount_id); 

                if (strcmp(flds[j], "services") == 0) {
                    printf("%s=[", flds[j]);
                    int first=1;
                    for (int k = 0; k < MAX_SERVICES; k++) {                
                        if (hd->data.services[k][0] != '\0') {
                            if (first == 1) {
                                printf("%s", hd->data.services[k]);
                                first = 0;
                            }
                            else
                                printf(",%s", hd->data.services[k]);
                        } else {
                            break;
                        }
                    }         
                    printf("] ");
                }           
            }

            printf("\n");
           
        }
        hd = hd->next;
    }
}