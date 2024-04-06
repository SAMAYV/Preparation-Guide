vector<bool> visited;
vector<ll> tin, low;
ll timer;

void dfs(ll v,vector<ll>* edges,ll p = -1){
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for(auto to:edges[v]){
        if(to == p) continue;
        if(visited[to]){
            low[v] = min(low[v], tin[to]);
        } 
        else {
            dfs(to,edges,v);
            // means no edge from 'to' to the ancestor of v exists
            if(low[to] >= tin[v] &&  p != -1){
                IS_CUTPOINT(v);
            }
            low[v] = min(low[v], low[to]);
            ++children;
        }
    }
    if(p == -1 && children > 1){
        IS_CUTPOINT(v);
    }
}

void find_cutpoints(ll n,vector<ll>* edges){
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    REP(i,0,n){
        if(!visited[i]){
            dfs(i,edges);
        }
    }
}

// Function IS_CUTPOINT(a) is some function that will process the fact that vertex a is an articulation point, for example, print it (Caution that this can be called multiple times for a vertex).
// Now, there is a back edge from vertex v or one of its descendants to one of its ancestors if and only if vertex v has a child to for which low[to] < tin[v]. 
// If low[to] = tin[v], the back edge comes directly to v, otherwise it comes to one of the ancestors of v.
// Thus, the vertex v in the DFS tree is an articulation point if and only if low[to] ≥ tin[v].
 