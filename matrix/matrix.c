
#include "matrix.h"

MATRIX MATRIX_INIT(int n, ...)
{
    EXIT_ERROR(n < 1, "<%d> columns cannot be created", n);

    MATRIX __m         = malloc(sizeof *__m);
    __m->ncols         = n;
    __m->schema        = (SCHEMA) malloc(sizeof(char*) * n);
    __m->cols          = malloc(sizeof(column) * __m->ncols);
    __m->cols->namelen = MAX_STR_LEN;

    for (int i = 0; i < __m->ncols; ++i)
    {
        __m->cols[i].name = malloc(sizeof(char) * __m->cols->namelen);
        __m->cols[i].value = malloc(sizeof(VALUES));
    }

    va_list arg_list;
    va_start(arg_list, n);
    size_t i = 0;
    for (; i < __m->ncols; i++)
    {
        const char* tmp_name = va_arg(arg_list, char *);
        __m->cols[i].name = malloc(sizeof(char) * (__m->cols->namelen + 1));
        strncpy(__m->cols[i].name, tmp_name, __m->cols->namelen);
        __m->cols[i].name[__m->cols->namelen] = '\0';
        __m->schema[i] = malloc(sizeof(char) * MAX_STR_LEN);

        if (__m->cols[i].name[0] == '$')
        {
			__m->cols[i].value = (CVECTOR) new_cvector();
            strncpy(__m->schema[i], SCHEMA_STRING, MAX_STR_LEN);
        } else {
			__m->cols[i].value = (VECTOR) new_vector();
            strncpy(__m->schema[i], SCHEMA_NUMBER, MAX_STR_LEN);
        }
    }
    va_end(arg_list);

    return __m;
}

VALUES mat_select(const MATRIX m, const string_t col_name)
{
    VALUES vec = NULL;
    int i = -1;
    while (++i < mat_ncols(m))
    {
        if (strncmp(m->cols[i].name, col_name, m->cols->namelen) == 0)
            vec = m->cols[i].value;
    }
    if (vec == NULL) 
        LOG_ERROR("%s doesn\'t exists in the matrix", col_name);
    
    return vec;
}

MATRIX mat_mutate(MATRIX m, unsigned int n, ...)
{
    m->ncols += n;
    size_t delta = mat_ncols(m) - n;

    m->cols = realloc(m->cols, sizeof(column) * mat_ncols(m));
    m->schema = realloc(m->schema, sizeof(char*) * mat_ncols(m));

    if (m->cols == NULL || m->schema == NULL) 
    {
        LOG_ERROR("memory allocation error");
    }


    for (size_t i = delta; i < n; i++)
    {
		m->cols[i].name = malloc(sizeof(char) * m->cols->namelen);
		m->cols[i].value = malloc(sizeof(VALUES));
    }

    va_list arg_list;
    va_start(arg_list, n);

    for (size_t i = delta; i < mat_ncols(m); ++i)
    {
        const char* tmp_name = va_arg(arg_list, char*);
        m->cols[i].name = malloc(sizeof(char) * (m->cols->namelen + 1));
		strncpy(m->cols[i].name, tmp_name, m->cols->namelen);
        m->cols[i].name[m->cols->namelen] = '\0';
        m->schema[i] = malloc(sizeof(char) * MAX_STR_LEN);

        if (m->cols[i].name[0] == '$')
        {
            m->cols[i].value = (CVECTOR) new_cvector();
            strncpy(m->schema[i], SCHEMA_STRING, MAX_STR_LEN);
        } else {
            m->cols[i].value = (VECTOR) new_vector();
            strncpy(m->schema[i], SCHEMA_NUMBER, MAX_STR_LEN);
        }
    }
    va_end(arg_list);
    
    return m;
}

MATRIX mat_append(MATRIX m, int n,  ...)
{
    va_list arg_list;
    va_start(arg_list, n);
    SCHEMA schema = mat_schema(m);
    int i = -1;
    while (++i < n)
    {
        if (STR_EQUALS(schema[i], SCHEMA_NUMBER))
        {
            int x = va_arg(arg_list, int);
            vec_push(m->cols[i].value, x);
        } 
        else if (STR_EQUALS(schema[i], SCHEMA_STRING))
        {
            char* x = va_arg(arg_list, string_t);
            cvec_push(m->cols[i].value, x);
        } 
        else 
        {
            LOG_ERROR("Unknown type found. The value is voided");
        }
    }

    for (; i < mat_ncols(m); ++i)
    {
        if (mat_strcol(m, m->cols[i].name))
            cvec_push(m->cols[i].value, NA);
        else
            vec_push(m->cols[i].value, NaN);
    }
    return m;
}

int mat_col_exist(const MATRIX m, const string_t col)
{
    int i = 0;
    while (i < mat_ncols(m) && strncmp(m->cols[i].name, col, m->cols->namelen) != 0)
        i++;
    // returns the cardinal number (index + 1), not index
    return i == mat_ncols(m) ? 0 : i + 1;
}

int mat_strcol(const MATRIX m, const string_t col)
{
    return mat_col_exist(m, col) && col[0] == '$';
}

SCHEMA mat_schema(const MATRIX m)
{
    return m->schema;
}

int mat_ncols(const MATRIX m)
{
    return m->ncols;
}

void mat_print_col(const MATRIX m, const string_t col)
{
    VALUES v = mat_select(m, col);
    if (v != NULL)
    {
        int is_str_col = mat_strcol(m, col),
            size = (int)vec_size(v),
            i = 0;

        if (is_str_col)
        {
            printf("\n*[%s (%d|str)]\n", col + 1, size);
            puts("-+---------------");
            for (; i < size; ++i)
                printf("%d| %s\n", i + 1, cvec_get(v, i));
        }
        else
        {
            printf("\n*[%s (%d|num)]\n", col, size);
            puts("-+---------------");
            for (; i < size; ++i)
                printf("%d| %d\n", i + 1, vec_get(v, i));
        }
    }
    else
    {
        fprintf(stderr,"\nError: [%s] does not exist.\n", col);
    }
}

void mat_glimpse(const MATRIX m)
{
    puts("-----------------------------------------------------------");
    for (int i = 0; i < mat_ncols(m); ++i)
    {
        printf("[%s] | ", m->cols[i].name);
        if (mat_strcol(m, m->cols[i].name)) 
        {
            for (int j = 0; j < cvec_size(m->cols[i].value); ++j)
                printf("%s, ", cvec_get(m->cols[i].value, j));
        } else {
            for (int j = 0; j < vec_size(m->cols[i].value); ++j)
                printf("%d ", vec_get(m->cols[i].value, j));
        }
        puts("");
    }
    puts("-----------------------------------------------------------\n");
}

void mat_pnames(const MATRIX m)
{
    int i = 0;
    for (; i < mat_ncols(m); i++)
        printf("%s%s", i == 0 ? "" : " | ", m->cols[i].name);
    puts("");
}

void mat_pschema(const MATRIX m)
{
    int i = -1;
    while(++i < mat_ncols(m))
    {
        printf("%s%s", i == 0 ? "" : " | ", m->schema[i]);
    }
    puts("");
}

void dis_matrix(MATRIX m)
{
    m->ncols = 0;
    m->cols->namelen = 0;
    for (size_t i = 0; i < m->ncols; ++i)
    {
        free(m->cols[i].name);
        free(m->cols[i].value);
        free(m->schema[i]);
    }
    free(m->cols);
    free(m->schema);
    free(m);
    m->cols = NULL;
    m->schema = NULL;
    m = NULL;
}