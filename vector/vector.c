#include "vector.h"

VECTOR new_vector()
{
	vector_t* __v = malloc(sizeof *__v);

	__v->size = 32; // 8 * 32 = 256 bytes
	__v->i = 0;
	__v->vec = malloc(__v->size * sizeof(vec_t));

	return __v;
}

size_t vec_size(const VECTOR v)
{
	return v->i;
}

vec_t vec_get(const VECTOR v, int i)
{
	if (v != NULL && !(i > -1 && i < v->i))
	{
		fprintf(stderr, "\nError: Invalid memory access not allowed <%d>.\n", i);
		return INT32_MIN;
	}

	return *((*v).vec + i);
}

bool vec_push(VECTOR v, vec_t val)
{
	*((*v).vec + (*v).i) = val;
	v->i++;
	
	if (v->i == v->size)
	{
		v->size += 0.5 * (double)v->size;
		size_t new_size = v->size * sizeof(vec_t);

		return ((v->vec = realloc(v->vec, new_size)) == NULL) ? false : true;
	}
	
	return true;
}

bool vec_is_empty(const VECTOR v)
{
	return (*v).i == 0;
}

int vec_indexof(const VECTOR v, vec_t val)
{
	int i = -1;
	while (++i < vec_size(v) && vec_get(v, i) != val);
	return i == vec_size(v) ? -1 : i;
}

void dis_vector(VECTOR v)
{
	free((*v).vec);
	free(v);
	(*v).i = 0;
	(*v).size = 0;
	(*v).vec = NULL;
	v = NULL;
}
