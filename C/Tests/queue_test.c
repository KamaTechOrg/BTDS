#include "Queue.h"
#include "Queue_test.h"

TEST_FUN_IMPL(QueueTest, QueueCreationAndBasicOperations) {
    Queue* q = Queue_Create(10);
    TEST_ASSERT(q != NULL);
    TEST_ASSERT_EQ(Queue_GetCapacity(q), 10, "%d");
    TEST_ASSERT_EQ(Queue_GetSize(q), 0, "%d");
    TEST_ASSERT(Queue_IsEmpty(q));
    TEST_ASSERT(!Queue_IsFull(q));
    Queue_Free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, EnqueueAndPeekOperations) {
    Queue* q = Queue_Create(2);
    bool enqueueResult = Queue_Enqueue(q, 'A');
    TEST_ASSERT(enqueueResult);
    TEST_ASSERT_EQ(Queue_GetSize(q), 1, "%d");

    Queue_DATA_TYPE front;
    bool peekResult = Queue_Peek(q, &front);
    TEST_ASSERT(peekResult);
    TEST_ASSERT_EQ(front, 'A', "%c");
    Queue_Free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, DequeueOperation) {
    Queue* q = Queue_Create(2);
    Queue_Enqueue(q, 'A');
    Queue_Enqueue(q, 'B');

    Queue_DATA_TYPE dequeued;
    bool dequeueResult = Queue_Dequeue(q, &dequeued);
    TEST_ASSERT(dequeueResult);
    TEST_ASSERT_EQ(dequeued, 'A', "%c");
    TEST_ASSERT_EQ(Queue_GetSize(q), 1, "%d");
    Queue_Free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, FullQueue) {
    Queue* q = Queue_Create(1);
    Queue_Enqueue(q, 'A');
    TEST_ASSERT(Queue_IsFull(q));
    TEST_ASSERT(!Queue_Enqueue(q, 'B')); // Should not be able to enqueue on full queue
    Queue_Free(q);
} END_FUN

INIT_TEST_SUITE(QueueTest)
BIND_TEST(QueueTest, QueueCreationAndBasicOperations)
BIND_TEST(QueueTest, EnqueueAndPeekOperations)
BIND_TEST(QueueTest, DequeueOperation)
BIND_TEST(QueueTest, FullQueue)
END_INIT_TEST_SUITE(QueueTest)

