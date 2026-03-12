# All Possible Combinations

| Graph Type                         | Weights                    | Source Type              | Best Algorithm             | Time Complexity | Notes                                |
| ---------------------------------- | -------------------------- | ------------------------ | -------------------------- | --------------- | ------------------------------------ |
| Unweighted (Directed / Undirected) | All edges = 1              | Single Source            | **BFS**                    | O(V + E)        | Most common grid/graph shortest path |
| Weighted                           | Positive                   | Single Source            | **Dijkstra (Min Heap)**    | O(E log V)      | Most standard weighted shortest path |
| Weighted                           | 0 or 1                     | Single Source            | **0-1 BFS (Deque)**        | O(V + E)        | Faster than Dijkstra                 |
| Weighted                           | Negative allowed           | Single Source            | **Bellman-Ford**           | O(VE)           | Detects negative cycles              |
| Weighted                           | DAG (may include negative) | Single Source            | **Topo Sort + Relaxation** | O(V + E)        | Fastest for DAG                      |
| Weighted                           | Any weights                | All Pairs                | **Floyd-Warshall**         | O(V³)           | Works with negative edges            |
| Weighted                           | Positive                   | All Pairs (Sparse graph) | **Run Dijkstra V times**   | O(VE log V)     | Often used in practice               |
| Weighted                           | Negative edges             | All Pairs                | **Johnson's Algorithm**    | O(VE log V)     | Uses Bellman-Ford + Dijkstra         |



# Easy to Remember Decision Tree

Unweighted → BFS

Weighted  
├── DAG → Topo Shortest Path  
├── weights {0,1} → 0-1 BFS  
├── negative weights → Bellman-Ford  
└── positive weights → Dijkstra  

All Pairs  
├── small graph → Floyd-Warshall  
└── large graph → Johnson's Algorithm
