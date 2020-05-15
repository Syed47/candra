#include "./core/core.h"
#include "./vector/vector.h"
#include "./cvector/cvector.h"
#include "./matrix/matrix.h"

int main(int argc, char const *argv[])
{
    MATRIX planes = new_matrix(4, "id", "$make", "$model", "engines", "fleet");
	mat_pnames(planes);
	mat_mutate(planes, 2, "$livery", "tyres");
	mat_pnames(planes);

	printf("TYPE: %s\n", typename("hamza"));
    dis_matrix(planes);

    return 0;
}
