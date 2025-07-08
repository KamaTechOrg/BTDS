#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data_types_config.h"
#include "POD_Utils.h"

#include <stdlib.h>
#include <stdbool.h>

#define HT_SIZE (16)

#ifndef HT_KEY_DATA_TYPE
#define HT_KEY_DATA_TYPE int
#endif

#ifndef HT_VALUE_DATA_TYPE
#define HT_VALUE_DATA_TYPE int
#endif


typedef struct HTEntry {
    HT_KEY_DATA_TYPE key;
    HT_VALUE_DATA_TYPE value;
    struct HTEntry* next;
} HTEntry;

typedef uint64_t(*HashFunction)(HT_KEY_DATA_TYPE key, uint64_t size);

typedef struct {
    HTEntry** buckets;
    uint64_t size;
    HashFunction hashFunction;
} HT;

// Opaque iterator type for values
typedef struct HT_Values_It_Impl* HT_Values_It;

HT* HT_Create(uint64_t size, HashFunction hashFunction);
void HT_Free(HT* table);
int HT_Insert(HT* table, HT_KEY_DATA_TYPE key, HT_VALUE_DATA_TYPE value);
int HT_Remove(HT* table, HT_KEY_DATA_TYPE key);

// Iterator functions
HT_Values_It HT_Search(HT* table, HT_KEY_DATA_TYPE key);
int HT_Iterator_Next(HT_Values_It it, HT_VALUE_DATA_TYPE* out_value);
void HT_Iterator_Free(HT_Values_It it);

#endif // HASHTABLE_H
