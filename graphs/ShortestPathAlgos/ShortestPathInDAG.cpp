//Special case where TopoSort + Relaxation is better that Dijkstra
//Works for Both +ve and -ve weights
/*
In a graph with cycles, a path you find later could "loop back" and provide a shorter route to a node you thought you were done with. That's why Dijkstra has to constantly re-evaluate and pick the "global minimum" from its priority queue—it’s playing it safe.
In a DAG, the "next" nodes are the only nodes. Because there is no way to loop back, the topological order guarantees that once you've finished relaxing all edges coming into a node, you have the absolute shortest path. You don't need to check the other nodes in the graph because none of them can ever point back to your current position.
Think of it like this:
Dijkstra is like navigating a maze: You have to keep track of all possible turns because you might find a shortcut that loops back around.
Toposort is like a one-way assembly line: Once a part passes a station, it never comes back, so you only need to worry about what's happening at the current station.
*/
void topoSort(int node, vector<vector<pair<int,int>>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for(auto &[nbr, wt] : adj[node]) {
        if(!vis[nbr])
            topoSort(nbr, adj, vis, st);
    }
    st.push(node);
}

vector<int> shortestPath(int V, vector<vector<pair<int,int>>>& adj, int src) {
    stack<int> st;
    vector<int> vis(V,0);
    for(int i=0;i<V;i++)
        if(!vis[i])
            topoSort(i, adj, vis, st);

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    while(!st.empty()) {
        int node = st.top();
        st.pop();
        if(dist[node] != INT_MAX) {
            for(auto &[nbr, wt] : adj[node]) {
                if(dist[node] + wt < dist[nbr])
                    dist[nbr] = dist[node] + wt;
            }
        }
    }

    return dist;
}