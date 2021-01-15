void Prim(ll n,vector<pair<ll,ll>>* edges){
	priority_queue<pair<ll,ll>> pq;
	vector<ll> parent(n,-1);
	vector<ll> distance(n,1e9);
	vector<bool> visited(n,0);

	distance[0] = 0;
	parent[0] = 0;
	pq.push({0,0});

	while(pq.size()){
		ll ver = pq.top().second;
		pq.pop();
		if(visited[ver]) continue;
		for(auto it : edges[ver]){
			if(it.second < distance[it.first]){
				distance[it.first] = it.second;
				parent[it.first] = ver;
				pq.push({-distance[it.first],it.first});
			}
		}
		visited[ver] = 1;
	}

	REP(i,1,n){
		cout<<i+1<<" "<<parent[i]+1<<" "<<distance[i]<<endl;
	}
	cout<<endl;
}
int main() 
{ 
	ll n,e;
	cin>>n>>e;
	vector<pair<ll,ll>> edges[n];
	REP(i,0,e){
		ll x,y,wt;
		cin>>x>>y>>wt;
		edges[x-1].push_back({y-1,wt});
		edges[y-1].push_back({x-1,wt});
	}
	Prim(n,edges);
	return 0;	
} 
