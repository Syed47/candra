#include "./vector/vector.h"
#include "./cvector/cvector.h"
#include "./matrix/matrix.h"

int main(int argc, char const *argv[])
{
    MATRIX planes = new_matrix(6, "id", "$make", "$model", "engines", "fleet", "operational");
	mat_cols(planes);
    dis_matrix(planes);

    return 0;
}
