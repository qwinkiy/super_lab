#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

#define FILTER_ARRAY_SIZE 100

int uniq(struct node* head, const char* fields, int n)
{
    if(strlen(fields) == 0) return 0;

    struct node* hd = head;
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
            strcat(filter_cond, hd->data.last_name);
            strcat(filter_cond, " ");
        }             
        if (strcmp(flds[j], "first_name") == 0)
        {
            strcat(filter_cond, "first_name==");
            strcat(filter_cond, hd->data.first_name);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "middle_name") == 0)
        {
            strcat(filter_cond, "middle_name==");
            strcat(filter_cond, hd->data.middle_name);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "number") == 0)
        {
            strcat(filter_cond, "number==");
            strcat(filter_cond, hd->data.number);
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "bonus_id") == 0)
        {
            char bonus_id[12];
            itoa(hd->data.bonus_id, bonus_id, 10);           
            strcat(filter_cond, "bonus_id==");
            strcat(filter_cond, bonus_id); 
            strcat(filter_cond, " ");
        }            
        if (strcmp(flds[j], "discount_id") == 0)
        {
            char discount_id[12]; 
            itoa(hd->data.discount_id, discount_id, 10);
            strcat(filter_cond, "discount_id==");
            strcat(filter_cond, discount_id);
            strcat(filter_cond, " ");
        }
        if (strcmp(flds[j], "services") == 0) 
        {
            strcat(filter_cond, "services==[");
            for (int k = 0; k <= MAX_SERVICES; k++) 
            {                
                if (hd->data.services[k][0] != '\0') {          
                    strcat(filter_cond, "'");          
                    strcat(filter_cond, hd->data.services[k]);
                    strcat(filter_cond, "'");
                } 
                else 
                {       
                    strcat(filter_cond, "]");             
                    break;
                }      

                if(k != MAX_SERVICES && hd->data.services[k + 1][0] != '\0')
                {
                    strcat(filter_cond, ",");
                }  
            }
        }
    }    
    
    struct node* nested_head = hd->next;
    while (nested_head != NULL) {   
        if(filter(filter_cond, nested_head->data))
        {
            return 1;
        }     
        nested_head = nested_head->next;
    }

    return 0;  
}

int exec_uniq(struct node* head, const char* fields) {
    int first = 1;
    int cnt=0;
    int i = 0;
    struct node* hd = head;
    struct node* head_base = hd;
    while (hd != NULL) {
        if (uniq(hd, fields, i) == 1) {
            delete_node(&head_base, i);
            head = head_base;
            hd = head;
            cnt++;
            i--;        
        }
        hd = hd->next;
        i++;
    }
    printf("uniq: %d rows\n", cnt);
    return cnt;
}

