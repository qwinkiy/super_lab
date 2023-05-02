#pragma once 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "mem_calc.h"
#include "list.h"

#define FILTER_ARRAY_SIZE 100

char* glob_field;
char* glob_value;

char* get_field(const char* cond)
{
    for(int i = 0; i < strlen(cond); i++)
    {      
        char t = cond[i];
        if(isalpha(t) == 0 && t != '_')
        {
            char* res = (char*)malloc(i); 
            memcpy(res, cond, i);
            res[i] = '\0';
            glob_field = res;
            return res;
        }
    }    
}

char* get_value(const char* cond, int trunc_length)
{
    char* value = (char*)malloc(strlen(cond) - trunc_length + 1);
    memcpy(value, cond + trunc_length, strlen(value));
    glob_value = value;

    return value;
}

void get_value_array(const char* cond, int trunc_length, char res_arr[FILTER_ARRAY_SIZE][12])
{
    for (int i=0; i<FILTER_ARRAY_SIZE; i++)
        for (int j=0; j<12; j++)
            res_arr[i][j] = '\0';
    int start = 0;
    int j = 0;
    for(int i = trunc_length; i < strlen(cond); i++)
    {      
        char t = cond[i];
        if(t == '\'' && start == 0)
        {
            start = i;
        }
        else if(t == '\'' && start != 0)
        {
            strncpy(res_arr[j], &(cond[start+1]), i - start - 1); 
            start = 0;
            j++; 
        }
    }     
}

int str_comparison(const char* comparison_operand, const char* val1, const char* val2)
{
    if (strcmp(comparison_operand, ">") == 0)
    {
        if(strcmp(val1, val2) > 0)
        {
            return 1;
        }
        return 0;
    }

    if (strcmp(comparison_operand, "<") == 0)
    {
        if(strcmp(val1, val2) < 0)
        {
            return 1;
        }
        return 0;
    }

    if (strcmp(comparison_operand, "==") == 0)
    {
        if(strcmp(val1, val2) == 0)
        {
            return 1;
        }
        return 0;
    }

    if (strcmp(comparison_operand, "!=") == 0)
    {
        if(strcmp(val1, val2) != 0)
        {
            return 1;
        }
        return 0; 
    }

    return 0;
}

int ulong_comparison(const char* comparison_operand, unsigned long val1, unsigned long val2)
{
    if (strcmp(comparison_operand, ">") == 0)
    {
        return val1 > val2;
    }

    if (strcmp(comparison_operand, "<") == 0)
    {
        return val1 < val2;
    }

    if (strcmp(comparison_operand, "==") == 0)
    {
        return val1 == val2;
    }

    if (strcmp(comparison_operand, "!=") == 0)
    {
        return val1 != val2; 
    }

    return 0;
}

int except(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char arr[FILTER_ARRAY_SIZE][12];
    get_value_array(cond, strlen(field) + 3, arr);
    int hit = 0;
    int count = 0;

    for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
    {
        if(strcmp(arr[i], "\0") != 0)
        {
            count += 1;
        }
        else
        {
            break;
        }
    }
    
    if(strcmp(field, "services") == 0)
    {
        for(int j = 0; j < MAX_SERVICES; j++)
        {
            for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
            {
                if(strcmp(arr[i], r.services[j]) == 0 && strcmp(arr[i], "\0") != 0)
                {
                    hit += 1;
                    break;
                }

                if(strcmp(arr[i], "\0") == 0)
                {
                    break;
                }
            }
        }

        return count != hit; 
    }

    return 0;
}

int only_include(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char arr[FILTER_ARRAY_SIZE][12];
    get_value_array(cond, strlen(field) + 3, arr);
    int hit = 0;
    int count = 0;

    for(int i = 0; i < MAX_SERVICES; i++)
    {
        if(strcmp(r.services[i], "\0") != 0)
        {
            count += 1;
        }
        else
        {
            break;
        }
    }
    
    if(strcmp(field, "services") == 0)
    {
        for(int j = 0; j < MAX_SERVICES; j++)
        {
            for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
            {
                if(strcmp(arr[i], r.services[j]) == 0 && strcmp(arr[i], "\0") != 0)
                {
                    hit += 1;
                    break;
                }

                if(strcmp(arr[i], "\0") == 0)
                {
                    break;
                }
            }
        }

        return count == hit; 
    }

    return 0;
}

