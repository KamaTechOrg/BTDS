#ifndef ARR_H
#define ARR_H

#include "data_types_config.h"

#include <stdlib.h>
#include <stdbool.h>
#include "POD_Utils.h"
#include "POD_Parser.h"

#ifndef ARR_DATA_TYPE
#define ARR_DATA_TYPE int
#endif

#define ARR_PARSE_FUN CAT(ARR_DATA_TYPE, _Parse)
#define ARR_FREE_ELEMENT_FUN CAT(ARR_DATA_TYPE, _Free)
#define ARR_ELEM_COPY CAT(ARR_DATA_TYPE, _Copy)

typedef struct {
    ARR_DATA_TYPE* data;        // Flattened array storing elements in row-major order
    uint64_t* dimensions;         // ARR storing size of each dimension
    uint64_t num_dimensions;      // Number of dimensions
    uint64_t total_size;          // Total number of elements
} ARR;

// Create a new array with specified dimensions
// dimensions: array of sizes for each dimension
// num_dimensions: number of dimensions
ARR* ARR_Create(const uint64_t* dimensions, uint64_t num_dimensions);

// Destroy array and free all resources
void ARR_Free(ARR* arr);

// Get value at specified indices
// indices: array of indices for each dimension
ARR_DATA_TYPE* ARR_Get(const ARR* arr, const uint64_t* indices);

// Convenient accessors for common dimensionalities. These do *not* allocate memory on the heap
// and therefore are suitable for performance–critical paths.
static inline ARR_DATA_TYPE * ARR_At1(const ARR* arr, uint64_t i) {
    uint64_t idx[1] = { i }; 
    return ARR_Get(arr, idx);
}

static inline ARR_DATA_TYPE * ARR_At2(const ARR* arr, uint64_t i, uint64_t j) {
    uint64_t idx[2] = { i, j };
    return ARR_Get(arr, idx);

}
static inline ARR_DATA_TYPE * ARR_At3(const ARR* arr, uint64_t i, uint64_t j, uint64_t k) {
    uint64_t idx[3] = { i, j, k };
    return ARR_Get(arr, idx);
}

// Set value at specified indices
// indices: array of indices for each dimension
// Returns 1 on success, 0 on failure
int ARR_Set(ARR* arr, const uint64_t* indices, ARR_DATA_TYPE value);

// Get number of dimensions
uint64_t ARR_NumDimensions(const ARR* arr);

// Get size of specific dimension
uint64_t ARR_DimensionSize(const ARR* arr, uint64_t dimension);

// Get total number of elements
uint64_t ARR_TotalSize(const ARR* arr);

// Helper function to calculate linear index from multi-dimensional indices
uint64_t ARR_CalculateIndex(const ARR* arr, const uint64_t* indices);

#endif // ARR_H 