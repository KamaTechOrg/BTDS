#ifndef HEAP_H
#define HEAP_H

#include "data_types_config.h"
#include "POD_Utils.h"

#include <stdbool.h>

#ifndef Heap_DATA_TYPE
#define Heap_DATA_TYPE int
#endif

typedef struct {
    Heap_DATA_TYPE* data;
    int size;
    int capacity;
} Heap;

Heap* Heap_Create(int capacity);
void Heap_Free(Heap* h);

bool Heap_insert(Heap* h, Heap_DATA_TYPE value);
bool Heap_extract_min(Heap* h, Heap_DATA_TYPE* value);
bool Heap_peek_min(Heap* h, Heap_DATA_TYPE* value);

#endif // HEAP_H
