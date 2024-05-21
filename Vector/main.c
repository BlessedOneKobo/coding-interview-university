#include "Vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>

// helpers
void print_int(void *vp);
void dealloc_string(void *vp);
bool compare_string(void *vp1, void *vp2);
void print_string(void *vp);
const char **create_string_container(const char *s);

// tests
void can_get_size(void);
void can_get_capacity(void);
void can_check_empty_state(void);
void can_get_value_at_index(void);
void can_push_values(void);
void can_pop_values(void);
void can_delete_values(void);
void can_remove_values(void);
void can_find_values(void);
void can_resize(void);

int main(void) {
    can_get_size();
    can_get_capacity();
    can_check_empty_state();
    can_get_value_at_index();
    can_push_values();
    can_pop_values();
    can_delete_values();
    can_remove_values();
    can_find_values();
    can_resize();
    return 0;
}

void can_resize(void) {
    printf("can resize");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    assert(Vector_capacity(numbers) == INITIAL_CAPACITY);

    __Vector_resize(numbers, 100);
    assert(Vector_capacity(numbers) == 100);

    printf("...OK\n");
}

void can_find_values(void) {
    printf("can find values");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    struct Vector *strings =
        Vector_create(sizeof(char **), dealloc_string, compare_string, NULL);

    for (size_t i = 0; i < 20; i++)
        Vector_push(numbers, &i);

    Vector_push(strings, create_string_container("Jon"));
    Vector_push(strings, create_string_container("Aemon"));
    Vector_push(strings, create_string_container("Frank"));

    int value = 19;
    assert(Vector_find(numbers, &value) == 19);
    value = 33;
    assert(Vector_find(numbers, &value) == -1);

    assert(Vector_find(strings, create_string_container("Aemon")) == 1);
    assert(Vector_find(strings, create_string_container("Dave")) == -1);
    printf("...OK\n");
}

void can_remove_values(void) {
    printf("can remove values");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    struct Vector *strings = Vector_create(sizeof(char **), dealloc_string,
                                           compare_string, print_string);

    Vector_push(strings, create_string_container("Jon"));
    Vector_push(strings, create_string_container("Aemon"));
    Vector_push(strings, create_string_container("Frank"));
    Vector_push(strings, create_string_container("Aemon"));
    int value = 99;
    for (size_t i = 0; i < 20; i++)
        if (i % 3 == 0)
            Vector_push(numbers, &value);
        else
            Vector_push(numbers, &i);

    Vector_remove(strings, create_string_container("Aemon"));
    assert(Vector_size(strings) == 2);
    assert(strcmp(*(char **)Vector_at(strings, 0), "Jon") == 0);
    assert(strcmp(*(char **)Vector_at(strings, 1), "Frank") == 0);

    Vector_remove(numbers, &value);
    assert(Vector_size(numbers) == 13);

    printf("...OK\n");
}

void can_delete_values(void) {
    printf("can delete values");

    struct Vector *strings =
        Vector_create(sizeof(char **), dealloc_string, compare_string, NULL);

    Vector_push(strings, create_string_container("Jon"));
    Vector_push(strings, create_string_container("Aemon"));
    Vector_push(strings, create_string_container("Frank"));

    Vector_delete(strings, 0);
    assert(Vector_size(strings) == 2);
    assert(strcmp(*(char **)Vector_at(strings, 0), "Aemon") == 0);
    assert(strcmp(*(char **)Vector_at(strings, 1), "Frank") == 0);

    printf("...OK\n");
}

void can_pop_values(void) {
    printf("can pop values");

    struct Vector *strings =
        Vector_create(sizeof(char **), dealloc_string, compare_string, NULL);

    Vector_push(strings, create_string_container("Jon"));
    Vector_push(strings, create_string_container("Aemon"));
    Vector_push(strings, create_string_container("Frank"));

    char **value = Vector_pop(strings);
    assert(Vector_size(strings) == 2);
    assert(strcmp(*(char **)Vector_at(strings, 1), "Aemon") == 0);
    assert(strcmp(*value, "Frank") == 0);

    printf("...OK\n");
}

void can_push_values(void) {
    printf("can push values");

    struct Vector *strings =
        Vector_create(sizeof(char **), dealloc_string, compare_string, NULL);

    Vector_push(strings, create_string_container("Jon"));
    assert(Vector_size(strings) == 1);
    assert(strcmp(*(char **)Vector_at(strings, 0), "Jon") == 0);

    Vector_push(strings, create_string_container("Aemon"));
    Vector_push(strings, create_string_container("Frank"));

    assert(Vector_size(strings) == 3);
    assert(strcmp(*(char **)Vector_at(strings, 2), "Frank") == 0);

    printf("...OK\n");
}

void can_get_value_at_index(void) {
    printf("can get value at index");
    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    struct Vector *strings =
        Vector_create(sizeof(char **), dealloc_string, compare_string, NULL);

    for (size_t i = 0; i < 20; i++) {
        Vector_push(numbers, &i);
        if (i % 2 == 0)
            Vector_push(strings, create_string_container("hello"));
        else
            Vector_push(strings, create_string_container("jello"));
    }

    assert(*(int *)Vector_at(numbers, 18) == 18);
    assert(strcmp(*(char **)Vector_at(strings, 16), "hello") == 0);

    printf("...OK\n");
}

void can_check_empty_state(void) {
    printf("can check empty state");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    assert(Vector_isEmpty(numbers) == true);

    int value = 10;
    Vector_push(numbers, &value);
    assert(Vector_isEmpty(numbers) == false);

    printf("...OK\n");
}

void can_get_capacity(void) {
    printf("can get capacity");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    assert(Vector_capacity(numbers) == INITIAL_CAPACITY);

    for (size_t i = 0; i < 20; i++)
        Vector_push(numbers, &i);
    assert(Vector_capacity(numbers) == INITIAL_CAPACITY << 1);

    for (size_t i = 0; i < 15; i++)
        Vector_pop(numbers);
    assert(Vector_capacity(numbers) == INITIAL_CAPACITY);

    for (size_t i = 0; i < 15; i++)
        Vector_push(numbers, &i);
    for (size_t i = 0; i < 15; i++)
        Vector_delete(numbers, 0);
    assert(Vector_capacity(numbers) == INITIAL_CAPACITY);

    printf("...OK\n");
}

void can_get_size(void) {
    printf("can get size");

    struct Vector *numbers = Vector_create(sizeof(int), NULL, NULL, NULL);
    assert(Vector_size(numbers) == 0);

    for (size_t i = 0; i < 20; i++)
        Vector_push(numbers, &i);
    assert(Vector_size(numbers) == 20);

    int value = 10;
    Vector_insert(numbers, 3, &value);
    assert(Vector_size(numbers) == 21);

    Vector_remove(numbers, &value);
    assert(Vector_size(numbers) == 19);

    for (size_t i = 0; i < 19; i++)
        Vector_pop(numbers);
    assert(Vector_size(numbers) == 0);

    printf("...OK\n");
}

void print_int(void *vp) { printf("%d", *(int *)vp); }
void dealloc_string(void *vp) { free(*(char **)vp); }
bool compare_string(void *vp1, void *vp2) {
    return strcmp(*(char **)vp1, *(char **)vp2) == 0;
}
void print_string(void *vp) { printf("'%s'", *(char **)vp); }
const char **create_string_container(const char *s) {
    const char **container = (const char **)malloc(sizeof(char **));
    assert(container != NULL);
    *container = strdup(s);

    return container;
}
