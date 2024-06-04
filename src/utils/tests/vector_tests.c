#include <unity.h>

#include "utils/vector.h"

void setUp(void)
{}

void tearDown(void)
{}

void will_pass(void)
{
    TEST_ASSERT(true);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(will_pass);
    return UNITY_END();
}