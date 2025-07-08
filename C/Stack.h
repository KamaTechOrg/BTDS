#ifndef STACK_H
#define STACK_H

#include "data_types_config.h"
#include <stdbool.h>
#include "POD_Utils.h"

#ifndef Stack_DATA_TYPE
#define Stack_DATA_TYPE int
#endif

typedef struct {
    Stack_DATA_TYPE* data;
    int top;
    int capacity;
} Stack;

Stack* Stack_Create(int capacity);  // Returns NULL on failure:
int Stack_GetCapacity(Stack* s);   // Return -1 if S is NULL
int Stack_GetSize(Stack* s);       // Return -1 if S is NULL
bool Stack_IsEmpty(Stack* s);      // Return false if S is NULL
bool Stack_IsFull(Stack* s);       // Return false if S is NULL
bool Stack_Push(Stack* stack, Stack_DATA_TYPE value); // Return false on any failure:
bool Stack_Pop(Stack* stack, Stack_DATA_TYPE* value); // Return false on any failure:
bool Stack_Peek(Stack* stack, Stack_DATA_TYPE* value); // Return false on any failure:
void Stack_Free(Stack* s);

#endif // STACK_H