int equal(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char* value = get_value(cond, strlen(field) + 2);

    if(strcmp(field, "first_name") == 0)
    {
        return str_comparison("==", r.first_name, value);      
    }
    if(strcmp(field, "last_name") == 0)
    {
        return str_comparison("==", r.last_name, value);
    }
    if(strcmp(field, "middle_name") == 0)
    {
        return str_comparison("==", r.middle_name, value);
    }

    if(strcmp(field, "number") == 0)
    {
        unsigned long converted_val1; 
        unsigned long converted_val2; 
        sscanf(r.number, "%d", &converted_val1);
        sscanf(value, "%d", &converted_val2);
        return ulong_comparison("==", converted_val1, converted_val2);
    }

    if(strcmp(field, "discount_id") == 0)
    {
        return r.discount_id == atoi(value);
    }
    if(strcmp(field, "bonus_id") == 0)
    {
        return r.bonus_id == atoi(value);
    }

    return 0;
}

int not_equal(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char* value = get_value(cond, strlen(field) + 2);
    if(strcmp(field, "first_name") == 0)
    {
        return str_comparison("!=", r.first_name, value);
    }
    if(strcmp(field, "last_name") == 0)
    {
        return str_comparison("!=", r.last_name, value);
    }
    if(strcmp(field, "middle_name") == 0)
    {
        return str_comparison("!=", r.middle_name, value);
    }

    if(strcmp(field, "number") == 0)
    {
        unsigned long converted_val1; 
        unsigned long converted_val2; 
        sscanf(r.number, "%d", &converted_val1);
        sscanf(r.number, "%d", &converted_val2);
        return ulong_comparison("!=", converted_val1, converted_val2);
    }

    if(strcmp(field, "discount_id") == 0)
    {
        return r.discount_id != atoi(value);
    }
    if(strcmp(field, "bonus_id") == 0)
    {
        return r.bonus_id != atoi(value);
    }	

    return 0;
}

int more(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char* value = get_value(cond, strlen(field) + 1);
    if(strcmp(field, "first_name") == 0)
    {
        return str_comparison(">", r.first_name, value);
    }
    if(strcmp(field, "last_name") == 0)
    {
        return str_comparison(">", r.last_name, value);
    }
    if(strcmp(field, "middle_name") == 0)
    {
        return str_comparison(">", r.middle_name, value);
    }

    if(strcmp(field, "number") == 0)
    {
        unsigned long converted_val1; 
        unsigned long converted_val2; 
        sscanf(r.number, "%d", &converted_val1);
        sscanf(r.number, "%d", &converted_val2);
        return ulong_comparison(">", converted_val1, converted_val2);
    }

    if(strcmp(field, "discount_id") == 0)
    {
        return r.discount_id > atoi(value);
    }
    if(strcmp(field, "bonus_id") == 0)
    {
        return r.bonus_id > atoi(value);
    }

    return 0;
}

int less(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char* value = get_value(cond, strlen(field) + 1);
    if(strcmp(field, "first_name") == 0)
    {
        return str_comparison("<", r.first_name, value);         
    }    
    if(strcmp(field, "last_name") == 0)
    {
        return str_comparison("<", r.last_name, value);
    }
    if(strcmp(field, "middle_name") == 0)
    {
        return str_comparison("<", r.middle_name, value);
    }

    if(strcmp(field, "number") == 0)
    {
        unsigned long converted_val1; 
        unsigned long converted_val2; 
        sscanf(r.number, "%d", &converted_val1);
        sscanf(r.number, "%d", &converted_val2);
        return ulong_comparison("<", converted_val1, converted_val2);
    }

    if(strcmp(field, "discount_id") == 0)
    {
        return r.discount_id < atoi(value);
    }
    if(strcmp(field, "bonus_id") == 0)
    {
        return r.bonus_id < atoi(value);
    }

    return 0;
}

