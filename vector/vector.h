
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>

#include "../core/core.h"

typedef int vec_t;

typedef struct __vector__
{
	vec_t* vec;
	size_t size;
	size_t i;
} vector_t;

typedef vector_t* VECTOR;

VECTOR new_vector(void);
void   dis_vector(VECTOR v);

size_t vec_size(const VECTOR v);
bool   vec_is_empty(const VECTOR v);
bool   vec_push(VECTOR v, vec_t val);
vec_t  vec_get(const VECTOR v, int i);
int    vec_indexof(const VECTOR v, vec_t val);
void   vec_replace(VECTOR v, size_t index, vec_t val);

#endif
