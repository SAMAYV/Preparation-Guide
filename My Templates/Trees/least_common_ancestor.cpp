ll depth[maxn], parent[maxn];

void dfs(vector<ll>* edges,ll curr,ll par,ll d){
	depth[curr] = d;
	parent[curr] = par;
	for(auto it : edges[curr]){
		if(it != prev){
			dfs(edges,it,curr,d + 1);
		}
	}
}
void initialize(vector<ll>* edges,ll n,vector<vector<ll>>& arr){
	dfs(edges,1,0,1);
	REP(j,1,n+1){
		arr[0][j] = parent[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = arr[i - 1][j];
			arr[i][j] = arr[i - 1][p];
		}
	}
}
ll LCA(ll x,ll y,vector<vector<ll>>& lca){
	if(depth[x] > depth[y]){
		swap(x,y);
	}
	ll diff = depth[y] - depth[x];
	REP(i,0,60){
		if((diff >> i) & 1){
			y = lca[i][y];
		}
		if(diff == 0) break;
	}
	REPI(i,0,20){
		if(lca[i][x] != lca[i][y]){
			x = lca[i][x];
			y = lca[i][y];
		}
		if(x == y){
			break;
		}
	}
	if(x != y){
		x = lca[0][x];
		y = lca[0][y];
	}
	return x;
}
int main() 
{ 
	ll n;
	cin>>n;
	vector<ll> edges[n+1];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	
	vector<vector<ll>> lca;
	lca.resize(20,vector<ll>(n+1));
	initialize(edges,n,lca);

	ll q;
	cin>>q;
	while(q--){
		ll x,y;
		cin>>x>>y;
		cout<<LCA(x,y,lca)<<endl;
	}
	return 0;	
} 