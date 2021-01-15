ll bfs(ll s,ll t,vector<ll>& parent,ll n,vector<vector<ll>>& adj,vector<vector<ll>>& capacity){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll,ll>> q;
    q.push({s, INF});

    while(q.size()){
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for(ll next : adj[cur]){
            if(parent[next] == -1 && capacity[cur][next]){
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if(next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}
ll maxflow(ll s,ll t,ll n,vector<vector<ll>>& adj,vector<vector<ll>>& capacity){
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;
    while(new_flow = bfs(s,t,parent,adj,capacity)){
        flow += new_flow;
        ll cur = t;
        while(cur != s){
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}
void Node_Disjoint_Paths(vector<pair<ll,ll>> edges,ll n,ll m,ll s,ll d){
	vector<vector<ll>> adj,capacity;
	adj.resize(2*n,vector<ll>());
	capacity.resize(2*n,vector<ll>(2*n,0));
	REP(i,0,m){
		ll x = edges[i].first;
		ll y = edges[i].second;
		if(x == source){
			capacity[x][y] = 1;
		}
		else {
			// outgoing edges are from (x+n)th vertex, incoming edges are to (x)th vertex and there is an edge from (x)th to (x+n)th vertex
			capacity[x+n][y] = 1;
		}
		if(y != dest){
			capacity[y][y+n] = 1;
		}
	}
	REP(i,0,2*n){
		REP(j,0,2*n){
			if(capacity[i][j]) adj[i].push_back(j);
		}
	}
	maxflow(s,d,n,adj,capacity);
}
int main() 
{ 
	ll n,m,source,dest;
	cin>>n>>m>>source>>dest;
	vector<pair<ll,ll>> edges(m);
	source--; dest--;
	REP(i,0,m){
		cin>>edges[i].first>>edges[i].second;
		edges[i].first--;
		edges[i].second--;
	}
	Node_Disjoint_Paths(edges,n,m,source,dest);
	return 0;	
} 