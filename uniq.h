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
    int i = 0;
    struct node* head_base = head;
    while (head != NULL) {
        if (uniq(head, fields, i) == 1) {
            delete_node(&head_base, i);
            head = head_base;
            cnt++;
            i--;        
        }
        head = head->next;
        i++;
    }
    printf("uniq: %d rows\n", cnt);
    return cnt;
}

int uniq(struct node* head, const char* fields, int n)
{
    const char* del_serv = ",";
    char tmp[1024];
    strcpy(tmp, fields);
    char* service = strtok(tmp, del_serv);
    char flds[10][30];

    char filter_cond[1024]; 
    for (int i=0; i<1024; i++)
        filter_cond[i] = '\0';    

    int i = 0;
    while (service) {
        strcpy(flds[i], service);
        service = strtok(NULL, del_serv);
        i++;
    }
    for (int j=0; j<i; j++) {  
        if (strcmp(flds[j], "last_name") == 0)
        {
            strcat(filter_cond, "last_name==");
            strcat(filter_cond, head->data.last_name);
            strcat(filter_cond, " ");
        }             
        if (strcmp(flds[j], "first_name") == 0)
        {
            strcat(filter_cond, "first_name==");
            strcat(filter_cond, head->data.first_name);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "middle_name") == 0)
        {
            strcat(filter_cond, "middle_name==");
            strcat(filter_cond, head->data.middle_name);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "number") == 0)
        {
            strcat(filter_cond, "number==");
            strcat(filter_cond, head->data.number);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "bonus_id") == 0)
        {
            char* bonus_id;
            itoa(head->data.bonus_id, bonus_id, 10);           
            strcat(filter_cond, "bonus_id==");
            strcat(filter_cond, head->data.bonus_id); 
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "discount_id") == 0)
        {
            char* discount_id; 
            itoa(head->data.discount_id, discount_id, 10);
            strcat(filter_cond, "discount_id==");
            strcat(filter_cond, head->data.discount_id);
            strcat(filter_cond, " ");
        }
        if (strcmp(flds[j], "services") == 0) 
        {
            for (int k = 0; k < MAX_SERVICES; k++) 
            {                
                if (head->data.services[k][0] != '\0') {
                    strcat(filter_cond, "services==");
                    strcat(filter_cond, head->data.services[k]);
                    strcat(filter_cond, " ");
                } else {
                    break;
                }
            }            
        }
    }    
    
    struct node* nested_head = head->next;
    while (nested_head != NULL) {   
        if(filter(&filter_cond, nested_head->data))
        {
            return 1;
        }     
        nested_head = nested_head->next;
    }

    return 0;  
}