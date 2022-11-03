# In-band-network-telemetry-problem
This project involves algorithms on undirected graphs, represented using adjacency lists, to solve the in-band network telemetry (INT) problem.


In computer networks, in-band network telemetry (INT) seeks to achieve high-precision monitoring of the
network links (e.g., latency, packet drop rate, time-to-live, jitter, and bandwidth along a link) and also the
routers (e.g., queue-depth of interfaces in a router). In this project, we will model a computer network as a
connected undirected graph G = (V, E) with routers modelled as the vertices V ; there is an edge (u, v) ∈ E,
where u, v ∈ V and u 6= v, if there is a communication link between routers u and v.
In this project, we are interested solve the problem of in-band network telemetry by finding a single path that traverses each edge of the graph once, though it is allowed to visit each vertex more than once.
Unfortunately, a graph G has an Euler path if and only if it has at most two vertices of odd-degree. An
Euler circuit is a path that starts and ends at the same vertex. As we’ll see, in order to handle an arbitrary
connected graph we may need to traverse each edge more than once.

![Screenshot 2022-11-03 005519](https://user-images.githubusercontent.com/81000984/199671008-ea481b5e-a3f0-4c10-964f-fc7f5b96b7ce.png)

