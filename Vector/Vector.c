#include "Vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

struct Vector *Vector_create(size_t item_size, void (*dealloc)(void *),
                             bool (*compare)(void *, void *),
                             void (*print)(void *)) {
    struct Vector *v = (struct Vector *)malloc(sizeof(struct Vector));
    assert(v != NULL);

    v->items = malloc(INITIAL_CAPACITY * item_size);
    assert(v->items != NULL);

    v->item_size = item_size;
    v->sz = 0;
    v->cp = INITIAL_CAPACITY;
    v->dealloc = dealloc;
    v->compare = compare;
    v->print = print;

    return v;
}

size_t Vector_size(struct Vector *v) { return v->sz; }

size_t Vector_capacity(struct Vector *v) { return v->cp; }

bool Vector_isEmpty(struct Vector *v) { return v->sz == 0; }

void *Vector_at(struct Vector *v, size_t index) {
    assert(index >= 0 && index < v->sz);

    void *value = malloc(v->item_size);
    assert(value != NULL);

    void *addr = (char *)v->items + index * v->item_size;
    memcpy(value, addr, v->item_size);

    return value;
}

void Vector_push(struct Vector *v, void *item) {
    if (v->sz == v->cp)
        __Vector_resize(v, v->cp << 1);

    void *addr = (char *)v->items + v->sz++ * v->item_size;
    memcpy(addr, item, v->item_size);
}

void Vector_insert(struct Vector *v, size_t index, void *item) {
    assert(index >= 0 && index < v->sz);

    if (v->sz == v->cp)
        __Vector_resize(v, v->cp << 1);

    void *addr = (char *)v->items + index * v->item_size;
    void *end = (char *)v->items + v->sz * v->item_size;
    memmove((char *)addr + v->item_size, addr,
            (size_t)((char *)end - (char *)addr));
    memcpy(addr, item, v->item_size);
    v->sz++;
}

void Vector_prepend(struct Vector *v, void *item) { Vector_insert(v, 0, item); }

void *Vector_pop(struct Vector *v) {
    if (v->sz == 0)
        return NULL;

    void *value = malloc(v->item_size);
    assert(value != NULL);

    void *addr = (char *)v->items + --v->sz * v->item_size;
    memcpy(value, addr, v->item_size);

    if (v->sz <= (v->cp >> 2))
        __Vector_resize(v, v->cp >> 1);

    return value;
}

void Vector_delete(struct Vector *v, size_t index) {
    assert(index >= 0 && index < v->sz);

    void *addr = (char *)v->items + index * v->item_size;
    if (v->dealloc != NULL)
        v->dealloc(addr);
    void *nextAddr = (char *)addr + v->item_size;
    void *end = (char *)v->items + v->sz * v->item_size;
    memmove(addr, nextAddr, (size_t)((char *)end - (char *)nextAddr));
    v->sz--;

    if (v->sz <= (v->cp >> 2))
        __Vector_resize(v, v->cp >> 1);
}

void Vector_remove(struct Vector *v, void *item) {
    for (size_t i = 0; i < v->sz; i++) {
        void *addr = (char *)v->items + i * v->item_size;
        if ((v->compare != NULL && v->compare(addr, item)) ||
            memcmp(addr, item, v->item_size) == 0)
            Vector_delete(v, i--);
    }
}

int Vector_find(struct Vector *v, void *item) {
    for (size_t i = 0; i < v->sz; i++) {
        void *addr = (char *)v->items + i * v->item_size;
        if ((v->compare != NULL && v->compare(addr, item)) ||
            memcmp(addr, item, v->item_size) == 0)
            return (int)i;
    }
    return -1;
}

void Vector_print(struct Vector *v) {
    assert(v->print != NULL);

    for (size_t i = 0; i < v->sz; i++) {
        void *addr = (char *)v->items + i * v->item_size;
        putchar(' ');
        putchar('[');
        v->print(addr);
        putchar(']');
    }
    putchar('\n');
}

void __Vector_resize(struct Vector *v, size_t new_capacity) {
    v->items = realloc(v->items, v->item_size * new_capacity);
    v->cp = new_capacity;
    assert(v->items != NULL);
}
