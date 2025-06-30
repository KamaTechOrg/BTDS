#ifndef STR_H
#define STR_H

#include "data_types_config.h"
#include <stddef.h>

typedef struct {
    uint64_t n;  /* length of the string */
    char* s;   /* pointer to string data */
} STR;

STR STR_Create(uint64_t len);
void STR_Free(STR s);
STR STR_Copy(STR s);
STR STR_Copy_raw(const char * s);

int STR_CMP(STR s1, STR s2);

#endif /* STR_H */ 