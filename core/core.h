
#ifndef core_h
#define core_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STR_LEN 32

#define typename(x) _Generic((x),                     \
	_Bool: "_Bool",                                   \
	unsigned char: "unsigned char",                   \
	char: "char",                                     \
	signed char: "signed char",                       \
    short int: "short int",                           \
	unsigned short int: "unsigned short int",         \
	int: "int",                                       \
	unsigned int: "unsigned int",                     \
	long int: "long int",                             \
	unsigned long int: "unsigned long int",           \
	long long int: "long long int",                   \
	unsigned long long int: "unsigned long long int", \
	float: "float",                                   \
	double: "double",                                 \
	long double: "long double",                       \
	char *: "pointer to char",                        \
	void *: "pointer to void",                        \
	int *: "pointer to int",                          \
	default: "other")

#define TYPECMP(a, b) \
	strncmp(typename(a), typename(b), MAX_STR_LEN) == 0

#define STR_EQUALS(a, b) \
	strncmp(a, b, MAX_STR_LEN) == 0

typedef char* string_t;


#endif
