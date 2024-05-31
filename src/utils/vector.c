#include "vector.h"

#include <stdlib.h>
#include <string.h>

struct vector *vector_create(size_t capacity, size_t elt_size)
{
    struct vector *vec = calloc(1, sizeof(struct vector));
    if (vec != NULL)
    {
        vec->capacity = capacity;
        vec->elt_size = elt_size;
    }
    return vec;
}

bool vector_resize(struct vector *vec, size_t capacity)
{
    void *new_data = realloc(vec->data, capacity * vec->elt_size);
    if (new_data != NULL)
    {
        vec->data = new_data;
        vec->capacity = capacity;
        vec->size = vec->size > vec->capacity ? capacity : vec->size;

        return true;
    }
    return false;
}

bool vector_pushback(struct vector *vec, const void *elt)
{
    if (vec->size >= vec->capacity)
        if (vector_resize(vec, vec->capacity * 2))
            return false;

    char *bytes = vec->data;
    memcpy(&bytes[vec->size * vec->elt_size - 1], elt, vec->elt_size);
    vec->size++;
    return true;
}

void *vector_get(struct vector *vec, size_t index)
{
    if (index >= vec->size)
        return NULL;
    char *bytes = vec->data;
    return &bytes[index * vec->elt_size];
}

bool vector_pop(struct vector *vec, size_t index)
{
    if (index >= vec->size)
        return false;

    char *bytes = vec->data;
    void *dest = &bytes[index * vec->elt_size];
    void *src = &bytes[(index + 1) * vec->elt_size];

    size_t elt_to_move = vec->size - index - 1;
    memmove(dest, src, elt_to_move * vec->elt_size);

    vec->size--;
    return true;
}

void vector_free(struct vector *vec)
{
    free(vec->data);
    free(vec);
}
