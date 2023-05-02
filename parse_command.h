#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct command{
    int command; 
    char fields[100];
    int fil_len;
    char cond[100];
    int con_len;
};

// Функция: замена подстроки в строке на заданную последовательность символов - C (СИ)
char* find_and_insert(char* str,char* sub_str, char* sub_str_rep){
  const int BUFFER_SIZE = 1024;
  char* buffer = NULL;
  int buffer_len = 0;
  // если входных данных нет - ничего не делаем.
  if (str && sub_str && sub_str_rep){
    
    // предпологаем что под строку str отведенно достаточно памяти.
    // в противном случае ничего не делаем    
    
    // если длина строки str достаточна для хранения новой строки, продолжаем
    if( strlen(str) < strlen(str) - strlen(sub_str) + strlen(sub_str_rep) ){
      // временный массив
      buffer = (char*)malloc(BUFFER_SIZE);
      // чистим массив от мусора
      memset(buffer, 0, strlen(str));
     
      // Делаем дело. strlen strstr strcat strcpy и strncpy 
      // стандартные ф-ии в string.h
      strncpy(buffer, str, strlen(str) - strlen(strstr(str,sub_str)) );
      strcat(buffer, sub_str_rep);  
      strcat(buffer, strstr(str,sub_str) + strlen(sub_str));
      
      
      //strcat(buffer, str + strlen(str) - strlen(strstr(str,sub_str)) + 1);      
      //strcat(buffer, strstr(str,su))
      strcpy(str, buffer);   
      
      // освобождаем память отведённую под массив
      free(buffer);
    }
  }
  return str;
}

struct command parse_command(const char* str1) {
    struct command comm = {-1, "\0", 0, "\0", 0};
    char str_t[1024];
    strcpy(str_t, str1);
    char * token = strtok(str_t, " ");
    if (strcmp(token, "insert") == 0){
        comm.command = 1;
        strcpy(comm.fields, strtok(NULL, " "));
        if (comm.fields)
            comm.fil_len = strlen(comm.fields);
        else comm.fil_len = 0;
    }
    else if (strcmp(token, "select") == 0){
        comm.command = 2;
        strcpy(comm.fields, strtok(NULL, " "));
        if (comm.fields)
            comm.fil_len = strlen(comm.fields);
        else comm.fil_len = 0;        
        strcpy(comm.cond, strtok(NULL, ""));
        if (comm.cond)
            comm.con_len = strlen(comm.cond);
        else comm.con_len = 0;
    }
    else if (strcmp(token, "delete") == 0){
        comm.command = 3;
        strcpy(comm.cond, strtok(NULL, ""));
        if (comm.cond)
            comm.con_len = strlen(comm.cond);
        else comm.con_len = 0;
    }
    else if (strcmp(token, "update") == 0){
        comm.command = 4;
        strcpy(comm.fields, strtok(NULL, " "));
        if (comm.fields)
            comm.fil_len = strlen(comm.fields);
        else comm.fil_len = 0;

        strcpy(comm.cond, strtok(NULL, ""));
        if (comm.cond)
            comm.con_len = strlen(comm.cond);
        else comm.con_len = 0;
    }
    else if (strcmp(token, "uniq") == 0){
        comm.command = 5;
        strcpy(comm.fields, strtok(NULL, " "));
        if (comm.fields)
            comm.fil_len = strlen(comm.fields);
        else comm.fil_len = 0;
    }
    //проверка на атрибуты
    switch (comm.command){
        case 1: if (comm.fields == NULL) {
                    comm.command = -1;
                } 
                break;
                
        case 2: if ((comm.fields == NULL)||(comm.cond == NULL)){
                    comm.command = -1;
                } 
                break;
        case 3: if (comm.cond == NULL){
                    comm.command = -1;
                } 
                break;
        case 4: if ((comm.fields == NULL)||(comm.cond == NULL)) {
                    comm.command = -1;
                } 
                break;
        case 5: if (comm.fields == NULL) {
                    comm.command = -1;
                } 
                break;
    }
    if (comm.command == 1 || comm.command == 2 || comm.command == 4 || comm.command == 5) {
        int len = strlen(comm.fields);
        if(len > 0)
            if(comm.fields[len-1] == '\n')
                comm.fields[len-1] = 0;
    }
    if (comm.command == 2 || comm.command == 3 || comm.command == 4) {
        int len = strlen(comm.cond);
        if(len > 0)
            if(comm.cond[len-1] == '\n')
                comm.cond[len-1] = 0;
    }
    return comm;
}