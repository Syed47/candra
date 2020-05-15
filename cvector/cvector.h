
#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define MAX_STR_LEN 32

typedef char* STRING;

typedef struct __cvector__
{
    STRING* vec;
    size_t size;
    size_t i;
} cvector_t;

typedef cvector_t* CVECTOR;

CVECTOR new_cvector(void);
void dis_cvector(CVECTOR v);

size_t cvec_size(const CVECTOR v);
int cvec_is_empty(const CVECTOR v);
int cvec_add(CVECTOR v, const STRING val);
STRING cvec_get(const CVECTOR v, int i);

#endif
