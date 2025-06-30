#ifndef VECTOR_H
#define VECTOR_H

#include "data_types_config.h"
#include <stdlib.h>
#include <stdbool.h>
#include "POD_Utils.h"

#ifndef Vec_DATA_TYPE
#define Vec_DATA_TYPE int
#endif

#define Vec_PARSE_FUN CAT(Vec_DATA_TYPE, _Parse)
#define Vec_FREE_ELEMENT_FUN CAT(Vec_DATA_TYPE, _Free)

typedef struct {
    Vec_DATA_TYPE* data;
    uint64_t size;
    uint64_t capacity;
} Vec;

Vec* Vec_Create(uint64_t initialCapacity);
void Vec_Free(Vec* vec);
int Vec_Insert(Vec* vec, Vec_DATA_TYPE val);
Vec_DATA_TYPE Vec_At(Vec* vec, uint64_t idx);
uint64_t Vec_Size(Vec* vec);
uint64_t Vec_Capacity(Vec* vec);

#endif // VECTOR_H
