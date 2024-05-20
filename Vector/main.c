#include "Vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void printInt(void *vp) { printf("%d", *(int *)vp); }
void deallocString(void *vp) { free(*(char **)vp); }
bool compareString(void *vp1, void *vp2) {
    return strcmp(*(char **)vp1, *(char **)vp2) == 0;
}
void printString(void *vp) { printf("'%s'", *(char **)vp); }
const char **createStringContainer(const char *s) {
    const char **container = (const char **)malloc(sizeof(char **));
    assert(container != NULL);
    *container = strdup(s);

    return container;
}

int main(int argc, char **argv) {
    // struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL,
    // printInt);
    struct Vector *strings = Vector_create(sizeof(char *), deallocString,
                                           compareString, printString);
    Vector_print(strings);

    for (int i = 0; i < argc; i++)
        Vector_push(strings, createStringContainer(argv[i]));

    Vector_print(strings);

    for (int i = 0; i < argc / 2; i++) {
        Vector_delete(strings, 0);
        Vector_print(strings);
    }

    Vector_print(strings);
    return 0;
}
