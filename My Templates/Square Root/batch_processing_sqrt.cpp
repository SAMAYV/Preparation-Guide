// In an n*n board, initially only cell at position (x,y) is coloured black and others are coloured white. For each query (x,y), determine 
// the nearest distance of white square (x,y) to any black square and then paint (x,y) as black.
// Time Complexity O(n^3)

void multisource_bfs(vector<vector<ll>>& distance,vector<vector<ll>>& mark,ll n){
	queue<pair<ll,ll>> q;
	vector<vector<ll>> visited(n,vector<ll>(n,0));
	REP(i,0,n){
		REP(j,0,n){
			if(mark[i][j]){
				distance[i][j] = 0;
				q.push({i,j});
			}
		}
	}
	while(q.size()){
		ll x = q.top().first;
		ll y = q.top().second;
		q.pop();
		visited[x][y] = 1;
		ll arrx[4] = {-1,1,0,0};
		ll arry[4] = {0,0,1,-1};
		REP(i,0,4){
			ll v1 = x+arrx[i];
			ll v2 = y+arry[i];
			if(v1 >= 0 && v1 < n && v2 >= 0 && v2 < n && !visited[v1][v2]){
				distance[v1][v2] = distance[x][y] + 1;
				q.push({v1,v2});
			}
		}
	}
}

vector<ll> batch_processing(ll n,ll x,ll y,vector<pair<ll,ll>>& queries){
	ll q = queries.size();
	vector<ll> ans(q);
	vector<vector<ll>> mark(n,vector<ll>(n,0));
	mark[x][y] = 1;
	ll i = 0;
	ll block_size = n;
	while(i < q){
		ll j = i;
		vector<vector<ll>> distance(n,vector<ll>(n,1e9));
		multisource_bfs(distance,mark,n);
		vector<pair<ll,ll>> block_dis;
		while(j < q && j < i + block_size){
			ll x = queries[j].first;
			ll y = queries[j].second;
			ll mini = distance[x][y];
			for(auto it:block_size){
				mini = min(mini,abs(it.first - x) + abs(it.second - y));
			}
			block_size.push_back({x,y});
			mark[x][y] = 1;
			ans[j] = mini; 
			j++;
		}
		i = j;
	}
	return ans;
}

int main() 
{  
	ll n,x,y,q;
	cin>>n>>x>>y>>q;
	vector<pair<ll,ll>> queries(q);
	REP(i,0,q){
		cin>>queries[i].first>>queries[i].second;
	}
	vector<ll> ans = batch_processing(n,x,y,queries);
	for(auto it:ans) cout<<it<<" ";
	cout<<endl;
	return 0;	 
} 