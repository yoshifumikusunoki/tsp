#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tsp_tools.h"

#define MAX_NUM_POINTS 100000000
#define BUFFER_SIZE 1000

/* http://stackoverflow.com/questions/6127503/shuffle-array-in-c */
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int read_tsp(float ***points, char *fn)
{
	int i,j;
	FILE *fp;
	char *buffer;
	int buffer_size = BUFFER_SIZE;
	float p1,p2;
	int n = MAX_NUM_POINTS;

	buffer = (char *) malloc(buffer_size-1);

	fp = fopen(fn,"r");

	*points = (float **) malloc(n*sizeof(float *));

	i = 0;
	while (fgets(buffer,buffer_size-1,fp) != NULL)
	{
		if(sscanf(buffer,"%d %f %f",&j,&p1,&p2)==3)
		{
			(*points)[i] = (float *) malloc(2*sizeof(float));
			(*points)[i][0] = p1;
			(*points)[i][1] = p2;		
			i = i+1;			
		}
	}
	n = i;

	free(buffer);

	fclose(fp);

	return n;
}

void write_tsp(char *fn, float **points, int n)
{
	int i;
	FILE *fp;

	fp = fopen(fn,"w");
	for(i=0; i<n; i++) fprintf(fp,"%d %f %f\n",i+1,points[i][0],points[i][1]);
	fclose(fp);
}

void read_tour(int **tour, int n, char *fn)
{
	int i,j;
	FILE *fp;
	char *buffer;
	int buffer_size = BUFFER_SIZE;

	buffer = (char *) malloc(buffer_size-1);

	fp = fopen(fn, "r");

	*tour = (int *) malloc(n*sizeof(int));

	i = 0;
	while (fgets(buffer,buffer_size-1,fp) != NULL)
	{
		if(sscanf(buffer,"%d",&j)==1)
		{
			(*tour)[i] = j-1;
			i = i+1;		
		}
	}

	fclose(fp);
}

void write_tour(char *fn, int *tour, int n)
{
	int i;
	FILE *fp;

	fp = fopen(fn,"w");
	for(i=0;i<n;i++) fprintf(fp, "%d\n", tour[i]+1);
	fclose(fp);
}

void write_plot(char *fn, float **points, int *tour, int n)
{
	int i;
	FILE *fp;

	fp = fopen(fn,"w");

	fprintf(fp,"set size ratio -1\n");
	fprintf(fp,"plot '-' title 'points' w p, '-' title 'tour' w l\n");

	for(i=0;i<n;i++) fprintf(fp,"%f %f\n",points[i][0],points[i][1]);
	fprintf(fp,"e\n");

	for(i=0;i<n-1;i++)
	{
		fprintf(fp,"%f %f\n",points[tour[i]][0],points[tour[i]][1]);
		fprintf(fp,"%f %f\n",points[tour[i+1]][0],points[tour[i+1]][1]);
		fprintf(fp,"\n\n");
	}
	fprintf(fp,"%f %f\n",points[tour[n-1]][0],points[tour[n-1]][1]);
	fprintf(fp,"%f %f\n",points[tour[0]][0],points[tour[0]][1]);
	fprintf(fp,"e\n");

	fclose(fp);
}

void distance_matrix(int ***dist, float **points, int n)
{
	int i,j;

	*dist = (int **) malloc(n*sizeof(int *));
	for(i=0;i<n;i++) (*dist)[i] = (int *) malloc(n*sizeof(int));
	for(i=0;i<n;i++) for(j=0;j<n;j++) (*dist)[i][j] = (int) sqrt(pow(points[i][0]-points[j][0],2) + pow(points[i][1]-points[j][1],2));	
}

int tour_length(int *tour, int **dist, int n)
{
	int i;
	int len = 0;
	for(i=0;i<n-1;i++) len = len + dist[tour[i]][tour[i+1]];
	len = len + dist[tour[n-1]][tour[0]];
	return len;
}
