#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mem_calc.h"
#include "list.h"

char* get_field(const char* cond)
{
    for(int i = 0; i < strlen(cond); i++)
    {      
        char t = cond[i];
        if(isalpha(t) == 0 && t != '_')
        {
            char* res = malloc(i); 
            memcpy(res, cond, i);
            res[i] = '\0';
            return res;
        }
    }    
}

char* get_value(const char* cond, int trunc_length)
{
    char* value = malloc(strlen(cond) - trunc_length + 1);
    memcpy(value, cond + trunc_length, strlen(value));

    return value;
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
        unsigned long converted_val; 
        sscanf(r.number, "%d", &converted_val);
        return ulong_comparison("==", converted_val, value);
    }
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
        unsigned long converted_val; 
        sscanf(r.number, "%d", &converted_val);
        return ulong_comparison("!=", converted_val, value);
    }
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
        unsigned long converted_val; 
        sscanf(r.number, "%d", &converted_val);
        return ulong_comparison(">", converted_val, value);
    }
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
        unsigned long converted_val; 
        sscanf(r.number, "%d", &converted_val);
        return ulong_comparison("<", converted_val, value);
    }
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
        return equal(cond, r);
    }
    else if(strstr(cond, "!="))
    {
        return not_equal(cond, r);
    }
    else if(strstr(cond, "/in/"))
    {
        //return in(cond, r);
    }    
    else if(strstr(cond, "/include/"))
    {
        //return include(cond, r);
    }
    else
    {
        return 0;
    }
}

int filter(const char* cond, struct row r) 
{
    int result; 
    int str_len = strlen(cond);
    if (str_len == 0)
    {
        return 1;
    }
    else
    {          
        char* single_cond = strtok(cond, " ");
        while (single_cond) {            
            result = do_work(single_cond, r);
            if(result == 0)
            {
                return 0;        
            }
            
            single_cond = strtok(NULL, " ");
        }
    }

    return 1;
}