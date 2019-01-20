void shuffle(int *array, size_t n);
int read_tsp(float ***points, char *fn);
void write_tsp(char *fn, float **points, int n);
void read_tour(int **tour, int n, char *fn);
void write_tour(char *fn, int *tour, int n);
void distance_matrix(int ***dist, float **points, int n);
void write_plot(char *fn, float **points, int *tour, int n);
int tour_length(int *tour, int **dist, int n);
