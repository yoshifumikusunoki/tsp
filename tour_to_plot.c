#include <stdio.h>
#include "tsp_tools.h"

int main(int argc, char *argv[])
{
	int n;
	char *fn_points;
	char *fn_tour;
	float **points;
	int *tour;

	fn_points = argv[1];
	fn_tour = argv[2];

	n = read_tsp(&points, fn_points);

	read_tour(&tour, n, fn_tour);

	write_plot("a.plt", points, tour, n);

	return 0;
}