int include(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char arr[FILTER_ARRAY_SIZE][12];
    get_value_array(cond, strlen(field) + 3, arr);
    int hit = 0;
    int count = 0;

    for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
    {
        if(strcmp(arr[i], "\0") != 0)
        {
            count += 1;
        }
        else
        {
            break;
        }
    }
    
    if(strcmp(field, "services") == 0)
    {
        for(int j = 0; j < MAX_SERVICES; j++)
        {
            for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
            {
                if(strcmp(arr[i], r.services[j]) == 0  && strcmp(arr[i], "\0") != 0)
                {
                    hit += 1;
                    break;
                }

                if(strcmp(arr[i], "\0") == 0)
                {
                    break;
                }
            }
        }

        return count == hit; 
    }

    return 0;
}

int in(const char* cond, struct row r)
{
    char* field = get_field(cond);
    char arr[FILTER_ARRAY_SIZE][12];
    get_value_array(cond, strlen(field) + 3, arr);
    if(strcmp(field, "first_name") == 0)
    {
        for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
        {
            if(strcmp(arr[i], r.first_name) == 0  && strcmp(arr[i], "\0") != 0)
            {
                return 1;
            }

            if(strcmp(arr[i], "\0") == 0)
            {
                break;
            }
        }
        return 0;     
    }    
    if(strcmp(field, "last_name") == 0)
    {
        for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
        {
            if(strcmp(arr[i], r.last_name) == 0  && strcmp(arr[i], "\0") != 0)
            {
                return 1;
            }

            if(strcmp(arr[i], "\0") == 0)
            {
                break;
            }
        }
        return 0; 
    }
    if(strcmp(field, "middle_name") == 0)
    {
        for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
        {
            if(strcmp(arr[i], r.middle_name) == 0  && strcmp(arr[i], "\0") != 0)
            {
                return 1;
            }

            if(strcmp(arr[i], "\0") == 0)
            {
                break;
            }
        }
        return 0; 
    }

    if(strcmp(field, "services") == 0)
    {
        for(int j = 0; j < MAX_SERVICES; j++)
        {
            for(int i = 0; i < FILTER_ARRAY_SIZE; i++)
            {
                if(strcmp(arr[i], r.services[j]) == 0  && strcmp(arr[i], "\0") != 0)
                {
                    return 1;
                }

                if(strcmp(arr[i], "\0") == 0)
                {
                    break;
                }
            }
        }
        
        return 0; 
    }

    return 0;
}

int do_work(const char* cond, struct row r)
{
    if(strstr(cond, ">"))
    {
        return more(cond, r);
    }
    else if(strstr(cond, "<"))
    {
        return less(cond, r);
    }    
    else if(strstr(cond, "=="))
    {
        if(strstr(cond, "["))
        {
            return only_include(cond, r);
        }
        else
        {
            return equal(cond, r);
        }        
    }
    else if(strstr(cond, "!="))
    {
        if(strstr(cond, "["))
        {
            return except(cond, r);
        }
        else
        {
            return not_equal(cond, r);
        }
    }
    else if(strstr(cond, "/in/"))
    {
        return in(cond, r);
    }    
    else if(strstr(cond, "/include/"))
    {
        return include(cond, r);
    }
    else
    {
        return 0;
    }
}

int filter(const char* cond, struct row r) 
{
    int result; 
    int len_cond = strlen(cond);
    if (len_cond == 0)
    {
        return 1;
    }
    else
    {          
        const char* del_serv = " ";
        char tmp[1024];
        strcpy(tmp, cond);
        char* service = strtok(tmp, del_serv);
        char single_cond[20][30];

        int i = 0;
        while (service) {
            strcpy(single_cond[i], service);
            service = strtok(NULL, del_serv);
            i++;
        }

        for (int j=0; j<i; j++) 
        {
            result = do_work(single_cond[j], r);
            if(result == 0)
            {
                if (glob_field)
                    free(glob_field);
                if (glob_value)
                    free(glob_value);
                return 0;        
            }            

            if (glob_field)
                free(glob_field);
            if (glob_value)
                free(glob_value);
        }        
    }    
    
    return 1;
}