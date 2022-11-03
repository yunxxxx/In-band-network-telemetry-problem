/* 
 *
 *
 * detials of different fucntion will be discrabe at the top of the functions.
 * The functing inside util.cpp is working for main to solve the in-band network telemetry problem.
 * 
 */
#include "util.h"
#include <iostream>

//the make graph will make a base of undirected graph
//because all of the nodes are being conceded connected and all edges have the same distence,  the function use the edgeNum as the besic number instead of positive infinity
int **make_graph(int nodeNum, int edgeNum) {
    int **graph;
    graph = new int*[nodeNum];
    for (int i = 1; i <= nodeNum; i++) {
        graph[i] = new int[nodeNum];
    }
    
    for (int i = 1; i <= nodeNum; i++) {
        for (int k = 1; k <= nodeNum; k++) {

            if (i == k) {
                graph[i][k] = 0;
            }
            else {
                graph[i][k] = edgeNum;
            }
        }
    }
    return graph;
}

//this function will use the graph made in the make graph function and keep get input from user get connection of all the edges.
void insert_connection(int edgeNum, int **graph) {
    int saver1, saver2;

    for (int i = 1; i <= edgeNum; i++) {
        std::cin >> saver1;
        std::cin >> saver2;
        graph[saver1][saver2] = 1;
        graph[saver2][saver1] = 1;
    }
}

//the make graph will make a base of the graph of next function, it will set all the node to -1 at frist wait for the floyd warshall function
int **make_next(int nodeNum, int **graph) {
    int **next;
    next = new int*[nodeNum];
    for (int i = 1; i <= nodeNum; i++) {
        next[i] = new int[nodeNum];
    }
    
    for (int i = 1; i <= nodeNum; i++) {
        for (int k = 1; k <= nodeNum; k++) {
            if (graph[i][k] == 1) {
                next[i][k] = k;
            }
            else {
                next[i][k] = -1;
            }
        }
    }
    return next;
}

