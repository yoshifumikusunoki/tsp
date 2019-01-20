#include <stdio.h>
#include <stdlib.h>
#include "tsp_tools.h"

int main(int argc, char *argv[])
{
	int i,j,k,l;
	int n;
	int seed;
	int L = 1000;
	float **points;
	int *index;
	int m = L*L;

	n = atoi(argv[1]); /* the number of cities */
	seed = atoi(argv[2]); /* the seed of random */

	srand(seed);

	index = (int *) malloc(m*sizeof(int));
	for(i=0;i<m;i++) index[i] = i;
	shuffle(index,m);

	points = (float **) malloc(n*sizeof(float *));
	for(i=0;i<n;i++)
	{
		points[i] = (float *) malloc(2*sizeof(float));
		j = index[i];
		k = j/L;
		l = j%L;
		points[i][0] = k;
		points[i][1] = l;
	}

	write_tsp("a.tsp", points, n);

	return 0;
}
