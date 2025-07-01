#include "LL.h"
#include "ll_test.h"
#include "UnitTestsInfra.h"
#include <stdlib.h>

TEST_FUN_IMPL(LLTest, CreateAndDestroy) {
    LL* list = LL_Create();
    TEST_ASSERT(list != NULL);
    TEST_ASSERT(LL_Size(list) == 0);
    LL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(LLTest, InsertFrontAndBack) {
    LL* list = LL_Create();
    TEST_ASSERT(list != NULL);

    // Insert at front
    TEST_ASSERT(LL_InsertFront(list, 1) == 0);
    TEST_ASSERT(LL_InsertFront(list, 2) == 0);
    TEST_ASSERT(LL_Size(list) == 2);

    // Insert at back
    TEST_ASSERT(LL_InsertBack(list, 3) == 0);
    TEST_ASSERT(LL_InsertBack(list, 4) == 0);
    TEST_ASSERT(LL_Size(list) == 4);

    // Verify order: 2 -> 1 -> 3 -> 4
    LL_DATA_TYPE value;
    TEST_ASSERT(LL_GetAt(list, 0, &value) && value == 2);
    TEST_ASSERT(LL_GetAt(list, 1, &value) && value == 1);
    TEST_ASSERT(LL_GetAt(list, 2, &value) && value == 3);
    TEST_ASSERT(LL_GetAt(list, 3, &value) && value == 4);

    LL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(LLTest, RemoveElements) {
    LL* list = LL_Create();
    TEST_ASSERT(list != NULL);

    // Add elements
    TEST_ASSERT(LL_InsertBack(list, 1) == 0);
    TEST_ASSERT(LL_InsertBack(list, 2) == 0);
    TEST_ASSERT(LL_InsertBack(list, 3) == 0);
    TEST_ASSERT(LL_Size(list) == 3);

    // Remove middle element
    TEST_ASSERT(LL_Remove(list, 2) == 0);
    TEST_ASSERT(LL_Size(list) == 2);

    // Verify remaining elements: 1 -> 3
    LL_DATA_TYPE value;
    TEST_ASSERT(LL_GetAt(list, 0, &value) && value == 1);
    TEST_ASSERT(LL_GetAt(list, 1, &value) && value == 3);

    // Remove non-existent element
    TEST_ASSERT(LL_Remove(list, 4) == -1);
    TEST_ASSERT(LL_Size(list) == 2);

    LL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(LLTest, GetAndSetAt) {
    LL* list = LL_Create();
    TEST_ASSERT(list != NULL);

    // Add elements
    TEST_ASSERT(LL_InsertBack(list, 1) == 0);
    TEST_ASSERT(LL_InsertBack(list, 2) == 0);
    TEST_ASSERT(LL_InsertBack(list, 3) == 0);

    // Test GetAt
    LL_DATA_TYPE value;
    TEST_ASSERT(LL_GetAt(list, 1, &value) && value == 2);
    TEST_ASSERT(!LL_GetAt(list, 3, &value));  // Out of bounds

    // Test SetAt
    TEST_ASSERT(LL_SetAt(list, 1, 42) == 0);
    TEST_ASSERT(LL_GetAt(list, 1, &value) && value == 42);
    TEST_ASSERT(LL_SetAt(list, 3, 10) == -1);  // Out of bounds

    LL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(LLTest, Contains) {
    LL* list = LL_Create();
    TEST_ASSERT(list != NULL);

    // Add elements
    TEST_ASSERT(LL_InsertBack(list, 1) == 0);
    TEST_ASSERT(LL_InsertBack(list, 2) == 0);
    TEST_ASSERT(LL_InsertBack(list, 3) == 0);

    // Test Contains
    TEST_ASSERT(LL_Contains(list, 2));
    TEST_ASSERT(!LL_Contains(list, 4));

    LL_Free(list);
    
} END_FUN

INIT_TEST_SUITE(LLTest)
BIND_TEST(LLTest, CreateAndDestroy)
BIND_TEST(LLTest, InsertFrontAndBack)
BIND_TEST(LLTest, RemoveElements)
BIND_TEST(LLTest, GetAndSetAt)
BIND_TEST(LLTest, Contains)
END_INIT_TEST_SUITE(LLTest) 