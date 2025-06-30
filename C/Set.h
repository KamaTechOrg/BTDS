#ifndef SET_H
#define SET_H

#include "data_types_config.h"
#include "POD_Utils.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef SET_DATA_TYPE
#define SET_DATA_TYPE int
#endif

#define SET_PARSER_FUN CAT(SET_DATA_TYPE, _Parse)
#define SET_FREE_ELEMENT_FUN CAT(SET_DATA_TYPE, _Free)
#define SET_HASH_FUN CAT(SET_DATA_TYPE, _hash_function)

typedef struct SetNode {
    SET_DATA_TYPE data;
    struct SetNode* next;
} SetNode;

typedef struct {
    SetNode** buckets;
    uint64_t size;
    uint64_t count;
} Set;

// Create a new set with given initial size
Set* Set_Create(uint64_t size);

// Destroy the set and free all memory
void Set_Free(Set* set);

// Add an element to the set. Returns 0 on success, -1 on failure
int Set_Add(Set* set, SET_DATA_TYPE data);

// Remove an element from the set. Returns 0 on success, -1 if element not found
int Set_Remove(Set* set, SET_DATA_TYPE data);

// Check if an element exists in the set
bool Set_Contains(Set* set, SET_DATA_TYPE data);

// Get current number of elements in the set
uint64_t Set_Count(Set* set);

#endif // SET_H 