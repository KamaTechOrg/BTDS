#include "Set.h"
#include "set_test.h"

TEST_FUN_IMPL(SetTest, CreateAndDestroy) {
    Set* set = Set_Create(10);
    TEST_ASSERT(set != NULL);
    Set_Free(set);
} END_FUN

TEST_FUN_IMPL(SetTest, AddAndContains) {
    Set* set = Set_Create(10);
    TEST_ASSERT(set != NULL);

    TEST_ASSERT(Set_Add(set, 1) == 0);
    TEST_ASSERT(Set_Add(set, 2) == 0);
    TEST_ASSERT(Set_Add(set, 3) == 0);

    TEST_ASSERT(Set_Contains(set, 1));
    TEST_ASSERT(Set_Contains(set, 2));
    TEST_ASSERT(Set_Contains(set, 3));
    TEST_ASSERT(!Set_Contains(set, 4));

    TEST_ASSERT(Set_Count(set) == 3);

    Set_Free(set);
} END_FUN

TEST_FUN_IMPL(SetTest, DuplicateAdd) {
    Set* set = Set_Create(10);
    TEST_ASSERT(set != NULL);

    TEST_ASSERT(Set_Add(set, 1) == 0);
    TEST_ASSERT(Set_Add(set, 1) == 0);  // Adding same element should succeed but not change set
    TEST_ASSERT(Set_Count(set) == 1);

    Set_Free(set);
} END_FUN

TEST_FUN_IMPL(SetTest, Remove) {
    Set* set = Set_Create(10);
    TEST_ASSERT(set != NULL);

    TEST_ASSERT(Set_Add(set, 1) == 0);
    TEST_ASSERT(Set_Add(set, 2) == 0);
    TEST_ASSERT(Set_Add(set, 3) == 0);

    TEST_ASSERT(Set_Remove(set, 2) == 0);
    TEST_ASSERT(!Set_Contains(set, 2));
    TEST_ASSERT(Set_Count(set) == 2);

    TEST_ASSERT(Set_Remove(set, 4) == -1);  // Remove non-existent element
    TEST_ASSERT(Set_Count(set) == 2);

    Set_Free(set);
} END_FUN

INIT_TEST_SUITE(SetTest)
BIND_TEST(SetTest, CreateAndDestroy)
BIND_TEST(SetTest, AddAndContains)
BIND_TEST(SetTest, DuplicateAdd)
BIND_TEST(SetTest, Remove)
END_INIT_TEST_SUITE(SetTest) 