void dfs(vector<ll>& parent,vector<ll>* edges,ll curr,ll prev,vector<ll>& depth,ll d){
	depth[curr] = d;
	for(auto it : edges[curr]){
		if(it == prev)
			continue;
		parent[it] = curr;
		dfs(parent,edges,it,curr,depth,d+1);	
	} 
}
void depth_and_diameter(ll n,vector<ll>* edges){
	vector<ll> parent(n,-1);
	vector<ll> depth1(n,0);
	vector<ll> depth2(n,0);
	dfs(parent,edges,0,-1,depth1,0);
	
	ll maxi = 0;
	REP(i,0,n){
		if(depth1[maxi] < depth1[i])
			maxi = i;
	}
	dfs(parent,edges,maxi,-1,depth2,0);
	
	maxi = 0;
	REP(i,0,n){
		if(depth2[maxi] < depth2[i])
			maxi = i;
	}
	cout<<depth2[maxi]<<endl;
}
int main() 
{ 
	ll n;
	cin>>n;
	vector<ll> edges[n];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edges[y-1].push_back(x-1);
	}
	depth_and_diameter(n,edges);
	return 0;	
} 
