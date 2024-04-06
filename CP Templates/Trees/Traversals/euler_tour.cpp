vector<ll> height,euler,first;
vector<bool> visited;

void dfs(vector<ll>* edges,ll node,ll h = 0){
    visited[node] = 1;
    height[node] = h;
    first[node] = euler.size();
    euler.push_back(node);
    for(auto to : edges[node]){
        if(!visited[to]){
            dfs(edges, to, h + 1);
            euler.push_back(node);
        }
    }
}

void Euler_Tour(ll n,vector<ll>* edges){
    visited.assign(n,0);
    height.assign(n,0);
    first.assign(n,0);
    euler.clear();
    dfs(edges,0);
}
