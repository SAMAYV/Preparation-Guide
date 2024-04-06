// https://www.codechef.com/IPC15P3B/problems/SROADS

vector<bool> visited;
vector<ll> tin, low;
ll timer = 0;

void dfs(ll v,vector<ll>* edges,set<ll>* tree,ll p = -1){
    visited[v] = 1;
    tin[v] = low[v] = timer++;
    for(auto to:edges[v]){
        if(to == p) continue;
        if(visited[to]){
            low[v] = min(low[v], tin[to]);
        } 
        else {
            dfs(to,edges,tree,v);
            if(low[to] > tin[v]){
                // IS_BRIDGE(v, to);
            	tree[v].erase(to);
            	tree[to].erase(v);
            }
            low[v] = min(low[v], low[to]);
        }
    }
}

ll connected(ll curr,ll par,set<ll>* tree,vector<bool>& vis){
	vis[curr] = 1;
	ll c = 1;
	for(auto it:tree[curr]){
		if(!visited[it] && it != par){
			c += connected(it,curr,tree,vis);
		}
	}
	return c;
}

void find_bridges(ll n,vector<ll>* edges,set<ll>* tree){
    timer = 0;
    visited.assign(n,0);
    tin.assign(n,-1);
    low.assign(n,-1);
    REP(i,0,n){
        if(!visited[i]){
            dfs(i,edges,tree);
        }
    }
    ll ans = 0;
    visited.assign(n,0);
    REP(i,0,n){
    	if(!visited[i]){
    		ll p = connected(i,-1,tree,visited);
    		ans += (p*(p-1))/2;
    	}
    }
    cout<<ans<<endl;
}

int main()
{
	i_os;
	ll n,m;
	cin>>n>>m;
	vector<ll> edges[n+1];
	set<ll> tree[n+1];
	REP(i,0,m){
		ll x,y;
		cin>>x>>y;
		x--; y--;
		edges[x].push_back(y);
		edges[y].push_back(x);
		tree[x].insert(y);
		tree[y].insert(x);
	}	
	find_bridges(n,edges,tree);
	return 0;
}
