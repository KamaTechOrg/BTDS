#include "HashTable.h"
#include "hash_table_test.h"
#include <stdint.h>


TEST_FUN_IMPL(HTTest, CreateAndDestroy) {
    // Arrange
    
    HT* table = HT_Create(10, HT_HASH_FUN);

    // Assert
    TEST_ASSERT(table != NULL);
    TEST_ASSERT(table->size == 10);
    TEST_ASSERT(table->buckets != NULL);

    // Cleanup
    HT_Free(table);
} END_FUN

TEST_FUN_IMPL(HTTest, InsertAndSearch) {
    // Arrange
    HT* table = HT_Create(10, HT_HASH_FUN);
    HT_KEY_DATA_TYPE key = 42;
    HT_VALUE_DATA_TYPE value1 = 100;
    HT_VALUE_DATA_TYPE value2 = 200;
    HT_VALUE_DATA_TYPE retrieved_value;

    // Act & Assert - First insertion
    int insertResult = HT_Insert(table, key, value1);
    TEST_ASSERT(insertResult == 1);
    
    HT_Values_It it = HT_Search(table, key);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value1);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);  // No more values
    HT_Iterator_Free(it);

    // Act & Assert - Second insertion with same key
    insertResult = HT_Insert(table, key, value2);
    TEST_ASSERT(insertResult == 1);
    
    it = HT_Search(table, key);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value2);  // Should get most recent value first
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value1);  // Then the older value
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);  // No more values
    HT_Iterator_Free(it);

    // Cleanup
    HT_Free(table);
} END_FUN

TEST_FUN_IMPL(HTTest, Remove) {
    // Arrange
    HT* table = HT_Create(10, HT_HASH_FUN);
    HT_KEY_DATA_TYPE key = 42;
    HT_VALUE_DATA_TYPE value1 = 100;
    HT_VALUE_DATA_TYPE value2 = 200;
    HT_VALUE_DATA_TYPE retrieved_value;
    
    // Insert multiple entries with same key
    HT_Insert(table, key, value1);
    HT_Insert(table, key, value2);

    // Act - Remove entries with the key
    int removeResult = HT_Remove(table, key);

    // Assert
    TEST_ASSERT(removeResult == 1); // Should return 1 as at least one entry was removed
    
    HT_Values_It it = HT_Search(table, key);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0); // Should not find any values
    HT_Iterator_Free(it);

    // Cleanup
    HT_Free(table);
} END_FUN

TEST_FUN_IMPL(HTTest, Chaining) {
    // Arrange
    HT* table = HT_Create(10, HT_HASH_FUN);
    
    // These keys will have the same hash (both % 10 = 2)
    HT_KEY_DATA_TYPE key1 = 12;
    HT_KEY_DATA_TYPE key2 = 22;
    HT_VALUE_DATA_TYPE value1 = 100;
    HT_VALUE_DATA_TYPE value2 = 200;
    HT_VALUE_DATA_TYPE retrieved_value;

    // Act - Insert values with different keys but same hash
    TEST_ASSERT(HT_Insert(table, key1, value1) == 1);
    TEST_ASSERT(HT_Insert(table, key2, value2) == 1);

    // Assert - Verify both values are stored correctly despite hash collision
    HT_Values_It it = HT_Search(table, key1);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value1);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
    HT_Iterator_Free(it);

    it = HT_Search(table, key2);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value2);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
    HT_Iterator_Free(it);

    // Act - Remove one key
    TEST_ASSERT(HT_Remove(table, key1) == 1);

    // Assert - Verify other key still exists
    it = HT_Search(table, key1);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
    HT_Iterator_Free(it);

    it = HT_Search(table, key2);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
    TEST_ASSERT(retrieved_value == value2);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
    HT_Iterator_Free(it);

    // Cleanup
    HT_Free(table);
} END_FUN

TEST_FUN_IMPL(HTTest, MultipleValuesForKey) {
    // Arrange
    HT* table = HT_Create(10, HT_HASH_FUN);
    HT_KEY_DATA_TYPE key = 42;
    HT_VALUE_DATA_TYPE retrieved_value;
    
    // Act & Assert - Insert multiple values and verify iterator behavior
    for(int i = 1; i <= 5; i++) {
        // Insert new value
        TEST_ASSERT(HT_Insert(table, key, i) == 1);
        
        // Verify values through iterator
        HT_Values_It it = HT_Search(table, key);
        TEST_ASSERT(it != NULL);
        
        // Should get values in reverse order (most recent first)
        for(int j = i; j >= 1; j--) {
            TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
            TEST_ASSERT(retrieved_value == j);
        }
        TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
        HT_Iterator_Free(it);
    }

    // Act - Remove all values
    TEST_ASSERT(HT_Remove(table, key) == 1);
    
    // Assert - Verify all values are removed
    HT_Values_It it = HT_Search(table, key);
    TEST_ASSERT(it != NULL);
    TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
    HT_Iterator_Free(it);

    // Cleanup
    HT_Free(table);
} END_FUN

TEST_FUN_IMPL(HTTest, BucketDistribution) {
    // Arrange
    HT* table = HT_Create(10, HT_HASH_FUN);
    HT_VALUE_DATA_TYPE retrieved_value;
    
    // Act - Insert values that should go to different buckets
    for(int i = 0; i < 10; i++) {
        HT_KEY_DATA_TYPE key = i;
        TEST_ASSERT(HT_Insert(table, key, i) == 1);
    }

    // Assert - Verify each value is in its correct bucket
    for(int i = 0; i < 10; i++) {
        HT_Values_It it = HT_Search(table, i);
        TEST_ASSERT(it != NULL);
        TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 1);
        TEST_ASSERT(retrieved_value == i);
        TEST_ASSERT(HT_Iterator_Next(it, &retrieved_value) == 0);
        HT_Iterator_Free(it);
    }

    // Cleanup
    HT_Free(table);
} END_FUN

INIT_TEST_SUITE(HTTest)
BIND_TEST(HTTest, CreateAndDestroy)
BIND_TEST(HTTest, InsertAndSearch)
BIND_TEST(HTTest, Remove)
BIND_TEST(HTTest, Chaining)
BIND_TEST(HTTest, MultipleValuesForKey)
BIND_TEST(HTTest, BucketDistribution)
END_INIT_TEST_SUITE(HTTest)
