//Since there is no weight for the edges, BFS naturally finds
// TC : O(V+E) 
//Each Vertex visited once to process and Each edge is explored once. (twice in undirected graph)
//SC : O(V)
vector<int> shortestPath(int V, vector<vector<int>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int nbr : adj[node]) {
            if(dist[node] + 1 < dist[nbr]) {
                dist[nbr] = dist[node] + 1;
                q.push(nbr);
            }
        }
    }
    return dist;
}