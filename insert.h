#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"

struct row* row_to_insert(const char* fields){
    struct row* row = (struct row*)malloc(sizeof(struct row));
    const char* del_serv = ",";
    char tmp[512];
    strcpy(tmp, fields);
    char* service = strtok(tmp, del_serv);
    char single_fld[20][30];
    
    int i = 0;
    while (service) {
        strcpy(single_fld[i], service);
        service = strtok(NULL, del_serv);
        i++;
    }
    int k1 = 0;
    int k2 = 0;
    int k3 = 0;
    int k4 = 0;
    int k5 = 0;
    int k6 = 0;
    for (int j = 0; j < i; j++) {
        const char* del_serv = "=";
        char* field = strtok(single_fld[j], del_serv);
        char* value = strtok(NULL, del_serv);

        if (strcmp(field, "last_name") == 0) {
            strcpy(row->last_name, value);
            k1++;
        }
        else if (strcmp(field, "first_name") == 0) {
            strcpy(row->first_name, value);
            k2++;
        }
        else if (strcmp(field, "middle_name") == 0) {
            strcpy(row->middle_name, value);
            k3++;
        }
        else if (strcmp(field, "number") == 0) {
            strcpy(row->number, value);
            k4++;
        }
        else if (strcmp(field, "bonus_id") == 0) {
            row->bonus_id = atoi(value);
            k5++;
        }
        else if (strcmp(field, "discount_id") == 0) {
            row->discount_id = atoi(value);
            k6++;
        }
        else {
            printf("Insert error, unknown field\n");
            return NULL;
        }
    }
    for (int k=0; k < MAX_SERVICES; ++k) 
        strncpy(row->services[k], "\0", 1);    
    if ((k1==1) && (k2==1) && (k3==1) && (k4==1) && (k5==1) && (k6==1)){
        return row;}
    else return NULL;
}


void exec_insert(struct node* head, const char* fields) {
    struct row* r = row_to_insert(fields);
    if (r != NULL)
        insert_back(&head, *r);
        free(r);
}