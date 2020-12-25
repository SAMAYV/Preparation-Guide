void dikstra(ll* distance,vector<pair<ll,ll>>* edges,ll* arr,ll n){

	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>> pq;

	REP(i,1,n){
		if(arr[i]){
			distance[i] = 0;
			pq.push({0,i});
		} 
		else {
			distance[i] = 1e9;
		}
	}
	bool visited[n];
	REP(i,1,n) visited[i] = 0;

	while(pq.size()){
		ll ver = pq.top().second;
		pq.pop();
		if(visited[ver]) 
			continue;
		for(auto it : edges[ver]){
			if(visited[it.second])
				continue;
			if(distance[ver] + it.second < distance[it.first]){
				distance[it.first] = distance[ver] + it.second;
				pq.push({-distance[it.first],it.first});
			}
		}
		visited[ver] = 1;
	}
}
int main() 
{ 
	ll n,x,y;
	cin>>n>>x>>y;

	ll* arr = new ll[n*n + 1]();
	arr[n*x + y] = 1;

	vector<pair<ll,ll>> edges[n*n + 1];
	REP(i,0,n){
		REP(j,1,n + 1){
			if(j + 1 <= n)
				edges[i*n + j].push_back({i*n + j + 1,1});
			if(i + 1 <= n-1)
				edges[i*n + j].push_back({(i+1)*n + j,1});
			if(i - 1 >= 0)
				edges[i*n + j].push_back({(i-1)*n + j,1});
			if(j - 1 >= 1)
				edges[i*n + j].push_back({i*n + j - 1,1});
		}
	}

	ll q;
	cin>>q;
	vector<ll> ans;
	ll count = 0;
	while(count < q){
		ll val;
		if(q - count < sqrt(q)){
			val = q - count;
		}
		else {
			val = sqrt(q);
		}
		vector<pair<ll,ll>> temp;
		ll* distance = new ll[n*n + 1];
		REP(i,1,n*n + 1) distance[i] = 1e9;

		dikstra(distance,edges,arr,n*n + 1);
		
		REP(i,0,val){
			ll x,y;
			cin>>x>>y;

			ll mini = distance[x*n + y];

			for(auto it:temp){
				mini = min(mini,abs(it.first - x) + abs(it.second - y));
			}
			temp.push_back({x,y});
			arr[n*x + y] = 1;
			ans.push_back(mini);
		}
		count += val;
	}
	REP(i,0,ans.size()){
		cout<<ans[i]<<" ";
	}
	cout<<endl;

	return 0;	 
} 