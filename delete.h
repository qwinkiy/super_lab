#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"
#include "list.h"
#include "filter.h"

int exec_delete(struct node* head, const char* fltr) {
    int i = 0;
    int res = 0;
    while (head != NULL) {
        if (filter(fltr, head->data) == 1){ 
            delete_node(&head, i);
            res++;
        }
        i++;
        head = head->next;
    }
    return res;
}