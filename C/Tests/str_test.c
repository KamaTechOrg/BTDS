#include "Str.h"
#include "STR_test.h"

#include <string.h>

TEST_FUN_IMPL(StrTest, CreateAndDestroy) {
    // Arrange
    const uint64_t len = 10;
    STR s = STR_Create(len);

    // Assert
    TEST_ASSERT(s.s != NULL);
    TEST_ASSERT(s.n == len);
    TEST_ASSERT(strlen(s.s) == 0);  // Should be empty initially

    // Cleanup
    STR_Free(s);
} END_FUN

TEST_FUN_IMPL(StrTest, InitFromString) {
    // Arrange
    const char* test_str = "Hello, World!";
    
    // Act
    STR s = STR_Copy_raw(test_str);

    // Assert
    TEST_ASSERT(s.s != NULL);
    TEST_ASSERT(s.n == strlen(test_str));
    TEST_ASSERT_STR_EQ(s.s, test_str)

    // Cleanup
    STR_Free(s);
} END_FUN

TEST_FUN_IMPL(StrTest, InitFromNullString) {
    // Act
    STR s = STR_Copy_raw(NULL);

    // Assert
    TEST_ASSERT(s.s == NULL);
    TEST_ASSERT(s.n == 0);
} END_FUN

TEST_FUN_IMPL(StrTest, InitZeroLength) {
    // Act
    STR s = STR_Create(0);

    // Assert
    TEST_ASSERT(s.s != NULL);
    TEST_ASSERT(s.n == 0);
    TEST_ASSERT(s.s[0] == '\0');

    // Cleanup
    STR_Free(s);
} END_FUN

TEST_FUN_IMPL(StrTest, FreeNull) {
    // Arrange
    STR s = {0};
    s.s = NULL;
    s.n = 0;

    // Act & Assert - should not crash
    STR_Free(s);
} END_FUN

INIT_TEST_SUITE(StrTest)
BIND_TEST(StrTest, CreateAndDestroy)
BIND_TEST(StrTest, InitFromString)
BIND_TEST(StrTest, InitFromNullString)
BIND_TEST(StrTest, InitZeroLength)
BIND_TEST(StrTest, FreeNull)
END_INIT_TEST_SUITE(StrTest) 