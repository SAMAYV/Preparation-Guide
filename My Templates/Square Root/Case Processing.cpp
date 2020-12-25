ll dikstra(vector<pair<ll,ll>>* vt,vector<pair<ll,ll>>* edges,char arr,ll n,ll y){

	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>> pq;
	ll distance[n];
	REP(i,1,n) distance[i] = 1e9;

	REP(i,0,vt[arr - 'A'].size()){
		pair<ll,ll> p = vt[arr - 'A'][i];
		distance[y*(p.first-1) + p.second] = 0;
		pq.push({0,y*(p.first-1) + p.second});
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
			if(distance[it.first] == 0){
				return distance[ver] + it.second;
			}
			else if(distance[ver] + it.second < distance[it.first]){
				distance[it.first] = distance[ver] + it.second;
				pq.push({-distance[it.first],it.first});
			}
		}
		visited[ver] = 1;
	}
	return 1e9;
}
int main() 
{ 
	ll n;
	cin>>n;

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
	unordered_map<char,ll> um;
	vector<pair<ll,ll>> vt[n*n + 1];

	REP(i,0,n){
		REP(j,1,n+1){
			char x;
			cin>>x;
			vt[x - 'A'].push_back({i+1,j});
			um[x]++;
		}
	}
	ll mini = 1e9;
	char ch = ' ';
	for(auto it:um){
		if(it.second >= n){
			ll p = dikstra(vt,edges,it.first,n*n + 1,n);
			if(p < mini){
				ch = it.first;
			}
			mini = min(mini,p);
		}
		else {
			ll mt = 1e9;
			REP(i,0,vt[it.first - 'A'].size()){
				REP(j,i+1,vt[it.first - 'A'].size()){
					pair<ll,ll> p1 = vt[it.first - 'A'][i];
					pair<ll,ll> p2 = vt[it.first - 'A'][j];
					mt = min(mt,abs(p1.first - p2.first) + abs(p1.second - p2.second));
				}	
			}
			if(mt < mini)
				ch = it.first;
			mini = min(mini,mt);
		}
	}
	cout<<ch<<" "<<mini<<endl;
	return 0;	 
} 