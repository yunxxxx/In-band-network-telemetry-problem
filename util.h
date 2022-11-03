/* 
 *
 * untl.h is a header file for the untl.cpp
 *
 * more information will be write in the top of untl.cpp
 */


#ifndef UTIL_H
#define UTIL_H

int **make_graph(int nodeNum, int edgeNum);

void insert_connection(int edgeNum, int **graph);

void floyd_warshall(int nodeNum, int **graph, int **next);

int **make_next(int nodeNum, int **graph);

int find_odd (int nodeNum, int **graph, int *odd_vertices);

int **make_odd_graph(int odd_vertices_num, int *odd_vertices, int **graph);

void print_graph(int nodeNum, int **graph);

int find_greedy_perfect(int odd_vertices_num, int *odd_vertices, int **odd_graph, int **perfect_match);

void print_odd_graph(int odd_vertices_num, int *odd_vertices, int **old_graph);

void find_circuit(int **graph, int **next, int **perfect_match, int *odd_vertices, int nodeNum, int odd_vertices_num);

void find_helper(int **graph, int **next, int **perfect_match, int *odd_vertices, int nodeNum, int odd_vertices_num, int current, int last, bool is_virtual);

void find_path(int **next, int current, int last);

void print_odd(int *odd_vertices, int odd_vertices_num);

#endif
