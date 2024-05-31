#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

struct vector
{
    void *data;
    size_t size;
    size_t capacity;
    size_t elt_size;
};

struct vector *vector_create(size_t capacity, size_t elt_size);
bool vector_resize(struct vector *vec, size_t capacity);
bool vector_pushback(struct vector *vec, const void *elt);
void *vector_get(struct vector *vec, size_t index);
bool vector_pop(struct vector *vec, size_t index);
void vector_free(struct vector *vec);

#endif // VECTOR_H
