
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "../core/core.h"
#include "../vector/vector.h"
#include "../cvector/cvector.h"

// UTIL MACROS
#define DIS_MATRIX(T)             \
	printf("\nMATRIX <" #T "> distroyed.\n"); \
	dis_matrix(T);

#define SCHEMA_NUMBER "number"
#define SCHEMA_STRING "string"
#define NA "NA"
#define NaN INT_MIN

typedef void* VALUES; // VECTOR, CVECTOR

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
    string_t* schema;
    COLUMN cols;
} matrix_t;

typedef matrix_t* MATRIX;

string_t* schema;


// DONE
MATRIX MATRIX_INIT(int n, ...);
void   dis_matrix(MATRIX m);

MATRIX    mat_mutate(MATRIX m, unsigned int n, ...);
VALUES    mat_select(const MATRIX m, const string_t tag);
void      mat_pnames(const MATRIX m);
void      mat_glimpse(const MATRIX m);
int       mat_col_exist(const MATRIX m, const string_t col);
int       mat_strcol(const MATRIX m, const string_t col);
int       mat_ncols(const MATRIX m);
void      mat_print_col(const MATRIX m, const string_t col);
void      mat_pschema(const MATRIX m);
string_t* mat_schema(const MATRIX m);

// IN PROCESS
MATRIX mat_append(MATRIX m, int n,  ...);

// NOT DONE
void mat_concat(MATRIX m, const string_t col, VECTOR data);
void join(const MATRIX m1, const MATRIX m2);


#endif


