#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp_tools.h"

int tsp_nn(int *min_tour, int init, int **dist, int n)
{
	int i,j,k;
	int min_len;
	int *used;
	int d;
	int min_d;
	int max_d;
	int min_c;

	/* array of used cities */
	used = (int *) malloc(n*sizeof(int));
	for(i=0;i<n;i++) used[i] = 0;

	/* find the maximum length of city pairs */
	max_d = 0;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(dist[i][j] > max_d)
			{
				max_d = dist[i][j];
			}
		}
	}

	min_tour[0] = init;
	used[init] = 1;

	for(i=0;i<n-1;i++)
	{
		j = min_tour[i];
		min_d = max_d+1;
		for(k=0;k<n;k++)
		{
			d = dist[j][k];
			if(used[k]==0 && d < min_d) /* if city k is not used and d_jk < the minimum distance */
			{
				min_d = d;
				min_c = k;
			}
		}
		min_tour[i+1] = min_c; /* the next city is min_c */
		used[min_c] = 1; /* min_c is used */
	}

	min_len = tour_length(min_tour, dist, n);

	free(used);

	return min_len;
}

int main(int argc, char *argv[])
{
	int i;

	char *fn;

	int n;
	float **points;
	int **dist;

	int min_len;
	int *min_tour;

	int init;

	clock_t begin, end;
	double time_spent;


	fn = argv[1]; /* tsp instance */
	init = atoi(argv[2])-1; /* initial point for the nearest neighbor */
	printf("init %d\n", init);

	n = read_tsp(&points, fn); /* (points[i][0], points[i][1]): the coordinate of point i. */
	/* for(i=0;i<n;i++) printf("%d %f %f\n", i+1, points[i][0], points[i][1]); */

	distance_matrix(&dist, points, n); /* dist[i][j]: the distance of i and j.*/

	min_tour = (int *) malloc(n*sizeof(int));
	begin = clock();
	min_len = tsp_nn(min_tour, init, dist, n);
	end = clock();
	time_spent = (double)(end - begin) / (double)CLOCKS_PER_SEC;

	printf("%d [", min_len);
	for(i=0;i<n;i++) printf("%d ", min_tour[i]+1);
	printf("]\n");
	printf("CPU time (s): %f\n", time_spent);

	write_tour("a.tour", min_tour, n);


	return 0;
}
