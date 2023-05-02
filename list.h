#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_calc.h"

#define MAX_SERVICES 14
#define SERVICE_NAME_LENGTH 8

struct row {
    char last_name[20];
    char first_name[20];
    char middle_name[20];
    char number[15];
    char services[MAX_SERVICES][SERVICE_NAME_LENGTH];
    int discount_id; 					// Код скидочной программы
    int bonus_id; 					// Код бонусной программы

};

struct node {
    struct row data;
    struct node* next;
};

void insert_front(struct node** head, struct row data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void insert_back(struct node** head, struct row data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}


struct node* get_node(struct node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

int get_list_size(struct node* head) {
    int counter = 0;
    while (head) {
        head = head->next;
        counter++;
    }
    return counter;
}

void print_node(struct node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    printf("%s %s %s, номер %s, дисконт: %d, бонус: %d, услуги:", head->data.last_name, head->data.first_name, 
            head->data.middle_name, head->data.number, head->data.discount_id, head->data.bonus_id);
        for (int j = 0; j < MAX_SERVICES; j++) {
            if (head->data.services[j][0] != '\0') {
                printf(" %s", head->data.services[j]);
            } else {
                break;
            }
        }
        printf("\n");
}

struct row pop(struct node **head) {
    struct node* prev = NULL;
    struct row val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->data;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

struct row delete_node(struct node** head, int n) {
    if (n == 0) {
        struct node* prev = get_node(*head, 0);
        (*head) = (*head)->next;
        free(prev);
    } else {
        struct node *prev = get_node(*head, n-1);
        struct node *elm  = prev->next;
        struct row val = elm->data;
 
        prev->next = elm->next;
        free(elm);
        return val;
    }
}

void print_list(struct node* head) {
    while (head != NULL) {
        printf("last: %s first: %s mid: %s, номер %s, дисконт: %d, бонус: %d, услуги:", head->data.last_name, head->data.first_name, 
            head->data.middle_name, head->data.number, head->data.discount_id, head->data.bonus_id);
        for (int j = 0; j < MAX_SERVICES; j++) {
            if (head->data.services[j][0] != '\0') {
                printf(" %s", head->data.services[j]);
            } else {
                break;
            }
        }
        printf("\n");
        head = head->next;
    }
}

void free_list(struct node* head) {
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
}
