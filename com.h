#include <stdio.h>

#include <stdlib.h>

#include <string.h>

struct command{
    int command; // 0 - select, 1 - insert
    char* fileds;
    int fil_len;// first_name, last_name, number
    char* cond;
    int con_len;// 
};

struct command create_command(char* str1){
    struct command comm = {-1, "", 0, "", 0};
    char * token = strtok(str1, " ");
    if (strcmp(token, "insert") == 0){
        comm.command = 1;
        comm.fileds = strtok(NULL, " ");
        comm.fil_len = sizeof(comm.fileds);
    }
    else if (strcmp(token, "select") == 0){
        comm.command = 2;
        comm.fileds = strtok(NULL, " ");
        comm.fil_len = sizeof(comm.fileds);
        comm.cond = strtok(NULL, "");
        comm.con_len = sizeof(comm.cond);
    }
    else if (strcmp(token, "delete") == 0){
        comm.command = 3;
        comm.cond = strtok(NULL, "");
        comm.con_len = sizeof(comm.cond);
    }
    else if (strcmp(token, "update") == 0){
        comm.command = 4;
        comm.fileds = strtok(NULL, " ");
        comm.fil_len = sizeof(comm.fileds);
        comm.cond = strtok(NULL, "");
        comm.con_len = sizeof(comm.cond);
    }
    else if (strcmp(token, "uniq") == 0){
        comm.command = 5;
        comm.fileds = strtok(NULL, "");
        comm.fil_len = sizeof(comm.fileds);
    }
    //if (comm.command>=1) && (comm.command<=5){return comm;}
    //else return comm;// тип вернуть что комнда говно, но по сути она не заполнится и будет пустой
    return comm;
}
