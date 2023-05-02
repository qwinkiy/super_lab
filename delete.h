#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

struct node* exec_delete(struct node* head, const char* fltr) {
    int first = 1;
    int cnt=0;
    int i = 0;
    struct node* head_base = head;
    while (head != NULL) {
        if (filter(fltr, head->data) == 1) {
            delete_node(&head_base, i);
            head = head_base;
            cnt++;            
            continue;
        }
        head = head->next;
        i++;
    }
    printf("deleted: %d rows\n", cnt);
    return head_base;
}