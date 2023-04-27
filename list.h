#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERVICES 14
#define SERVICE_NAME_LENGTH 8

struct row {
    char last_name[20];
    char first_name[20];
    char middle_name[20];
    char number[15];
    char services[MAX_SERVICES][SERVICE_NAME_LENGTH];
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

void print_node(struct node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    printf("%s %s %s, номер %s, услуги:", head->data.last_name, head->data.first_name, head->data.middle_name, head->data.number);
        for (int j = 0; j < MAX_SERVICES; j++) {
            if (head->data.services[j][0] != '\0') {
                printf(" %s", head->data.services[j]);
            } else {
                break;
            }
        }
        printf("\n");
}

void print_node_select(struct node* head, int n, const char* fields) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }

    const char* del_serv = ",";
    char tmp[1024];
    strcpy(tmp, fields);
    char* service = strtok(tmp, del_serv);
    int i = 0;
    char flds[10][30];

    while (service) {
        strcpy(flds[i], service);
        service = strtok(NULL, del_serv);
        i++;
    }

    for (int j=0; j<i; j++) {
        if (strcmp(flds[j], "last_name") == 0) 
            printf("%s=%s ", flds[j], head->data.last_name);
        if (strcmp(flds[j], "first_name") == 0) 
            printf("%s=%s ", flds[j], head->data.first_name);
        if (strcmp(flds[j], "middle_name") == 0) 
            printf("%s=%s ", flds[j], head->data.middle_name);
        if (strcmp(flds[j], "number") == 0) 
            printf("%s=%s ", flds[j], head->data.number);   
        if (strcmp(flds[j], "services") == 0) {
            printf("%s=[", flds[j]);
            int first=1;
            for (int k = 0; k < MAX_SERVICES; k++) {                
                if (head->data.services[k][0] != '\0') {
                    if (first == 1) {
                        printf("%s", head->data.services[k]);
                        first = 0;
                    }
                    else
                        printf(",%s", head->data.services[k]);
                } else {
                    break;
                }
            }         
            printf("] ");
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
        return pop(head);
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
        printf("%s %s %s, номер %s, услуги:", head->data.last_name, head->data.first_name, head->data.middle_name, head->data.number);
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
