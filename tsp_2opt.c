#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp_tools.h"

int diff_len(int i1, int i2, int i3, int i4, int *tour, int **dist)
{
	int s1, s2, s3, s4;
	s1 = tour[i1];
	s2 = tour[i2];
	s3 = tour[i3];
	s4 = tour[i4];
	return dist[s1][s3] + dist[s2][s4] - dist[s1][s2] - dist[s3][s4];
}

int tsp_2opt(int *min_tour, int *init, int **dist, int n)
{
	int h,i,j;
	int i1,i2,i3,i4;
	int min_len;

	int *sub_tour1, *sub_tour2;
	int n1, n2;

	int diff, min_diff;
	int min_neighbor[4];

	int *tour;

	tour = (int *) malloc(n*sizeof(int));

	for(i=0;i<n;i++) min_tour[i] = init[i];
	min_len = tour_length(min_tour, dist, n);

	for(i=0;i<n;i++) tour[i] = min_tour[i];

	sub_tour1 = (int *) malloc(n*sizeof(int));
	sub_tour2 = (int *) malloc(n*sizeof(int));

	h = 0;
	while(1)
	{
	    min_diff = 0;
	    min_neighbor[0] = 0;
	    min_neighbor[1] = 1;
	    min_neighbor[2] = 1;
	    min_neighbor[3] = 2;

	    for(i=0;i<n;i++)
	    {
	    	i1 = i;
	    	i2 = (i1+1)%n;
	    	for(j=0;j<n-1;j++)
	    	{
	    		i3 = (i2+j)%n;
	    		i4 = (i3+1)%n;
	    		diff = diff_len(i1, i2, i3, i4, tour, dist);
	    		/*
	    		printf("%d %d %d %d %d\n", diff, i1, i2, i3, i4);
	    		*/
	    		if(diff < min_diff)
	    		{
	    			min_diff = diff;
	    			min_neighbor[0] = i1;
	    			min_neighbor[1] = i2;
	    			min_neighbor[2] = i3;
	    			min_neighbor[3] = i4;
	    		}
	    	}
	    }
	
		if(min_diff==0)	break;

		i1 = min_neighbor[0];
		i2 = min_neighbor[1];
		i3 = min_neighbor[2];
		i4 = min_neighbor[3];

		/*
		printf("%d %d %d %d %d\n", min_diff, i1, i2, i3, i4);
		*/
		
		if(i2 <= i3)
		{
			for(i=0;i<i3-i2+1;i++) sub_tour1[i] = tour[i2+i];
			n1 = i3-i2+1;
		}
		else
		{
			for(i=0;i<n-i2;i++) sub_tour1[i] = tour[i2+i];
			for(i=0;i<i3+1;i++) sub_tour1[i+n-i2] = tour[i];
			n1 = i3-i2+n+1;
		}
		if(i4 <= i1)
		{
			for(i=0;i<i1-i4+1;i++) sub_tour2[i] = tour[i4+i];
			n2 = i1-i4+1;
		}
		else
		{
			for(i=0;i<n-i4;i++) sub_tour2[i] = tour[i4+i];
			for(i=0;i<i1+1;i++) sub_tour2[i+n-i4] = tour[i];
			n2 = i1-i4+n+1;
		}

/*
		printf("[");
		for(i=0;i<n1;i++) printf("%d ", sub_tour1[i]+1);
		printf("]\n");
		printf("[");
		for(i=0;i<n2;i++) printf("%d ", sub_tour2[i]+1);
		printf("]\n");
*/

		for(i=0;i<n1;i++) min_tour[i] = sub_tour1[i];
		for(i=0;i<n2;i++) min_tour[n1+i] = sub_tour2[n2-1-i];

		min_len = tour_length(min_tour, dist, n);
				
		printf("%d: diff = %d, obj = %d \n",h, -min_diff, min_len);
		printf("replace_pos = [%d %d %d %d]\n", i1, i2, i3, i4);
		printf("tour = [");
		for(i=0;i<n;i++) printf("%d ", min_tour[i]+1);
		printf("]\n\n");
		
		for(i=0;i<n;i++) tour[i] = min_tour[i];
		h = h+1;
	}

    free(tour);
    free(sub_tour1);
    free(sub_tour2);

	return min_len;
}


int main(int argc, char *argv[])
{
	int i;

	char *fn;
	char *fn_init;

	int n;
	float **points;
	int **dist;

	int min_len;
	int *min_tour;

	int *init;

	clock_t begin, end;
	double time_spent;


	fn = argv[1]; /* tsp instance */
	fn_init = argv[2]; /* initial tour for the 2-opt */

	n = read_tsp(&points, fn); /* (points[i][0], points[i][1]): the coordinate of point i. */
	/*
	for(i=0;i<n;i++) printf("%d %f %f\n", i+1, points[i][0], points[i][1]);
	*/

	distance_matrix(&dist, points, n); /* dist[i][j]: the distance of i and j. */

	read_tour(&init, n, fn_init);

	min_tour = (int *) malloc(n*sizeof(int));
	begin = clock();
	min_len = tsp_2opt(min_tour, init, dist, n);
	end = clock();
	time_spent = (double)(end - begin) / (double) CLOCKS_PER_SEC;

	printf("obj = %d\n", min_len);
	printf("tour = [");
	for(i=0;i<n;i++) printf("%d ", min_tour[i]+1);
	printf("]\n");
	printf("CPU time (s): %f\n", time_spent);

	write_tour("a.tour", min_tour, n);


	return 0;
}
