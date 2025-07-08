#ifndef STR_H
#define STR_H

#include "data_types_config.h"
#include <stddef.h>

typedef char* STR;

STR STR_Create(uint64_t len);
void STR_Free(STR s);
STR STR_Copy(const char * s);

int STR_CMP(STR s1, STR s2);

#endif /* STR_H */ 