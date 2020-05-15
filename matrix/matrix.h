
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../core/core.h"
#include "../vector/vector.h"
#include "../cvector/cvector.h"

typedef void* VALUES;

typedef struct __column__
{
	int namelen;
	string_t name;
	VALUES value;
} column;

typedef column* COLUMN;

typedef struct __matrix__
{
    int ncols;
    COLUMN cols;
} matrix_t;

typedef matrix_t* MATRIX;


MATRIX new_matrix(int n, ...);
void   dis_matrix(MATRIX m);

MATRIX mat_mutate(MATRIX m, unsigned int n, ...);
VALUES mat_select(const MATRIX m, const string_t tag);
void   mat_append(MATRIX m, const string_t col, void* data);
void   mat_concat(MATRIX m, const string_t col, VECTOR data);
void   mat_pnames(const MATRIX m);
void   mat_print_col(const MATRIX m, const string_t col);
void   mat_glimpse(const MATRIX m);
int    mat_col_exist(const MATRIX m, const string_t col);
int    mat_strcol(const MATRIX m, const string_t col);
int    mat_ncols(const MATRIX m);

#endif
