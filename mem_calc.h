#pragma once

#include <stdlib.h>
#include <stdio.h>

int c_malloc = 0;
int c_free = 0;
int c_calloc = 0;
int c_realloc = 0;

void* _malloc(size_t size) {
    c_malloc++;
    return malloc(size);
}

void _free(void* ptr) {
    c_free++;
    return free(ptr);
}

void* _calloc(size_t a, size_t b) {
    c_calloc++;
    return calloc(a, b);
}

void* _realloc(void* ptr, size_t size) {
    if (ptr == NULL)
        c_malloc++;
    else
        c_realloc++;
    return realloc(ptr, size);
}

#define malloc(size) \
    _malloc(size)

#define free(size) \
    _free(size)

#define calloc(a, b) \
    _calloc(a, b)

#define realloc(ptr, size) \
    _realloc(ptr, size)

void print_mem() {
    printf("malloc:%d\n", c_malloc);
    printf("realloc:%d\n", c_realloc);
    printf("calloc:%d\n", c_calloc);
    printf("free:%d\n", c_free);

    FILE* file = fopen("memstat.txt", "w");

    fprintf(file, "malloc:%d\n", c_malloc);
    fprintf(file, "realloc:%d\n", c_realloc);
    fprintf(file, "calloc:%d\n", c_calloc);
    fprintf(file, "free:%d\n", c_free);

    fclose(file);

    return;
}