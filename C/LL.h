#ifndef LL_H
#define LL_H

#include "data_types_config.h"
#include <stdlib.h>
#include <stdbool.h>
#include "POD_Utils.h"

#ifndef LL_DATA_TYPE
#define LL_DATA_TYPE int
#endif

#define LL_PARSE_FUN CAT(LL_DATA_TYPE, _Parse)
#define LL_FREE_ELEMENT_FUN CAT(LL_DATA_TYPE, _Free)
#define LL_ELEM_CMP CAT(LL_DATA_TYPE, _CMP)


typedef struct LLNode {
    LL_DATA_TYPE data;
    struct LLNode* next;
} LLNode;

typedef struct {
    LLNode* head;
    uint64_t size;
} LL;

// Create a new empty linked list
LL* LL_Create(void);

// Destroy the linked list and free all memory
void LL_Free(LL* list);

// Insert a value at the beginning of the list
// Returns 0 on success, -1 on failure
int LL_InsertFront(LL* list, LL_DATA_TYPE data);

// Insert a value at the end of the list
// Returns 0 on success, -1 on failure
int LL_InsertBack(LL* list, LL_DATA_TYPE data);

// Remove the first occurrence of a value from the list
// Returns 0 on success, -1 if value not found
int LL_Remove(LL* list, LL_DATA_TYPE data);

// Get value at specified index (0-based)
// Returns true if index exists and value is set, false otherwise
bool LL_GetAt(LL* list, uint64_t index, LL_DATA_TYPE* value);

// Set value at specified index (0-based)
// Returns 0 on success, -1 if index out of bounds
int LL_SetAt(LL* list, uint64_t index, LL_DATA_TYPE value);

// Check if a value exists in the list
bool LL_Contains(LL* list, LL_DATA_TYPE data);

// Get the number of elements in the list
uint64_t LL_Size(LL const * list);

#endif // LL_H 