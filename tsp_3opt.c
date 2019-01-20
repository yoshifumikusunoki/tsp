#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp_tools.h"

int diff_len(int i1, int i2, int i3, int i4, int i5, int i6, int type, int *tour, int **dist)
{
  	int s1, s2, s3, s4, s5, s6;
	s1 = tour[i1];
	s2 = tour[i2];
	s3 = tour[i3];
	s4 = tour[i4];
	s5 = tour[i5];
	s6 = tour[i6];
	if(type == 0)
	{
		return (dist[s1][s6] + dist[s5][s4]  + dist[s2][s3] - dist[s1][s2] - dist[s3][s4] - dist[s5][s6]);
	}else if(type == 1)
	{
		return (dist[s1][s5] + dist[s6][s4]  + dist[s2][s3] - dist[s1][s2] - dist[s3][s4] - dist[s5][s6]);
	}else if(type == 2)
	{
		return (dist[s1][s6] + dist[s5][s3]  + dist[s2][s4] - dist[s1][s2] - dist[s3][s4] - dist[s5][s6]);
	}else
	{
		return (dist[s1][s3] + dist[s5][s4]  + dist[s2][s6] - dist[s1][s2] - dist[s3][s4] - dist[s5][s6]);		
	}

}

int tsp_3opt(int *min_tour, int *init, int **dist, int n)
{
	int h,i,j,k;
	int i1,i2,i3,i4,i5,i6;
	int min_len;

	int *sub_tour1, *sub_tour2, *sub_tour3;
	int n1, n2, n3;

	int diff, min_diff;
	int min_neighbor[6];
	int min_type;

	int *tour;

	tour = (int *) malloc(n*sizeof(int));

	for(i=0;i<n;i++) min_tour[i] = init[i];

	min_len = tour_length(min_tour, dist, n);

	for(i=0;i<n;i++) tour[i] = min_tour[i];

	sub_tour1 = (int *) malloc(n*sizeof(int)); /* sub tour 2 to 5 */
	sub_tour2 = (int *) malloc(n*sizeof(int)); /* sub tour 6 to 3 */
	sub_tour3 = (int *) malloc(n*sizeof(int)); /* sub tour 4 to 1 */

	h = 0;
	while(1)
	{
		/* initialize the next neighbor */
	    min_diff = 0;
	    min_type = 1;
	    min_neighbor[0] = 0;
	    min_neighbor[1] = 1;
	    min_neighbor[2] = 2;
	    min_neighbor[3] = 3;
	    min_neighbor[4] = 1;
	    min_neighbor[5] = 2;

	    /* find the minimum neighbor */
	    for(i=0;i<n;i++)
	    {
	    	i1 = i;
	    	i2 = (i1+1)%n;
	    	for(j=0;j<n-2;j++)
	    	{
	    		i3 = (i2+1+j)%n;
	    		i4 = (i3+1)%n;
	    		for(k=0;k<=j;k++)
	    		{
		    			i5 = (i2+k)%n;
		    			i6 = (i5+1)%n;
		    		
		    		/* calculate the difference of distance between the current tour and a neighbor tour */
		    		diff = diff_len(i1, i2, i3, i4, i5, i6, 0, tour, dist);
		    		if(diff < min_diff)
		    		{
		    			min_diff = diff;
		    			min_type = 0;
		    			min_neighbor[0] = i1;
		    			min_neighbor[1] = i2;
		    			min_neighbor[2] = i3;
		    			min_neighbor[3] = i4;
		    			min_neighbor[4] = i5;
		    			min_neighbor[5] = i6;
		    		}
		    		diff = diff_len(i1, i2, i3, i4, i5, i6, 1, tour, dist);
		    		if(diff < min_diff)
		    		{
		    			min_diff = diff;
		    			min_type = 1;
		    			min_neighbor[0] = i1;
		    			min_neighbor[1] = i2;
		    			min_neighbor[2] = i3;
		    			min_neighbor[3] = i4;
		    			min_neighbor[4] = i5;
		    			min_neighbor[5] = i6;
		    		}
		    		diff = diff_len(i1, i2, i3, i4, i5, i6, 2, tour, dist);
		    		if(diff < min_diff)
		    		{
		    			min_diff = diff;
		    			min_type = 2;
		    			min_neighbor[0] = i1;
		    			min_neighbor[1] = i2;
		    			min_neighbor[2] = i3;
		    			min_neighbor[3] = i4;
		    			min_neighbor[4] = i5;
		    			min_neighbor[5] = i6;
		    		}
		    		diff = diff_len(i1, i2, i3, i4, i5, i6, 3, tour, dist);
		    		if(diff < min_diff)
		    		{
		    			min_diff = diff;
		    			min_type = 3;
		    			min_neighbor[0] = i1;
		    			min_neighbor[1] = i2;
		    			min_neighbor[2] = i3;
		    			min_neighbor[3] = i4;
		    			min_neighbor[4] = i5;
		    			min_neighbor[5] = i6;
		    		}
				}
	    	}
	    }
	
		if(min_diff==0)	break;

		i1 = min_neighbor[0];
		i2 = min_neighbor[1];
		i3 = min_neighbor[2];
		i4 = min_neighbor[3];
		i5 = min_neighbor[4];
		i6 = min_neighbor[5];
		
		/* cut the sub tours */
		if(i2 <= i5)
		{
			for(i=0;i<i5-i2+1;i++) sub_tour1[i] = tour[i2+i];
			n1 = i5-i2+1;
		}
		else
		{
			for(i=0;i<n-i2;i++) sub_tour1[i] = tour[i2+i];
			for(i=0;i<i5+1;i++) sub_tour1[i+n-i2] = tour[i];
			n1 = i5-i2+n+1;
		}
		if(i6 <= i3)
		{
			for(i=0;i<i3-i6+1;i++) sub_tour2[i] = tour[i6+i];
			n2 = i3-i6+1;
		}
		else
		{
			for(i=0;i<n-i6;i++) sub_tour2[i] = tour[i6+i];
			for(i=0;i<i3+1;i++) sub_tour2[i+n-i6] = tour[i];
			n2 = i3-i6+n+1;
		}
		if(i4 <= i1)
		{
			for(i=0;i<i1-i4+1;i++) sub_tour3[i] = tour[i4+i];
			n3 = i1-i4+1;
		}
		else
		{
			for(i=0;i<n-i4;i++) sub_tour3[i] = tour[i4+i];
			for(i=0;i<i1+1;i++) sub_tour3[i+n-i4] = tour[i];
			n3 = i1-i4+n+1;
		}

/*
		printf("[");
		for(i=0;i<n1;i++) printf("%d ", sub_tour1[i]+1);
		printf("]\n");
		printf("[");
		for(i=0;i<n2;i++) printf("%d ", sub_tour2[i]+1);
		printf("]\n");
		printf("[");
		for(i=0;i<n3;i++) printf("%d ", sub_tour3[i]+1);
		printf("]\n");
*/

		/* reconnect the sub tours */
		if(min_type == 0)
		{
			for(i=0;i<n1;i++) min_tour[i] = sub_tour1[i];
			for(i=0;i<n3;i++) min_tour[n1+i] = sub_tour3[i];
			for(i=0;i<n2;i++) min_tour[n1+n3+i] = sub_tour2[i];
		}
		else if(min_type == 1)
		{
			for(i=0;i<n1;i++) min_tour[i] = sub_tour1[i];
			for(i=0;i<n3;i++) min_tour[n1+i] = sub_tour3[n3-1-i];
			for(i=0;i<n2;i++) min_tour[n1+n3+i] = sub_tour2[i];
		}
		else if(min_type == 2)
		{
			for(i=0;i<n1;i++) min_tour[i] = sub_tour1[i];
			for(i=0;i<n2;i++) min_tour[n1+i] = sub_tour2[n2-1-i];
			for(i=0;i<n3;i++) min_tour[n1+n2+i] = sub_tour3[n3-1-i];
		}
		else
		{
			for(i=0;i<n1;i++) min_tour[i] = sub_tour1[i];
			for(i=0;i<n3;i++) min_tour[n1+i] = sub_tour3[i];
			for(i=0;i<n2;i++) min_tour[n1+n3+i] = sub_tour2[n2-1-i];
		}

		min_len = tour_length(min_tour, dist, n);

		printf("%d: diff = %d, obj = %d \n",h, -min_diff, min_len);
		printf("replace_type = %d, replace_pos = [%d %d %d %d %d %d]\n", min_type, i1, i2, i3, i4, i5, i6);
		printf("tour = [");
		for(i=0;i<n;i++) printf("%d ", min_tour[i]+1);
		printf("]\n\n");

		for(i=0;i<n;i++) tour[i] = min_tour[i];
		h = h+1;
	}

    free(tour);
    free(sub_tour1);
    free(sub_tour2);
    free(sub_tour3);

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
	/* for(i=0;i<n;i++) printf("%d %f %f\n", i+1, points[i][0], points[i][1]); */

	distance_matrix(&dist, points, n); /* dist[i][j]: the distance of i and j. */

	read_tour(&init, n, fn_init);

	min_tour = (int *) malloc(n*sizeof(int));
	begin = clock();
	min_len = tsp_3opt(min_tour, init, dist, n);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("obj = %d\n", min_len);
	printf("tour = [");
	for(i=0;i<n;i++) printf("%d ", min_tour[i]+1);
	printf("]\n");
	printf("CPU time (s): %f\n", time_spent);

	write_tour("a.tour", min_tour, n);


	return 0;
}
