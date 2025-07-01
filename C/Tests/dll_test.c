#include "DLL.h"
#include "dll_test.h"

#include <stdlib.h>

TEST_FUN_IMPL(DLLTest, CreateAndDestroy) {
    DLL* list = DLL_Create();
    TEST_ASSERT(list != NULL);
    TEST_ASSERT(DLL_Size(list) == 0);
    DLL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(DLLTest, InsertFrontAndBack) {
    DLL* list = DLL_Create();
    TEST_ASSERT(list != NULL);

    // Insert at front
    TEST_ASSERT(DLL_InsertFront(list, 1) == 0);
    TEST_ASSERT(DLL_InsertFront(list, 2) == 0);
    TEST_ASSERT(DLL_Size(list) == 2);

    // Insert at back
    TEST_ASSERT(DLL_InsertBack(list, 3) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 4) == 0);
    TEST_ASSERT(DLL_Size(list) == 4);

    // Verify order: 2 -> 1 -> 3 -> 4
    DLL_DATA_TYPE value;
    TEST_ASSERT(DLL_GetAt(list, 0, &value) && value == 2);
    TEST_ASSERT(DLL_GetAt(list, 1, &value) && value == 1);
    TEST_ASSERT(DLL_GetAt(list, 2, &value) && value == 3);
    TEST_ASSERT(DLL_GetAt(list, 3, &value) && value == 4);

    DLL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(DLLTest, RemoveElements) {
    DLL* list = DLL_Create();
    TEST_ASSERT(list != NULL);

    // Add elements
    TEST_ASSERT(DLL_InsertBack(list, 1) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 2) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 3) == 0);
    TEST_ASSERT(DLL_Size(list) == 3);

    // Remove middle element
    TEST_ASSERT(DLL_Remove(list, 2) == 0);
    TEST_ASSERT(DLL_Size(list) == 2);

    // Verify remaining elements: 1 -> 3
    DLL_DATA_TYPE value;
    TEST_ASSERT(DLL_GetAt(list, 0, &value) && value == 1);
    TEST_ASSERT(DLL_GetAt(list, 1, &value) && value == 3);

    // Remove non-existent element
    TEST_ASSERT(DLL_Remove(list, 4) == -1);
    TEST_ASSERT(DLL_Size(list) == 2);

    DLL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(DLLTest, GetAndSetAt) {
    DLL* list = DLL_Create();
    TEST_ASSERT(list != NULL);

    // Add elements
    TEST_ASSERT(DLL_InsertBack(list, 1) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 2) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 3) == 0);

    // Test GetAt
    DLL_DATA_TYPE value;
    TEST_ASSERT(DLL_GetAt(list, 1, &value) && value == 2);
    TEST_ASSERT(!DLL_GetAt(list, 3, &value));  // Out of bounds

    // Test SetAt
    TEST_ASSERT(DLL_SetAt(list, 1, 42) == 0);
    TEST_ASSERT(DLL_GetAt(list, 1, &value) && value == 42);
    TEST_ASSERT(DLL_SetAt(list, 3, 10) == -1);  // Out of bounds

    DLL_Free(list);
    
} END_FUN

TEST_FUN_IMPL(DLLTest, FirstAndLast) {
    DLL* list = DLL_Create();
    TEST_ASSERT(list != NULL);

    // Test empty list
    DLL_DATA_TYPE value;
    TEST_ASSERT(!DLL_GetFirst(list, &value));
    TEST_ASSERT(!DLL_GetLast(list, &value));

    // Add elements
    TEST_ASSERT(DLL_InsertBack(list, 1) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 2) == 0);
    TEST_ASSERT(DLL_InsertBack(list, 3) == 0);

    // Test first and last
    TEST_ASSERT(DLL_GetFirst(list, &value) && value == 1);
    TEST_ASSERT(DLL_GetLast(list, &value) && value == 3);

    DLL_Free(list);
    
} END_FUN

INIT_TEST_SUITE(DLLTest)
BIND_TEST(DLLTest, CreateAndDestroy)
BIND_TEST(DLLTest, InsertFrontAndBack)
BIND_TEST(DLLTest, RemoveElements)
BIND_TEST(DLLTest, GetAndSetAt)
BIND_TEST(DLLTest, FirstAndLast)
END_INIT_TEST_SUITE(DLLTest) 