//Famously Known as Dijkstra Algorithm, Only works for non-ngeative weights
//Workd for both directed and undirected
//It is greedy algo based on the fact that , in each step if we pick minimum, the overall response will be correct
//But for -ve weights, first step can be a large +ve value and second step can be a large -ve value and result with be optimal.
//TC : O(VlogV + E) , O(V) + O(E) + O(ElogV) ~ O((V+E)LogV)
//SC : O(V)

vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        // Optimization: skip outdated entries
        if(d > dist[node]) continue;
        for(auto &[nbr, wt] : adj[node]) {
            if(dist[node] + wt < dist[nbr]) {
                dist[nbr] = dist[node] + wt;
                pq.push({dist[nbr], nbr});
            }
        }
    }
    return dist;
}

/*
0 --10--> 1
0 --1-->  2
2 --1-->  1

here (10,1) becomes an outdated entry, so optimization by skipping is important to not process the same node twice
*/