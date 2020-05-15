
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

typedef int vec_t;
typedef enum { FALSE, TRUE } bool;

typedef struct __vector__
{
	vec_t* vec;
	size_t size;
	size_t i;
} vector_t;

typedef vector_t* VECTOR;

VECTOR new_vector(void);
void dis_vector(VECTOR v);

size_t vec_size(const VECTOR v);
bool   vec_is_empty(const VECTOR v);
bool   vec_add(VECTOR v, vec_t val);
vec_t  vec_get(const VECTOR v, int i);

#endif
