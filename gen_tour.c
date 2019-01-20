#include <stdio.h>
#include <stdlib.h>
#include "tsp_tools.h"


int main(int argc, char *argv[])
{
	int i;
	int n;
	int seed;
	int *tour;

	n = atoi(argv[1]);
	seed = atoi(argv[2]);
	tour = (int *) malloc(n*sizeof(int));

	srand(seed);

	/* generate a random tour. */
	for(i=0;i<n;i++) tour[i] = i;
	shuffle(tour, n);

	write_tour("a.tour", tour, n);

	return 0;
}
