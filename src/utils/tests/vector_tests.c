#include <unity.h>

#include "utils/vector.h"

void setUp(void)
{}

void tearDown(void)
{}

void test_vector_create(void)
{
    struct vector *vec = vector_create(10, sizeof(int));
    TEST_ASSERT_NOT_NULL(vec);
    TEST_ASSERT_NOT_NULL(vec->data);
    TEST_ASSERT_EQUAL(0, vec->size);
    TEST_ASSERT_EQUAL(10, vec->capacity);
    TEST_ASSERT_EQUAL(sizeof(int), vec->elt_size);
    vector_free(vec);
}

void test_vector_pushback(void)
{
    struct vector *vec = vector_create(2, sizeof(int));
    int a = 1, b = 2, c = 3;

    vector_pushback(vec, &a);
    vector_pushback(vec, &b);
    TEST_ASSERT_EQUAL(2, vec->size);
    TEST_ASSERT_EQUAL(2, vec->capacity);

    vector_pushback(vec, &c);
    TEST_ASSERT_EQUAL(3, vec->size);
    TEST_ASSERT_EQUAL(4, vec->capacity);

    int *data = (int *)vec->data;
    TEST_ASSERT_EQUAL_INT(a, data[0]);
    TEST_ASSERT_EQUAL_INT(b, data[1]);
    TEST_ASSERT_EQUAL_INT(c, data[2]);

    vector_free(vec);
}

void test_vector_get(void)
{
    struct vector *vec = vector_create(2, sizeof(int));
    int a = 1, b = 2;
    vector_pushback(vec, &a);
    vector_pushback(vec, &b);

    int *pa = vector_get(vec, 0);
    int *pb = vector_get(vec, 1);
    TEST_ASSERT_NOT_NULL(pa);
    TEST_ASSERT_NOT_NULL(pb);
    TEST_ASSERT_EQUAL_INT(a, *pa);
    TEST_ASSERT_EQUAL_INT(b, *pb);

    int *pc = vector_get(vec, 2);
    TEST_ASSERT_NULL(pc);

    vector_free(vec);
}

void test_vector_pop(void)
{
    struct vector *vec = vector_create(2, sizeof(int));
    int a = 1, b = 2, c = 3;
    vector_pushback(vec, &a);
    vector_pushback(vec, &b);
    vector_pushback(vec, &c);

    TEST_ASSERT_TRUE(vector_pop(vec, 1));
    TEST_ASSERT_EQUAL(2, vec->size);

    int *data = (int *)vec->data;
    TEST_ASSERT_EQUAL_INT(a, data[0]);
    TEST_ASSERT_EQUAL_INT(c, data[1]);

    TEST_ASSERT_FALSE(vector_pop(vec, 5));

    vector_free(vec);
}

void test_vector_resize(void)
{
    struct vector *vec = vector_create(2, sizeof(int));
    vector_resize(vec, 5);
    TEST_ASSERT_EQUAL(5, vec->capacity);

    vector_resize(vec, 1);
    TEST_ASSERT_EQUAL(1, vec->capacity);
    TEST_ASSERT_EQUAL(0, vec->size);

    vector_free(vec);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_vector_create);
    RUN_TEST(test_vector_pushback);
    RUN_TEST(test_vector_get);
    RUN_TEST(test_vector_pop);
    RUN_TEST(test_vector_resize);
    return UNITY_END();
}