void bfs(vector<ll>* edges,ll n){
	queue<ll> q;
	vector<bool> visited(n,0);
	vector<ll> distance(n,1e9);
	vector<ll> parent(n,-1);
	
	parent[0] = 0;
	q.push(0);
	visited[0] = 1;
	distance[0] = 0;

	while(q.size()){
		ll curr = q.front();
		q.pop();
		for(auto u : edges[curr]){
			if(!visited[u]){
				visited[u] = 1;
				distance[u] = distance[curr] + 1;
				q.push(u);
				parent[u] = curr;
			}
		}
	}
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
		edges[y-1].push_back(x-1);
	}
	bfs(edges,n);
	return 0;	
} 
