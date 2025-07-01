#include "Heap.h"
#include "Heap_test.h"

TEST_FUN_IMPL(HeapTest, HeapCreationAndBasicOperations) {
    Heap* h = Heap_Create(10);
    TEST_ASSERT(h != NULL);
    TEST_ASSERT_EQ(Heap_peek_min(h, NULL), false, "%d"); // Should fail because heap is empty
    Heap_Free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, InsertAndPeekMin) {
    Heap* h = Heap_Create(10);
    Heap_insert(h, 5);
    Heap_insert(h, 3);

    Heap_DATA_TYPE min;
    TEST_ASSERT(Heap_peek_min(h, &min));
    TEST_ASSERT_EQ(min, 3, "%d");
    Heap_Free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, InsertAndExtractMin) {
    Heap* h = Heap_Create(10);
    Heap_insert(h, 5);
    Heap_insert(h, 3);
    Heap_insert(h, 8);

    Heap_DATA_TYPE extracted;
    TEST_ASSERT(Heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 3, "%d");
    TEST_ASSERT(Heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 5, "%d");
    TEST_ASSERT(Heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 8, "%d");
    TEST_ASSERT_EQ(Heap_extract_min(h, &extracted), false, "%d"); // Heap should be empty now
    Heap_Free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, FullHeap) {
    Heap* h = Heap_Create(2);
    Heap_insert(h, 5);
    Heap_insert(h, 3);

    // Heap is full now; next insert should fail
    TEST_ASSERT_EQ(Heap_insert(h, 7), false, "%d");
    Heap_Free(h);
} END_FUN

INIT_TEST_SUITE(HeapTest)
BIND_TEST(HeapTest, HeapCreationAndBasicOperations)
BIND_TEST(HeapTest, InsertAndPeekMin)
BIND_TEST(HeapTest, InsertAndExtractMin)
BIND_TEST(HeapTest, FullHeap)
END_INIT_TEST_SUITE(HeapTest)
