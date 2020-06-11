#include "./core/core.h"
#include "./vector/vector.h"
#include "./cvector/cvector.h"
#include "./matrix/matrix.h"

int main(int argc, char const *argv[])
{
    MATRIX planes = MATRIX_INIT(5, "id", "$make", "$model", "engines", "fleet");
	mat_mutate(planes, 2, "$livery", "tyres");

	mat_append(planes, mat_ncols(planes), 1, "Airbus", "A380-800", 4, 17, "Expo 2020", 12);
	mat_append(planes, mat_ncols(planes), 2, "Airbus", "A350-1000", 2, 10, "SPACE NEXT", 8);
	mat_append(planes, mat_ncols(planes)-5, 3, "Boeing", "737-800", 2, 92, "classis", 5);
	mat_append(planes, mat_ncols(planes), 4, "Bombardier", "luxer", 2, 7, "Luxery", 3);
	mat_append(planes, mat_ncols(planes) - 2, 5, "Boeing", "777-300ER", 2, 54, "Cricket WC", 10);


	mat_print_col(planes, "id");
	mat_print_col(planes, "$make");
	mat_print_col(planes, "$model");
	mat_print_col(planes, "engines");
	mat_print_col(planes, "fleet");
	mat_print_col(planes, "$livery");
	mat_print_col(planes, "tyres");

	DIS_MATRIX(planes);

	return 0;
}
