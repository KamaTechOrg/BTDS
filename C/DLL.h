#ifndef DLL_H
#define DLL_H

#include <stdbool.h>
#include "POD_Utils.h"

#include <stdlib.h>
#include <stdbool.h>

#ifndef DLL_DATA_TYPE
#define DLL_DATA_TYPE int
#endif

#define DLL_PARSE_FUN CAT(DLL_DATA_TYPE, _Parse)
#define DLL_FREE_ELEMENT_FUN CAT(DLL_DATA_TYPE, _Free)
#define DLL_ELEM_CMP CAT(DLL_DATA_TYPE, _CMP)


typedef struct DLLNode {
    DLL_DATA_TYPE data;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

typedef struct {
    DLLNode* head;
    DLLNode* tail;
    uint64_t size;
} DLL;

// Create a new empty doubly linked list
DLL* DLL_Create(void);

// Destroy the doubly linked list and free all memory
void DLL_Free(DLL* list);

// Insert a value at the beginning of the list
// Returns 0 on success, -1 on failure
int DLL_InsertFront(DLL* list, DLL_DATA_TYPE data);

// Insert a value at the end of the list
// Returns 0 on success, -1 on failure
int DLL_InsertBack(DLL* list, DLL_DATA_TYPE data);

// Remove the first occurrence of a value from the list
// Returns 0 on success, -1 if value not found
int DLL_Remove(DLL* list, DLL_DATA_TYPE data);

// Get value at specified index (0-based)
// Returns true if index exists and value is set, false otherwise
bool DLL_GetAt(DLL* list, uint64_t index, DLL_DATA_TYPE* value);

// Set value at specified index (0-based)
// Returns 0 on success, -1 if index out of bounds
int DLL_SetAt(DLL* list, uint64_t index, DLL_DATA_TYPE value);

// Check if a value exists in the list
bool DLL_Contains(DLL* list, DLL_DATA_TYPE data);

// Get the number of elements in the list
uint64_t DLL_Size(DLL const * list);

// Get the first element in the list
// Returns true if list is not empty and value is set, false otherwise
bool DLL_GetFirst(DLL* list, DLL_DATA_TYPE* value);

// Get the last element in the list
// Returns true if list is not empty and value is set, false otherwise
bool DLL_GetLast(DLL* list, DLL_DATA_TYPE* value);

#endif // DLL_H 