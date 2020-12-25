void dfs(ll parent[],vector<ll>* edges,ll curr,ll prev,ll depth[],ll d){
	depth[curr] = d;
	for(auto it : edges[curr]){
		if(it == prev)
			continue;
		parent[it] = curr;
		dfs(parent,edges,it,curr,depth,d + 1);
	}
}

void initialize(vector<ll>* edges,ll n,vector<ll>& depth,vector<ll>& parent,vector<vector<ll>>& arr){
	dfs(parent,edges,1,0,depth,1);
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
ll LCA(ll x,ll y,vector<vector<ll>>& arr,ll depth[]){
	if(depth[x] > depth[y]){
		ll diff = depth[x] - depth[y]; 
		REP(i,0,60){
			if((diff >> i) & 1){
				x = arr[i][x];
			}
		}
	}
	else if(depth[x] < depth[y]){
		ll diff = depth[y] - depth[x];
		REP(i,0,60){
			if((diff >> i) & 1){
				y = arr[i][y];
			}
		} 
	}
	REPI(i,0,20){
		if(arr[i][x] != arr[i][y]){
			x = arr[i][x];
			y = arr[i][y];
		}
		if(x == y){
			break;
		}
	}
	if(x != y){
		x = arr[0][x];
		y = arr[0][y];
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
	vector<vector<ll>> arr;
	arr.resize(20,vector<ll>(n+1));
	vector<ll> depth(n+1,0);
	vector<ll> parent(n+1,-1);
	parent[1] = 0;
	initialize(edges,n,depth,parent,arr);

	ll q;
	cin>>q;
	while(q--){
		ll x,y;
		cin>>x>>y;
		cout<<LCA(x,y,arr,depth)<<endl;
	}
	return 0;	
} 