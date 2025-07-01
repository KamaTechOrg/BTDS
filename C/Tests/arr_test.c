#include "arr_test.h"
#include "ARR.h"

#include <stdio.h>
#include <string.h>

TEST_FUN_IMPL(ArrayTest, CreateAndDestroy) {
    printf("\nTesting ARR Create/Destroy...\n");
    
    // Test 1: Create 2D array
    uint64_t dims2d[] = {2, 3};
    ARR* arr2d = ARR_Create(dims2d, 2);
    TEST_ASSERT(arr2d != NULL);
    TEST_ASSERT_EQ((int)ARR_NumDimensions(arr2d)     , 2, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr2d,  0) , 2, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr2d,  1) , 3, "%d");
    TEST_ASSERT_EQ((int)ARR_TotalSize(arr2d)         , 6, "%d");
    ARR_Free(arr2d);
    
    // Test 2: Create 3D array
    uint64_t dims3d[] = {2, 3, 4};
    ARR* arr3d = ARR_Create(dims3d, 3);
    TEST_ASSERT(arr3d != NULL);
    TEST_ASSERT_EQ((int)ARR_NumDimensions(arr3d), 3, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 0), 2, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 1), 3, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 2), 4, "%d");
    TEST_ASSERT_EQ((int)ARR_TotalSize(arr3d), 24, "%d");
    ARR_Free(arr3d);
    
    // Test 3: Invalid creation
    TEST_ASSERT(ARR_Create(NULL, 2) == NULL);
    
    TEST_ASSERT(ARR_Create(dims2d, 0) == NULL);
    
    printf("ARR Create/Destroy tests passed!\n");
    return 0;
} END_FUN

TEST_FUN_IMPL(ArrayTest, GetAndSet) {
    printf("\nTesting ARR Get/Set...\n");
    
    // Create 2D array
    uint64_t dims[] = {2, 3};
    ARR* arr = ARR_Create(dims, 2);
    TEST_ASSERT(arr != NULL);
    
    // Test setting and getting values
    uint64_t indices[] = {0, 0};
    TEST_ASSERT_EQ(ARR_Set(arr, indices, 1), 1, "%d");
    TEST_ASSERT_EQ(*ARR_Get(arr, indices), 1, "%d");
    
    indices[0] = 1;
    indices[1] = 2;
    TEST_ASSERT_EQ(ARR_Set(arr, indices, 42), 1, "%d");
    TEST_ASSERT_EQ(*ARR_Get(arr, indices), 42, "%d");
    
    // Test invalid indices
    indices[0] = 2;  // Out of bounds
    TEST_ASSERT_EQ(ARR_Set(arr, indices, 100), 0, "%d");
    TEST_ASSERT_EQ(ARR_Get(arr, indices), NULL, "%p");  // Default value for out of bounds
    
    ARR_Free(arr);
    printf("ARR Get/Set tests passed!\n");
    return 0;
} END_FUN

TEST_FUN_IMPL(ArrayTest, DimensionQueries) {
    printf("\nTesting ARR Dimensions...\n");
    
    // Test 1: 1D array
    uint64_t dims1d[] = {5};
    ARR* arr1d = ARR_Create(dims1d, 1);
    TEST_ASSERT(arr1d != NULL);
    TEST_ASSERT_EQ((int)ARR_NumDimensions(arr1d), 1, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr1d, 0), 5, "%d");
    TEST_ASSERT_EQ((int)ARR_TotalSize(arr1d), 5, "%d");
    ARR_Free(arr1d);
    
    // Test 2: 3D array
    uint64_t dims3d[] = {2, 3, 4};
    ARR* arr3d = ARR_Create(dims3d, 3);
    TEST_ASSERT(arr3d != NULL);
    TEST_ASSERT_EQ((int)ARR_NumDimensions(arr3d), 3, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 0), 2, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 1), 3, "%d");
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 2), 4, "%d");
    TEST_ASSERT_EQ((int)ARR_TotalSize(arr3d), 24, "%d");
    
    // Test invalid dimension index
    TEST_ASSERT_EQ((int)ARR_DimensionSize(arr3d, 3), 0, "%d");
    
    ARR_Free(arr3d);
    printf("ARR Dimensions tests passed!\n");
    return 0;
} END_FUN

TEST_FUN_IMPL(ArrayTest, EdgeCases) {
    // Test 1: Empty array
    uint64_t dims[] = {0};
    TEST_ASSERT(ARR_Create(dims, 1) == NULL);

    // Test 2: Single element array
    dims[0] = 1;
    ARR* arr = ARR_Create(dims, 1);
    TEST_ASSERT(arr != NULL);
    TEST_ASSERT_EQ((int)ARR_TotalSize(arr), 1, "%d");
    uint64_t indices[] = {0};
    TEST_ASSERT_EQ(ARR_Set(arr, indices, 42), 1, "%d");
    TEST_ASSERT_EQ(*ARR_Get(arr, indices), 42, "%d");
    ARR_Free(arr);

    // Test 3: Out of bounds access
    dims[0] = 2;
    arr = ARR_Create(dims, 1);
    TEST_ASSERT(arr != NULL);
    indices[0] = 2;
    TEST_ASSERT_EQ(ARR_Set(arr, indices, 42), 0, "%d");
    TEST_ASSERT_EQ(ARR_Get(arr, indices), NULL, "%p");
    ARR_Free(arr);

    // Test 4: NULL indices
    dims[0] = 2;
    arr = ARR_Create(dims, 1);
    TEST_ASSERT(arr != NULL);
    TEST_ASSERT_EQ(ARR_Set(arr, NULL, 42), 0, "%d");
    TEST_ASSERT_EQ(ARR_Get(arr, NULL), NULL, "%p");
    ARR_Free(arr);
    return 0;
} END_FUN

INIT_TEST_SUITE(ArrayTest)
BIND_TEST(ArrayTest, CreateAndDestroy)
BIND_TEST(ArrayTest, GetAndSet)
BIND_TEST(ArrayTest, DimensionQueries)
BIND_TEST(ArrayTest, EdgeCases)
END_INIT_TEST_SUITE(ArrayTest) 