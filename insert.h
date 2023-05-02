#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"

struct row exec_insert(struct command comm){
    struct row row;
    const char* del_serv = ",";
    char tmp[1024];
    strcpy(tmp, comm.fields);
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
    
        if (strcmp(field, "last_name") == 0) 
            strcpy(row.last_name, value);
        if (strcmp(field, "first_name") == 0) 
            strcpy(row.first_name, value);
        if (strcmp(field, "middle_name") == 0) 
            strcpy(row.middle_name, value);
        if (strcmp(field, "number") == 0) 
            strcpy(row.number, value);
        if (strcmp(field, "bonus_id") == 0) 
            row.bonus_id = atoi(value);
        if (strcmp(field, "discount_id") == 0) 
            row.discount_id = atoi(value);
    }
    return (row);
}