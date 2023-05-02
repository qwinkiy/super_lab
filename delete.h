#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

int exec_delete(struct node* head, const char* fltr) {
    int first = 1;
    int cnt=0;
    struct node* head_base = head;
    while (head != NULL) {
        if (filter(fltr, head->data) == 1){ 
            if (first == 1) {
                pop(&head);    
                head_base = head;
                cnt++;
                continue;
            }
            else {
                pop(&head);
                cnt++;
                first = 0;
                continue;
            }            
        }
        head = head->next;
    }
    printf("deleted: %d rows\n", cnt);
    return head_base;
}