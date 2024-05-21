#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY 16

struct Vector {
    void *items;
    size_t item_size;
    size_t sz;
    size_t cp;
    void (*dealloc)(void *);
    bool (*compare)(void *, void *);
    void (*print)(void *);
};

struct Vector *Vector_create(size_t item_size, void (*dealloc)(void *vp),
                             bool (*compare)(void *a, void *b),
                             void (*print)(void *));

size_t Vector_size(struct Vector *v);

size_t Vector_capacity(struct Vector *v);

bool Vector_isEmpty(struct Vector *v);

void *Vector_at(struct Vector *v, size_t index);

void Vector_push(struct Vector *v, void *item);

void Vector_insert(struct Vector *v, size_t index, void *item);

void Vector_prepend(struct Vector *v, void *item);

void *Vector_pop(struct Vector *v);

void Vector_delete(struct Vector *v, size_t index);

void Vector_remove(struct Vector *v, void *item);

int Vector_find(struct Vector *v, void *item);

void Vector_print(struct Vector *v);

void __Vector_resize(struct Vector *v, size_t new_capacity);
