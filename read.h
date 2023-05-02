#include <stdlib.h>
#include "mem_calc.h"
#include "parse_command.h"
#include "list.h"
#include "select.h"
#include "filter.h"
#include "delete.h"
#include "update.h"

void read_command(struct node* head) {
    char buffer[256];
    FILE * f = fopen("input.txt","r");
    if(f) {
        while((fgets(buffer, 256, f)) != NULL) {
            struct command a = parse_command(buffer);
                if (a.command != -1) {

                    // SELECT
                    if (a.command == 2) {
                        exec_select(head, a.cond, a.fields);
                    }
                
                    // DELETE
                    if (a.command == 3) {
                        printf("-exec delete: ");
                        head = exec_delete(head, a.cond);
                        
                    }

                    // UPDATE
                    // if (a.command == 4) {
                    //     printf("-exec delete: ");
                    //     int cnt = exec_update(head, a.cond, a.fields);
                    //     printf("deleted: %d rows\n", cnt);
                    // }

                }


                    // printf("command: %i  origin: %s",a.command, buffer);
                    // printf("fileds: %s\n",a.fields);
                    // printf("fil_len: %i\n",a.fil_len);
                    // printf("cond: %s\n",a.cond);
                    // printf("con_len: %i\n",a.con_len);
                    // printf("конец\n\n");
                    // вызов команд
        }
        
        fclose(f);
    }
};