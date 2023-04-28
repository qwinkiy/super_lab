#pragma once

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

struct command{
    int command; 
    char* fileds;
    int fil_len;
    char* cond;
    int con_len;
};
struct command parse_command(char* str1){
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
    //проверка на атрибуты
    switch (comm.command){
        case 1: if (comm.fileds == NULL){comm.command = -1;} break;
        case 2: if ((comm.fileds == NULL)&&(comm.cond == NULL)){comm.command = -1;} break;
        case 3: if (comm.cond == NULL){comm.command = -1;} break;
        case 4: if ((comm.fileds == NULL)&&(comm.cond == NULL)){comm.command = -1;} break;
        case 5: if (comm.fileds == NULL){comm.command = -1;} break;
    }
    return comm;
}