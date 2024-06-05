#include <unity.h>

#include "volume/file.h"

void setUp(void)
{}

void tearDown(void)
{}

void test_file_create(void)
{
    struct file *file = file_create("testfile", 100, 0, "owner", false);
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_EQUAL_STRING("testfile", file->name);
    TEST_ASSERT_EQUAL(100, file->size);
    TEST_ASSERT_EQUAL(0, file->offset);
    TEST_ASSERT_EQUAL_STRING("owner", file->owner);
    TEST_ASSERT_FALSE(file->is_dir);
    TEST_ASSERT_NOT_NULL(file->children);
    TEST_ASSERT_EQUAL(0, file->children->size);
    TEST_ASSERT_EQUAL(sizeof(struct file *), file->children->elt_size);

    file_free(file);
}

void test_file_addchild(void)
{
    struct file *dir = file_create("dir", 0, 0, "owner", true);
    struct file *child1 = file_create("child1", 50, 0, "owner", false);
    struct file *child2 = file_create("child2", 30, 0, "owner", false);

    TEST_ASSERT_EQUAL_PTR(child1, file_addchild(dir, child1));
    TEST_ASSERT_EQUAL(1, dir->children->size);
    TEST_ASSERT_EQUAL_PTR(child2, file_addchild(dir, child2));
    TEST_ASSERT_EQUAL(2, dir->children->size);

    struct file **data = dir->children->data;
    TEST_ASSERT_EQUAL_PTR(child1, data[0]);
    TEST_ASSERT_EQUAL_PTR(child2, data[1]);

    file_free(child1);
    file_free(child2);
    file_free(dir);
}

void test_file_delchild(void)
{
    struct file *dir = file_create("dir", 0, 0, "owner", true);
    struct file *child1 = file_create("child1", 50, 0, "owner", false);
    struct file *child2 = file_create("child2", 30, 0, "owner", false);
    file_addchild(dir, child1);
    file_addchild(dir, child2);

    TEST_ASSERT_TRUE(file_delchild(dir, 0));
    TEST_ASSERT_EQUAL(1, dir->children->size);

    struct file **data = dir->children->data;
    TEST_ASSERT_EQUAL_PTR(child2, data[0]);

    TEST_ASSERT_FALSE(file_delchild(dir, 5));

    file_free(child1);
    file_free(child2);
    file_free(dir);
}

void test_file_isreg(void)
{
    struct file *file = file_create("file", 100, 0, "owner", false);
    struct file *dir = file_create("dir", 0, 0, "owner", true);

    TEST_ASSERT_TRUE(file_isreg(file));
    TEST_ASSERT_FALSE(file_isreg(dir));

    file_free(file);
    file_free(dir);
}

void test_file_nodec(void)
{
    struct file *dir = file_create("dir", 0, 0, "owner", true);
    struct file *child1 = file_create("child1", 50, 0, "owner", false);
    struct file *child2 = file_create("child2", 30, 0, "owner", false);
    file_addchild(dir, child1);
    file_addchild(dir, child2);

    TEST_ASSERT_EQUAL(3, file_nodec(dir));
    TEST_ASSERT_EQUAL(1, file_nodec(child1));

    file_free(child1);
    file_free(child2);
    file_free(dir);
}

void test_file_recsize(void)
{
    struct file *dir = file_create("dir", 0, 0, "owner", true);
    struct file *child1 = file_create("child1", 50, 0, "owner", false);
    struct file *child2 = file_create("child2", 30, 0, "owner", false);
    file_addchild(dir, child1);
    file_addchild(dir, child2);

    TEST_ASSERT_EQUAL(80, file_recsize(dir));
    TEST_ASSERT_EQUAL(50, file_recsize(child1));

    file_free(child1);
    file_free(child2);
    file_free(dir);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_file_create);
    RUN_TEST(test_file_addchild);
    RUN_TEST(test_file_delchild);
    RUN_TEST(test_file_isreg);
    RUN_TEST(test_file_nodec);
    RUN_TEST(test_file_recsize);

    return UNITY_END();
}
