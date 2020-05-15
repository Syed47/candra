
#include "matrix.h"

MATRIX new_matrix(int n, ...)
{
    if (n < 0)
    {
        fprintf(stderr, "\nError: 0 columns cannot be created <%d>.\n", n);
        exit(EXIT_FAILURE);
    }
    MATRIX __m = malloc(sizeof *__m);
    __m->ncols = n;
    __m->cols = malloc(sizeof(column) * __m->ncols);
    __m->cols->namelen = MAX_STR_LEN;

     for (int i = 0; i < __m->ncols; ++i)
     {
        __m->cols[i].name   = malloc(sizeof(char) * __m->cols->namelen);
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
        
        if (__m->cols[i].name[0] == '$')
        {
			__m->cols[i].value = (CVECTOR) new_cvector();
        } else {
			__m->cols[i].value = (VECTOR) new_vector();
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
    return vec;
}

MATRIX mat_mutate(MATRIX m, unsigned int n, ...)
{
    m->ncols += n;
    size_t delta = mat_ncols(m) - n;

    m->cols = realloc(m->cols, sizeof(column) * mat_ncols(m));
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
		m->cols[i].value = new_vector();
    }
    va_end(arg_list);
    
    return m;
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
            printf("\n[%s (%d|str)]\n\n", col + 1, size);
            for (; i < size; ++i)
                printf("-| %s\n", cvec_get(v, i));
        } else if (!is_str_col) {
            printf("\n[%s (%d|num)]\n\n", col, size);
            for (; i < size; ++i)
                printf("-| %d\n", vec_get(v, i));
        }
    } else {
        printf("\n[%s] does not exist.\n", col);
    }
}

void mat_append(MATRIX m, const string_t col, void* data)
{
    // working on this one
}

int mat_col_exist(const MATRIX m, const string_t col)
{
    int i = 0;
    while (i < mat_ncols(m) && strncmp(m->cols[i].name, col, m->cols->namelen) != 0)
        i++;
    // returns the cordinal number (index + 1), not index
    return i == mat_ncols(m) ? 0 : i + 1;
}

int mat_strcol(const MATRIX m, const string_t col)
{
    return mat_col_exist(m, col) && col[0] == '$';
}

void mat_pnames(const MATRIX m)
{
    int i = 0;
    for (; i < mat_ncols(m); i++)
        printf("%s%s", i == 0 ? "" : " | ", m->cols[i].name);
    puts("");
}

int mat_ncols(const MATRIX m)
{
    return m->ncols;
}

void dis_matrix(MATRIX m)
{
    m->ncols = 0;
    m->cols->namelen = 0;
    for (size_t i = 0; i < m->ncols; ++i)
    {
        free(m->cols[i].name);
        free(m->cols[i].value);
    }
    free(m->cols);
    free(m);
    m->cols = NULL;
    m = NULL;
}
