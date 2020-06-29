#include "cvector.h"

CVECTOR new_cvector()
{
    CVECTOR __v = malloc(sizeof *__v);

    __v->size = 32;
    __v->i = 0;
    __v->vec = malloc(__v->size * sizeof(string_t));

    for (int i = 0; i < __v->size; ++i)
    {
        __v->vec[i] = malloc(sizeof(char) * (MAX_STR_LEN + 1));
    }

    return __v;
}

size_t cvec_size(const CVECTOR v)
{
    return v->i;
}

string_t cvec_get(const CVECTOR v, int i)
{
    if (v != NULL && !(i > -1 || i < v->i))
    {
        LOG_ERROR("Invalid memory access not allowed <%d>.\n", i);
        return NULL;
    }

    return v->vec[i];
}

int cvec_push(CVECTOR v, const string_t val)
{
    strncpy(v->vec[v->i], val, MAX_STR_LEN);
    v->vec[v->i][MAX_STR_LEN] = '\0';
    v->i++;

    if (v->i == v->size)
    {
        v->size += 0.5 * (double)v->size;
        size_t new_size = v->size * sizeof(string_t);

        return ((v->vec = realloc(v->vec, new_size)) == NULL) ? 0 : 1;
    }

    return 1;
}

void cvec_replace(CVECTOR v, size_t index, string_t val)
{
    EXIT_ERROR(index < 0 || index >= cvec_size(v), "cannot replace out-of-bound value");
    strncpy(v->vec[index], val, MAX_STR_LEN);
}

int cvec_is_empty(const CVECTOR v)
{
    return v->i == 0;
}

int cvec_indexof(const CVECTOR v, const string_t val)
{
    int i = -1;
    while (++i < cvec_size(v) && strncmp(cvec_get(v, i), val, MAX_STR_LEN) != 0);
    return i == cvec_size(v) ? -1 : i;
}

void dis_cvector(CVECTOR v)
{
    for (int i = 0; i < v->i; i++)
    {
        free(v->vec[i]);
    }
    free(v->vec);
    free(v);
    v->i = 0;
    v->size = 0;
    v->vec = NULL;
    v = NULL;
}
