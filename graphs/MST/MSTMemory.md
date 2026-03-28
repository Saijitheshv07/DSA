# Minimum Spanning Tree Quick Memory

## What is MST?

For a **connected, weighted, undirected graph**, MST is a subset of edges such that:

- All vertices are connected
- No cycle is formed
- Total edge weight is minimum
- Number of edges in MST is always `V - 1`

## Which graph type?

- MST is defined for **undirected weighted graphs**
- If graph is disconnected, we get a **Minimum Spanning Forest**

## Prim vs Kruskal

| Algorithm | Main Idea | Best When | Time Complexity | Data Structure |
| --------- | --------- | --------- | --------------- | -------------- |
| Prim's | Grow MST node by node | Adjacency list graph traversal style problems | `O((V + E) log V)` | Min Heap |
| Kruskal's | Pick edges globally in sorted order | Edge list input, DSU/cycle questions | `O(E log E)` | Sorting + DSU |

## Easy Intuition

- **Prim's**: stand on current MST and pull the cheapest outgoing edge
- **Kruskal's**: look at all edges globally and keep taking the smallest safe edge

## Recognition Pattern

- Asked for minimum cost to connect all nodes -> MST
- Weighted undirected graph -> think MST first
- If input is `edges = {u, v, wt}` -> Kruskal is natural
- If input is adjacency list -> Prim is natural

## Common Mistakes

- Do not use MST on directed graphs
- Do not confuse MST with shortest path
- MST minimizes **total tree cost**, not distance from a source
- For disconnected graphs, MST of whole graph does not exist

## One Line Difference From Shortest Path

- **Shortest Path**: minimum distance from one source to another
- **MST**: minimum total cost to connect every vertex
