// https://codeforces.com/contest/118/problem/E

vector<bool> visited;
vector<ll> tin, low;
ll timer = 0,IS_BRIDGE = 0;

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
                IS_BRIDGE++;
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

vector<pair<ll,ll>> ans;
map<pair<ll,ll>,ll> mp;
void dfs_tree(ll curr,ll par,vector<ll>* edges,ll n,vector<ll>& visited){
	visited[curr] = 1;
	for(auto it:edges[curr]){
		if(it == par) continue;
		if(!mp.count({curr,it}) && !mp.count({it,curr})){
			ans.push_back({curr,it});
			mp[{curr,it}] = 1;
		}
		if(!visited[it]){
			dfs_tree(it,curr,edges,n,visited);
		}
	}
}

int main()
{
	i_os;
	ll n,m;
	cin>>n>>m;
	vector<ll> edges[n];
	REP(i,0,m){
		ll x,y;
		cin>>x>>y;
		x--; y--;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	find_bridges(n,edges);
	if(IS_BRIDGE > 0){
		cout<<0<<endl;
		return 0;
	}
	vector<ll> visited(n,0);
	dfs_tree(0,-1,edges,n,visited);
	for(auto it:ans) cout<<it.first+1<<" "<<it.second+1<<endl;
	return 0;
}