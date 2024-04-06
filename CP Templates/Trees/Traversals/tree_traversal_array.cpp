void dfs(vector<ll>& parent,vector<ll>* edges,ll curr,ll prev,vector<ll>& v){
	v.push_back(curr + 1);
	for(auto it : edges[curr]){
		if(it == prev)
			continue;
		parent[it] = curr;
		dfs(parent,edges,it,curr,v);
	}
}
// A tree traversal array contains the nodes of a rooted tree in the order in which a depth-first search from the root node visits them.
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
	vector<ll> parent(n,-1);
	vector<ll> traversal;
	dfs(parent,edges,0,-1,traversal);
	return 0;	
} 