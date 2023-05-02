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
    struct node* hd = head;

    while (hd != NULL) {
        if (filter(fltr, hd->data) == 1){ 
            res++;
            const char* del_serv = ",";
            char tmp[1024];
            strcpy(tmp, fld);
            char* service = strtok(tmp, del_serv);
            char single_fld[20][30];

            int num = 0;
            while (service) {
                strcpy(single_fld[num], service);                
                service = strtok(NULL, del_serv);
                num++;
            }

            for (int j = 0; j < num; j++) {
                const char* del_serv = "=";
                char* field = strtok(single_fld[j], del_serv);               
                char* value = strtok(NULL, del_serv);                

                if (strcmp(field, "last_name") == 0) 
                    strcpy(hd->data.last_name, value);
                if (strcmp(field, "first_name") == 0) 
                    strcpy(hd->data.first_name, value);
                if (strcmp(field, "middle_name") == 0) 
                    strcpy(hd->data.middle_name, value);
                if (strcmp(field, "number") == 0) 
                    strcpy(hd->data.number, value);
                if (strcmp(field, "bonus_id") == 0) 
                    hd->data.bonus_id = atoi(value);
                if (strcmp(field, "discount_id") == 0) 
                    hd->data.discount_id = atoi(value);
            }
        }
        i++;
        hd = hd->next;
    }
    return res;
}