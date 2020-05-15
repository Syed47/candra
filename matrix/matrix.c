
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
    __m->names = malloc(sizeof(char *) * __m->ncols);
    __m->values = malloc(sizeof(VECTOR) * __m->ncols);
    __m->max_name_len = MAX_STR_LEN;

    va_list arg_list;
    va_start(arg_list, n);
    size_t i = 0;
    for (; i < __m->ncols; i++)
    {
        const char* tmp_name = va_arg(arg_list, char *);
        __m->names[i] = malloc(sizeof(char) * (__m->max_name_len + 1));
        strncpy(__m->names[i], tmp_name, __m->max_name_len);
        __m->names[i][__m->max_name_len] = '\0';
        
        if (__m->names[i][0] == '$')
        {
            __m->values[i] = (CVECTOR) new_cvector();
        } else {
            __m->values[i] = (VECTOR) new_vector();
        }
    }
    va_end(arg_list);

    return __m;
}

VALUES mat_select(const MATRIX m, const STRING tag)
{
    VALUES vec = NULL;
    int i = 0;
    while (i < m->ncols)
    {

        if (strncmp(m->names[i], tag, m->max_name_len) == 0)
            vec = m->values[i];
        i++;
    }
    return vec;
}

MATRIX mat_mutate(MATRIX m, unsigned int n, ...)
{
    m->ncols += n;
    m->names = realloc(m->names, sizeof(NAMES) * m->ncols);
    m->values = realloc(m->values, sizeof(VALUES) * m->ncols);

    va_list arg_list;
    va_start(arg_list, n);
    size_t i = m->ncols - n;

    for (; i < m->ncols; ++i)
    {
        const char* tmp_name = va_arg(arg_list, char*);
        m->names[i] = malloc(sizeof(char) * (m->max_name_len + 1));
        strncpy(m->names[i], tmp_name, m->max_name_len);
        m->names[i][m->max_name_len] = '\0';
        m->values[i] = new_vector();
    }
    va_end(arg_list);
    
    return m;
}

void mat_print_col(const MATRIX m, const STRING col)
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

void mat_append(MATRIX m, const STRING col, void* data)
{

}

// working on this function
void mat_glimpse(const MATRIX m)
{
    if (m == NULL) exit(EXIT_FAILURE);

    int is_str_col = 0,
        col_size = (int)vec_size(m->values[0]),
        cols = m->ncols;

    size_t delta = 0;
    
    mat_cols(m);

    for (int i = 0; i < col_size; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            STRING name = m->names[j];
            VECTOR values = mat_select(m, name);
            is_str_col = mat_strcol(m, name);

            if (is_str_col)
            {
                STRING s = cvec_get((CVECTOR)values, i);
                delta = strlen(name) - strlen(s);
                if (delta < 0)
                {
                    for (int i = 0; i < strlen(s) + delta; i++)
                        printf("%c", s[i]);
                    printf("%s", "|");
                } else {
                    printf("%s%s", "|", s);
                }
            }
            else
            {
                int x = vec_get(values, i);
                printf("%s%d", "|", x);
                delta = strlen(name) - numlen(x);
            }
            // printf("\nDELTA %zu\n", delta);

            for (int k = 0; k < delta && j + 1 != cols; ++k)
                printf("%s", " ");
        }
        puts("");
    }
    // printf("\nlen %zu\n", numlen(999));
}

int mat_col_exist(const MATRIX m, const STRING col)
{
    int i = 0;
    while (i < m->ncols && strncmp(m->names[i], col, m->max_name_len) != 0)
        i++;
    // returns the cordinal number (index + 1), not index
    return i == m->ncols ? 0 : i + 1;
}

int mat_strcol(const MATRIX m, const STRING col)
{
    return mat_col_exist(m, col) && col[0] == '$';
}

void mat_cols(const MATRIX m)
{
    int i = 0;
    for (; i < m->ncols; i++)
        printf("%s%s", i == 0 ? "" : " | ", m->names[i]);
    puts("");
}

size_t numlen(size_t num)
{
    size_t n = 0;
    do
    {
        ++n;
        num /= 10;
    } while (num);
    return n;
}

size_t max(size_t a, size_t b)
{
    return a > b ? a : b;
}

size_t min(size_t a, size_t b)
{
    return a < b ? a : b;
}

void dis_matrix(MATRIX m)
{
    m->ncols = 0;
    m->max_name_len = 0;
    for (size_t i = 0; i < m->ncols; ++i)
    {
        free(m->names[i]);
        free(m->values[i]);
    }
    free(m->names);
    free(m->values);
    free(m);
    m->names = NULL;
    m->values = NULL;
    m = NULL;
}
