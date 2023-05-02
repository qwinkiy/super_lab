#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

#define FILTER_ARRAY_SIZE 100

int exec_uniq(struct node* head, const char* fields) {
    int first = 1;
    int cnt=0;
    while (head != NULL) {
        cnt = uniq(head, fields);
        head = head->next;
    }
    printf("uniq: %d rows\n", cnt);
    return cnt;
}


void sort_array(char arr[FILTER_ARRAY_SIZE][12])
{
    char temp[12];
    for(int i=0; i<FILTER_ARRAY_SIZE; i++){
        for(int j=0; j<FILTER_ARRAY_SIZE - 1 - i; j++){
            if(strcmp(arr[j], arr[j+1]) > 0){
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }  
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int uniq(struct node* head, const char* fields)
{
    const char* del_serv = ",";
    char tmp[1024];
    strcpy(tmp, fields);
    char* service = strtok(tmp, del_serv);
    char flds[10][30];

    char target[10][30]; 
    char* row_main_flds; 
    char* row_services_flds; 

    int i = 0;
    while (service) {
        strcpy(flds[i], service);
        service = strtok(NULL, del_serv);
        i++;
    }
    for (int j=0; j<i; j++) {  
        if (strcmp(flds[j], "last_name") == 0)
            row_main_flds = concat(head->data.last_name, head->data.last_name); 
        if (strcmp(flds[j], "first_name") == 0)
            row_main_flds = concat(head->data.last_name, head->data.first_name); 
        if (strcmp(flds[j], "middle_name") == 0)
            row_main_flds = concat(row_main_flds, head->data.middle_name);
        if (strcmp(flds[j], "number") == 0)
            row_main_flds = concat(row_main_flds, head->data.number);
        if (strcmp(flds[j], "bonus_id") == 0)
        {
            char* bonus_id;
            itoa(head->data.bonus_id, bonus_id, 10);            
            row_main_flds = concat(row_main_flds, bonus_id);
        }            
        if (strcmp(flds[j], "discount_id") == 0)
        {
            char* discount_id; 
            itoa(head->data.discount_id, discount_id, 10);
            row_main_flds = concat(row_main_flds, discount_id);
        }
        if (strcmp(flds[j], "services") == 0) 
        {
            char tmp_serv[MAX_SERVICES][SERVICE_NAME_LENGTH];
            for (int i=0; i<MAX_SERVICES; i++)
                for (int j=0; j<SERVICE_NAME_LENGTH; j++)
                    tmp_serv[i][j] = '\0';

            strcpy(tmp_serv, head->data.services);
            sort_array(tmp_serv);
            for (int k = 0; k < MAX_SERVICES; k++) 
            {                
                if (tmp_serv[k][0] != '\0') {
                    row_main_flds = concat(row_main_flds, tmp_serv[k]);
                } else {
                    break;
                }
            }
            
        }
    }

    return 0;
    /*struct node* nested_head = head->next;
        while (nested_head != NULL) {   
            if()
            {

            }     
            nested_head = head->next;
        }
*/
    
    
}