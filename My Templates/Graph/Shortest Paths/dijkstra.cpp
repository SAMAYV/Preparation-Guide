void dijkstra(ll n,vector<pair<ll,ll>>* edges,ll st){
	priority_queue<pair<ll,ll>> pq;
	vector<ll> distance(n,1e9);
	distance[st] = 0;
	vector<bool> visited(n,0);
	pq.push({0,st});
	while(pq.size()){
		ll ver = pq.top().second;
		pq.pop();
		if(visited[ver]) continue;
		visited[ver] = 1;
		for(auto it:edges[ver]){
			if(distance[ver] + it.second < distance[it.first]){
				distance[it.first] = distance[ver] + it.second;
				pq.push({-distance[it.first],it.first});
			}
		}
	}
	REP(i,0,n){
		cout<<distance[i]<<" ";
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
	dijkstra(n,edges,0);
	return 0;	
} 
