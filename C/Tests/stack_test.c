#include "Stack.h"
#include "stack_test.h"

TEST_FUN_IMPL(StackTest, StackCreationAndBasicOperations) {
    Stack* s = Stack_Create(10);
    TEST_ASSERT(s != NULL);
    TEST_ASSERT_EQ(Stack_GetCapacity(s), 10, "%d");
    TEST_ASSERT_EQ(Stack_GetSize(s), 0, "%d");
    TEST_ASSERT(Stack_IsEmpty(s));
    TEST_ASSERT(!Stack_IsFull(s));
    Stack_Free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, PushAndPeekOperations) {
    Stack* s = Stack_Create(2);
    bool pushResult = Stack_Push(s, 'A');
    TEST_ASSERT(pushResult);
    TEST_ASSERT_EQ(Stack_GetSize(s), 1, "%d");

    Stack_DATA_TYPE top;
    bool peekResult = Stack_Peek(s, &top);
    TEST_ASSERT(peekResult);
    TEST_ASSERT_EQ(top, 'A', "%c");
    Stack_Free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, PopOperation) {
    Stack* s = Stack_Create(2);
    Stack_Push(s, 'A');
    Stack_Push(s, 'B');

    Stack_DATA_TYPE popped;
    bool popResult = Stack_Pop(s, &popped);
    TEST_ASSERT(popResult);
    TEST_ASSERT_EQ(popped, 'B', "%c");
    TEST_ASSERT_EQ(Stack_GetSize(s), 1, "%d");
    Stack_Free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, FullStack) {
    Stack* s = Stack_Create(1);
    Stack_Push(s, 'A');
    TEST_ASSERT(Stack_IsFull(s));
    TEST_ASSERT(!Stack_Push(s, 'B')); // Should not be able to push on full stack
    Stack_Free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, EmptyStack) {
    Stack* s = Stack_Create(1);
    TEST_ASSERT(Stack_IsEmpty(s));

    Stack_DATA_TYPE popped;
    TEST_ASSERT(!Stack_Pop(s, &popped)); // Should not pop from an empty stack
    Stack_Free(s);
} END_FUN

INIT_TEST_SUITE(StackTest)
BIND_TEST(StackTest, StackCreationAndBasicOperations)
BIND_TEST(StackTest, PushAndPeekOperations)
BIND_TEST(StackTest, PopOperation)
BIND_TEST(StackTest, FullStack)
BIND_TEST(StackTest, EmptyStack)
END_INIT_TEST_SUITE(StackTest)
