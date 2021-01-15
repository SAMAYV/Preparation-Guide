void dfs1(ll ind,vector<bool>& visited,stack<ll>& s,vector<ll>* edges){
	visited[ind] = 1;
	for(auto it:edges[ind]){
		if(!visited[it]){
			dfs1(it,visited,s,edges);
		}
	}
	s.push(ind);
}

void dfs2(ll ind,vector<bool>& visited,vector<ll>* edges,vector<ll>& v){
	visited[ind] = 1;
	v.push_back(ind);
	for(auto it:edges[ind]){
		if(!visited[it]){
			dfs2(it,visited,edges,v);
		}
	}
}

vector<vector<ll>> KosaRaju(vector<ll>* edges,vector<ll>* edgesT,ll n){
	vector<vector<ll>> components;
	stack<ll> s;
	vector<bool> visited(n,0);
	REP(i,0,n){
		if(!visited[i]){
			dfs1(i,visited,s,edges);
		}
	}
	vector<bool> visited2(n,0);
	while(s.size()){
		vector<ll> v;
		dfs2(s.top(),visited2,edgesT,v);
		components.push_back(v);
		s.pop();
		while(s.size() > 0 && visited2[s.top()] == 1){
			s.pop();
		}
	}
	return components;
}
int main() 
{ 
	ll v,e;
	cin>>v>>e;
	vector<ll> edges[v],edgesT[v];
	REP(i,0,e){
		ll x,y;
		cin>>x>>y;
		edges[x-1].push_back(y-1);
		edgesT[y-1].push_back(x-1);
	}
	vector<vector<ll>> components = KosaRaju(edges,edgesT,v);  
	return 0;	
} 
