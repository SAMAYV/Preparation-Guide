vector<bool> visited;
vector<ll> tin, low;
ll timer = 0;

void dfs(ll v,vector<ll>* edges,ll p = -1){
    visited[v] = 1;
    tin[v] = low[v] = timer++;
    for(auto to:edges[v]){
        if(to == p) continue;
        if(visited[to]){
            low[v] = min(low[v], tin[to]);
        } 
        else {
            dfs(to,edges,v);
            low[v] = min(low[v], low[to]);
            if(low[to] > tin[v]){
                IS_BRIDGE(v, to);
            }
        }
    }
}

void find_bridges(ll n,vector<ll>* edges){
    timer = 0;
    visited.assign(n,0);
    tin.assign(n,-1);
    low.assign(n,-1);
    REP(i,0,n){
        if(!visited[i]){
            dfs(i,edges);
        }
    }
}

// Function IS_BRIDGE(a, b) is some function that will process the fact that edge (a,b) is a bridge, for example, print it.
// Note that this implementation malfunctions if the graph has multiple edges, since it ignores them. 
// Of course, multiple edges will never be a part of the answer, so IS_BRIDGE can check additionally that the reported bridge is not a multiple edge. 
// Alternatively it's possible to pass to dfs the index of the edge used to enter the vertex instead of the parent vertex (and store the indices of all vertices).
// Now, there is a back edge from vertex v or one of its descendants to one of its ancestors if and only if vertex v has a child to for which low[to] ≤ tin[v]. 
// If low[to] = tin[v], the back edge comes directly to v, otherwise it comes to one of the ancestors of v.
// Thus, the current edge (v,to) in the DFS tree is a bridge if and only if low[to] > tin[v].
 