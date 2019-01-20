# Introduction
This includes C codes of 2-opt and 3-opt methods for travel salesman problems.

# Compile
## 2-opt
```
gcc tsp_2opt.c tsp_tools.c -o tsp_2opt
```
## 3-opt
```
gcc tsp_3opt.c tsp_tools.c -o tsp_3opt
```
## Initializing tours
The nearest neighbor method for tour generation.
```
gcc tsp_nn.c tsp_tools.c -o tsp_nn
```
Random tour generation.
```
gcc gen_tour.c tsp_tools.c -o gen_tour
```
## Plot planar problems and tours using GNU plot
```
gcc tour_to_plot.c tsp_tools.c -o tour_to_plot
```
# How to use
## Case 1
Let `problem/tsp225.tsp` be a problem.

Get initial tour.
```
./tsp_nn problem/tsp225.tsp 1
```
The last argument `1` is an initial node index for the nearest neighbor method.
The output is `a.tour`. It contains an order of the node indexes.

Get a tour by 3-opt
```
./tsp_3opt problem/tsp225.tsp a.tour
```
The output is also `a.tour`.

Plot the result by GNU plot
```
./tour_to_plot a.tour
gnuplot -p a.plt
```
