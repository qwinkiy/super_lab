#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

int exec_update(struct node* head, const char* fltr, const char* fld) {
    int i = 0;
    int res = 0;
    while (head != NULL) {
        // if (filter(fltr, head->data) == 1){ 
            
            const char* del_serv = ",";
            char tmp[1024];
            strcpy(tmp, fld);
            char* service = strtok(tmp, del_serv);
            char single_fld[20][30];

            int i = 0;
            while (service) {
                strcpy(single_fld[i], service);                
                service = strtok(NULL, del_serv);
                i++;
            }

            for (int j = 0; j < i; j++) {
                const char* del_serv = "=";
                char* field = strtok(single_fld[j], del_serv);               
                char* value = strtok(NULL, del_serv);
                printf("=== field = %s, value = %s\n", field,value);

                // TODO
            }

            delete_node(&head, i);
            res++;
        // }
        i++;
        head = head->next;
    }
    return res;
}