/* 
 * This is a function to solve the problem of In-band Network Telemetry
 * Detial of different function will be discrabe in util.cpp at the top each different function
 * 
 * The function will include util.h and iostream just for scaning and print popurse.
 * 
 * 
 * The make file will creat "int" and to run the fucntion
 * enter the command "./int"
 */

#include "util.h"
#include <iostream>

int main(int argc, char **argv) {
    // all the virables  will be used in the functions.
    int nodeNum, edgeNum, odd_vertices_num;
    int **graph, **next, **odd_graph, **perfect_match;
    int *odd_vertices;

    //read the number of node and number of edge from user.
    std::cin >> nodeNum;
    std::cin >> edgeNum;

    //functiong call. Detial will be discrabe in util.cpp
    odd_vertices = new int[nodeNum];

    graph = make_graph(nodeNum, edgeNum);

    insert_connection(edgeNum, graph);

    next = make_next(nodeNum, graph);

    floyd_warshall(nodeNum, graph, next);

    odd_vertices_num = find_odd(nodeNum, graph, odd_vertices);

    print_odd(odd_vertices, odd_vertices_num);

    odd_graph = make_odd_graph(odd_vertices_num, odd_vertices, graph);

    print_odd_graph(odd_vertices_num, odd_vertices, odd_graph);

    //use the odd verticus number set up the perfect mach graph before use it.
    perfect_match = new int*[odd_vertices_num];
    for (int i = 1; i <= odd_vertices_num; i++) {
        perfect_match[i] = new int[odd_vertices_num];
    }

    //keep function calling.

    edgeNum += find_greedy_perfect(odd_vertices_num, odd_vertices, odd_graph, perfect_match);

    find_circuit(graph, next, perfect_match, odd_vertices, nodeNum, odd_vertices_num);
}