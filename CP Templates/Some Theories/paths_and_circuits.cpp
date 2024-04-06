Focusing on two types of graphs->
    1. An Eulerian path is a path that goes through each edge,
        exactly once. 
    2. A Hamiltonian path is a path that visits each node exactly once. 

Finding a Hamiltonian path is a NP hard problem. 

An eulerian circuit is an eulerian path that starts and ends at the same node. 

An undirected graph, has an eulerian path, exactly when all edges belong to the same component,
and->
    -> degree of each node is even or
    -> degree of exactly two node is odd, and rest all are even degree nodes.

A directed graph contains an eulerian path exactly, when all the edges, belong to the same connected component,
and->
    -> in each node, indegree equals outdegree.
    -> in one node indegree is one greater than outdegree, and another node having outdegree one,
        greater than indegree, and rest all have equal in and out-degrees.


Hierholzers algo:
    Algo to constructing Eulerian circuit.
    Assuming there exists an Eulerian circuit,
    -> First find any circuit, and then keep adding subcircuits, associated,
        with a considered node.

    -> Use it to find Eulerian path, by adding an edge between the odd degree nodes,
        and then later removing it. 


Hamiltonian paths:
    Path that visits each node exactly once.
    If a Hamiltonian path has same begin and end node, then it is called,
        Hamiltonian circuit.
        
    Existence:
        A complete graph contains a Hamiltonian path.

        Dirac's theorem:
            if the degree of each node is atleast n/2, the graph 
                contains a Hamiltonian path.

        Ore's theorem:
            If the sum of degrees of each non-adjacent pair of nodes is,
            at least n, the graph conatins a Hamiltonian path.


    Construction:
         

        
