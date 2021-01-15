ll bfs(ll s,ll t,vector<ll>& parent,ll n,vector<vector<ll>>& adj,vector<vector<ll>>& capacity){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll,ll>> q;
    q.push({s, 1e9});

    while(q.size()){
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();
        for(ll next : adj[cur]){
            if(parent[next] == -1 && capacity[{cur,next}]){
                parent[next] = cur;
                ll new_flow = min(flow, capacity[{cur,next}]);
                if(next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}
ll maxflow(ll s,ll t,ll n,vector<vector<ll>>& adj,map<pair<ll,ll>,ll>& capacity){
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;
    while(new_flow = bfs(s,t,parent,adj,capacity)){
        flow += new_flow;
        ll cur = t;
        while(cur != s){
            ll prev = parent[cur];
            capacity[{prev,cur}] -= new_flow;
            capacity[{cur,prev}] += new_flow;
            cur = prev;
        }
    }
    return flow;
}
bool bipartite(ll n,vector<vector<ll>>& edges,vector<ll>* arr){
    vector<ll> side(n, -1);
    bool is_bipartite = true;
    queue<ll> q;
    REP(st,0,n){
        if(side[st] == -1){
            q.push(st);
            side[st] = 0;
            while(q.size()){
                ll v = q.front();
                arr[side[v]].insert(v);
                q.pop();
                for(auto u : edges[v]){
                    if(side[u] == -1){
                        side[u] = side[v] ^ 1;
                        q.push(u);
                    } 
                    else {
                        is_bipartite &= (side[u] != side[v]);
                    }
                }
            }
        }
    }
    return is_bipartite;
}

// In a node-disjoint path cover, each node belongs to exactly one path.
void Min_node_disjoint_path_cover(ll n,ll m,ll s,ll d,vector<ll>* edges){
    map<pair<ll,ll>,ll> capacity;
    vector<vector<ll>> adj;
    adj.resize(2*n+2,vector<ll>());

    REP(i,0,n+2){
        for(auto it:edges[i]){
            capacity[{i,it+n}] = 1;
            capacity[{it+n,i}] = 0;
            adj[i].push_back(it+n);
            adj[it+n].push_back(i);
        }
    }
    vector<ll> v[2];
    if(!bipartite(2*n,adj,v)){
        cout<<-1<<endl;
        return;
    }
    for(auto it:v[0]){
        adj[0].push_back(it);
        capacity[{0,it}] = 1;
        capacity[{it,0}] = 0;
    }
    for(auto it:v[1]){
        adj[it].push_back(2*n+1);
        capacity[{it,2*n+1}] = 1;
        capacity[{2*n+1,it}] = 0;
    }
    maxflow(s,d,n + 2,adj,capacity);
}
int main() 
{ 
	ll n,m;
	cin>>n>>m;
	vector<ll> edges[2*n+2];
	ll source = 0;
	ll dest = 2*n+1;
	REP(i,0,m){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
	}
	cout<<n - Min_node_disjoint_path_cover(n,m,source,dest,edges)<<endl;
    // A minimum general path cover can be found almost like a minimum node disjoint path cover. 
    // It suffices to add some new edges to the matching graph so that there is an edge a → b always when there is a path from a to b 
    // in the original graph (possibly through several edges).

    // In a directed acyclic graph, the size of a minimum general path cover equals the size of a maximum antichain
    // An antichain is a set of nodes of a graph such that there is no path from any node to another node using the edges of the graph.
	return 0;	
} 