//this function will use floyd warshall algorthms get the shotest path by geting the graph and the length of the graph
//it also get the graph "next" and use the algorthm to record the next node of every node for the shortest path.
void floyd_warshall(int nodeNum, int **graph, int **next) {
    for (int k = 1; k <= nodeNum; k++) {
        for (int i = 1; i <= nodeNum; i++) {
            for (int j = 1; j <= nodeNum; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

//This functing will find all the node have odd number of edge been connected and return the total number of odd node
int find_odd (int nodeNum, int **graph, int *odd_vertices) {
    int odd_counter = 0, vertices_counter = 1;
    for (int i = 1; i <= nodeNum; i++) {
        for (int j = 1; j <= nodeNum; j++) {
            if (graph[i][j] == 1) {
                odd_counter++;
            }
        }
        if (odd_counter % 2 != 0) {
            odd_vertices[vertices_counter] = i;
            vertices_counter++;
        }
        odd_counter = 0;
    }
    return (vertices_counter - 1);
}

//this function will use the result of find odd function to make another 2D graph then return it.
int **make_odd_graph(int odd_vertices_num, int *odd_vertices, int **graph) {
    int **odd_graph;
    odd_graph = new int*[odd_vertices_num];
    for (int i = 1; i <= odd_vertices_num; i++) {
        odd_graph[i] = new int[odd_vertices_num];
    }
    
    int saver1, saver2;
    for (int i = 1; i <= odd_vertices_num; i++) {
        for (int k = 1; k <= odd_vertices_num; k++) {
            saver1 = odd_vertices[i];
            saver2 = odd_vertices[k];
            odd_graph[i][k] = graph[saver1][saver2];
        }
    }
    return odd_graph;
}

//this fucntion will use greedy algorithms find the perfect match of the function
//perfect match: All the node been connected that only have been used once 
//the function will print the result out when finding it and it will record the result to the perfect match graph
//then it will return the number of how many paired been found in the graph as an int.
int find_greedy_perfect(int odd_vertices_num, int *odd_vertices, int **odd_graph, int **perfect_match) {
    int *odd_vertices_copy = new int[odd_vertices_num];
    int node_counter = 0, vertices_left = odd_vertices_num;

    int perfect_edge_num = 0;
    
    int path_adder = 1;
    int list_adder = 0;
    bool checker = true;

    //make the empty function first and copy the list of odd vertices array.
    for (int i = 1; i <= odd_vertices_num; i++) {
        for (int k = 1; k <= odd_vertices_num; k++) {
            perfect_match[i][k] = 0;
        }
        odd_vertices_copy[i] = odd_vertices[i];
    }

    //use whild loop check the list untill all of the node been checked or no more odd vertices left
    //the for loop and if steament inside of the function is just for checking all the nodes and mark it down when it been checked.
    std::cout << "The greedy perfect matching in O: M = { ";
    while (node_counter < (odd_vertices_num * odd_vertices_num) && vertices_left > 0) {
        for (int i = 1; i <= odd_vertices_num; i++) {
            for (int j = 1; j <= odd_vertices_num; j++) {

                if (odd_graph[i][j] == 0) {
                    perfect_match[i][j] = -1;
                    node_counter++;
                }
                else if (perfect_match[i][j] == 0 && odd_graph[i][j] == path_adder){
                    while (list_adder < odd_vertices_num && checker) {
                        list_adder++;
                        if (odd_vertices_copy[list_adder] == odd_vertices[j]) {
                            //set checker to false when if find a odd pair may need to be add
                            checker = false;
                        }
                    }
                    if (!checker) {
                        //check is the node have already been used
                        for (int k = 1; k < odd_vertices_num; k++) {
                            if (odd_vertices_copy[k] == odd_vertices[i]) {
                                checker = true;
                                perfect_match[i][j] = odd_graph[i][j];
                                perfect_match[j][i] = odd_graph[i][j];
                                odd_vertices_copy[k] = -1;
                                odd_vertices_copy[list_adder] = -1;
                                node_counter++;
                                vertices_left--;
                                vertices_left--;
                                std::cout << "("<< odd_vertices[i] << "," << odd_vertices[j] << ") ";
                                perfect_edge_num++;
                            }
                        }
                        //if the checker not been set back to true, means it not the case. Mark the node been checked and go to next.
                        if (!checker) {
                            checker = true;
                            perfect_match[i][j] = -1;
                            node_counter++;
                        }
                    }
                    //reset the list adder to 0 every time because it's useing a while loop to check every line to redese the runtime
                    list_adder = 0;
                }
            }
        }
        path_adder++;
    }
    std::cout << "}\n\n";

    //if the vertices left is 0, means there are node not been marked. Then enter the graph again mark down every node that are not perfect edge for the fucture use.
    if (vertices_left == 0) {
        for (int i = 1; i <= odd_vertices_num; i++) {
                for (int k = 1; k <= odd_vertices_num; k++) {
                    if (perfect_match[i][k] == 0) {
                        perfect_match[i][k] = -1;
                    }
                }
            }
    }

    return perfect_edge_num;
}

//This function is to call the recursive function find_helper to get the final path of the euler circuit.
//current will set up the start node of the graph and it will set the the previous node as -1 first.
void find_circuit(int **graph, int **next, int **perfect_match, int *odd_vertices, int nodeNum, int odd_vertices_num) {
    int current = 1;
    int previous = -1;
    bool is_virtual = false;
    std::cout << "The Euler circuit in G with virtual edges is:\n";

    //recursive function start
    find_helper(graph, next, perfect_match, odd_vertices, nodeNum, odd_vertices_num, current, previous, is_virtual);
}

void find_helper(int **graph, int **next, int **perfect_match, int *odd_vertices, int nodeNum, int odd_vertices_num, int current, int previous, bool is_virtual) {

//because of odd vertices graph is from 1 to number of the odd vertices, it will need to have 2 index to be able to find the place of each node.
    int odd_index1 = -1; 
    int odd_index2 = 1; 

//everytime when there is a new node, check if this node could be a virtices node. set the index1 to i to record the place of the ndoe.
    for (int i = 1; i <= odd_vertices_num; i++) {
        if (odd_vertices[i] == current) {
            odd_index1 = i;
            break;
        }
    }

//enter the for loop check for every node that could connect to current node
    for (int i = 1; i <= nodeNum; i++) {
        //if there is a connection find, call the function with new node
        if (graph[current][i] == 1) {
            //before call the new node, set the node on the graph to -1 mark it as used.
            graph[current][i] = -1;
            graph[i][current] = -1;
            //when call the function, set the current to i which is next node, then set the previous to current. Because this if steatment is cheking forthe graph, so set teh virtual checker to false.
            find_helper(graph, next, perfect_match, odd_vertices, nodeNum, odd_vertices_num, i, current, false);
        }

        //if there is a odd vertices find, enter this if steatment
        if (odd_index1 != -1 && odd_vertices[odd_index2] == i) {
            //check if this odd vertices bees used by using perfect match graph
            if (perfect_match[odd_index1][odd_index2] != -1) {
                //set the node on the perfect match to -1 marked as used
                perfect_match[odd_index1][odd_index2] = -1;
                perfect_match[odd_index2][odd_index1] = -1;
                //call the function, set the current as the i of the odd_vertices and set teh previous to current. Because this is checking the vertices path, so set the checker to true.
                find_helper(graph, next, perfect_match, odd_vertices, nodeNum, odd_vertices_num, odd_vertices[odd_index2], current, true);
            }
            odd_index2++;
        }
    }

    //when previous is -1, means all the path has been print. return the function with out print out anything.
    if (previous == -1) {
        return;
    }

    //if the path is virtual, call the get path function to print the path of the virtual path.
    if (is_virtual) {
        find_path(next, current, previous);
    }
    //if it's not a virtual path, print out the paht.
    else {
        std::cout << "\t(" << current << "," << previous << ")\n";
    }
}

//this is a helper function to get the path of some node are not connected.
void find_path(int **next, int current, int previous) {
    //use graph of "next" keep get the next node until it find the node it want.
    while (current != previous) {
        std::cout << "\t(" << current << "," << next[current][previous] << ")\n";
        current = next[current][previous];
    }
}


//this function will print the odd degree vertices out by geting the list of vertices and totla number.
void print_odd(int* odd_vertices, int odd_vertices_num) {
    std::cout << "The odd degree vertices in G: { O = { ";
    for (int i = 1; i <= odd_vertices_num; i++) {
        std::cout << odd_vertices[i] << " ";
    }
    std::cout << "} }\n\n";
}

//this funcrion can print out the graph with out any information.
//the function is never been used in main
//it's a test perpost function.
void print_graph(int nodeNum, int **graph) {
    for (int i = 1; i <= nodeNum; i++) {
        for (int k = 1; k <= nodeNum; k++) {

            std::cout << graph[i][k] << " ";
        }
            std::cout << "\n";
    }
}

//this function will print the graph of odd graph my geting the number of odd vertices, array of odd vertices and the graph of odd nodes.
//the function will print the graph by the sample fomular.
//As a result, if the node number get over 999, the fomular will looks not as expect.
void print_odd_graph(int odd_vertices_num, int *odd_vertices, int **odd_graph) {
    std::cout << "Results of Floyd-Warshall on O: \n";
    std::cout << "     | ";
    for (int i = 1; i <= odd_vertices_num; i++) {
        if (odd_vertices[i] < 10) {
            std::cout << "   "<< odd_vertices[i];
        }
        else if (odd_vertices[i] < 100) {
            std::cout << "  "<< odd_vertices[i];
        }
        else {
            std::cout << " "<< odd_vertices[i];
        }
    }
    std::cout << "\n--- -+- ";
    for (int i = 1; i <= odd_vertices_num; i++) {
            std::cout <<"--- ";
    }
    std::cout << "\n";

    for (int i = 1; i <= odd_vertices_num; i++) {
        if (odd_vertices[i] < 10) {
            std::cout << "  "<< odd_vertices[i] << "  | ";
        }
        else if (odd_vertices[i] < 100) {
            std::cout << " "<< odd_vertices[i] << "  | ";;
        }
        else {
            std::cout << ""<< odd_vertices[i] << "  | ";;
        }

        for (int k = 1; k <= odd_vertices_num; k++) {
            if (odd_graph[i][k] < 10) {
                std::cout << "   "<< odd_graph[i][k];
            }
            else if (odd_graph[i][k] < 100) {
                std::cout << "  "<< odd_graph[i][k];
            }
            else {
                std::cout << " "<< odd_graph[i][k];
            }
        }
            std::cout << "\n";
    }

    std::cout << "\n";
}




