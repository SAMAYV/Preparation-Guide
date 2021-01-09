oid dfs3(vector<bool>& visited,ll ind,vector<ll>* edges,vector<ll>& vt){
	visited[ind] = 1;
	for(auto it:edges[ind]){
		if(!visited[it]){
			dfs3(visited,it,edges,vt);
		}
	}
	vt.push_back(ind);
}

vector<ll> topological(vector<ll>* edges,ll n){
	vector<ll> vt;
	vector<bool> visi(n,0);
	REP(i,0,n){
		if(!visi[i]){
			dfs3(visi,i,edges,vt);
		}
	}
	reverse(vt.begin(),vt.end());
	return vt;
}
int main() 
{ 
	ll n,e;
	cin>>n>>e;
	vector<ll> edges[n];
	REP(i,0,e){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
	}
	vector<ll> v = topological(edges,n);
	return 0;	
} 
