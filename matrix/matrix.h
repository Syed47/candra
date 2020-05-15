
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../vector/vector.h"
#include "../cvector/cvector.h"

typedef char* NAMES;
typedef void* VALUES;

typedef struct __matrix__
{
    int ncols;
    int max_name_len;
    NAMES* names;
    VALUES* values;
} matrix_t;

typedef matrix_t* MATRIX;


MATRIX new_matrix(int n, ...);
void   dis_matrix(MATRIX m);

MATRIX mat_mutate(MATRIX m, unsigned int n, ...);
VALUES mat_select(const MATRIX m, const STRING tag);
void   mat_append(MATRIX m, const STRING col, void* data);
void   mat_concat(MATRIX m, const STRING col, VECTOR data);
void   mat_cols(const MATRIX m);
void   mat_print_col(const MATRIX m, const STRING col);
void   mat_glimpse(const MATRIX m);
int    mat_col_exist(const MATRIX m, const STRING col);
int    mat_strcol(const MATRIX m, const STRING col);

size_t numlen(size_t n);
size_t max(size_t a, size_t b);
size_t min(size_t a, size_t b);

#endif
