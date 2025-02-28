
#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "../core/core.h"

typedef struct __cvector__
{
    string_t* vec;
    size_t size;
    size_t i;
} cvector_t;

typedef cvector_t* CVECTOR;

CVECTOR  new_cvector(void);
void     dis_cvector(CVECTOR v);

size_t   cvec_size(const CVECTOR v);
int      cvec_is_empty(const CVECTOR v);
int      cvec_push(CVECTOR v, const string_t val); 
string_t cvec_get(const CVECTOR v, int i);
int      cvec_indexof(const CVECTOR v, const string_t val);
void     cvec_replace(CVECTOR v, size_t index, string_t val);

#endif
