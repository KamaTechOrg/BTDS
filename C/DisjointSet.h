#ifndef DISJOINT_Set_H
#define DISJOINT_Set_H

#include "data_types_config.h"
#include "POD_Utils.h"
#include <stdbool.h>

#ifndef DS_DATA_TYPE
#define DS_DATA_TYPE int
#endif

#define DS_PARSER_FUN CAT(DS_DATA_TYPE, _Parse)
#define DS_FREE_ELEMENT_FUN CAT(DS_DATA_TYPE, _Free)

typedef struct {
    DS_DATA_TYPE* parent;
    int* rank;
    int size;
} DisjointSet;

DisjointSet* disjoint_set_Create(int size);
void disjoint_set_Free(DisjointSet* ds);

int disjoint_set_find(DisjointSet* ds, DS_DATA_TYPE element);
bool disjoint_set_union(DisjointSet* ds, DS_DATA_TYPE x, DS_DATA_TYPE y);

#endif // DISJOINT_Set_H
