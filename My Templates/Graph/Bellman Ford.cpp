void Bellman(vector<tuple<ll,ll,ll>>& edges,ll n){
	vector<ll> distance(n,1e9);
	distance[0] = 0;
	bool flag = 0;

	REP(i,0,n-1){
		bool f = 0;
		for(auto edge:edges){
			ll a,b,c;
			tie(a,b,c) = edge;
			if(distance[b] > distance[a] + c){
				f = 1;
				distance[b] = distance[a] + c;
			}
		}
		if(i == n-2 && f == 1)
			flag = 1;
	}

	if(flag == 1) cout<<"Graph contains negative cycle"<<endl;
	REP(i,0,n){
		cout<<distance[i]<<" ";
	}
	cout<<'\n';
}
int main() 
{ 
	ll n,e;
	cin>>n>>e;
	vector<tuple<ll,ll,ll>> edges;
	REP(i,0,e){
		ll x,y,wt;
		cin>>x>>y>>wt;
		edges.push_back({x-1,y-1,wt});
		edges.push_back({y-1,x-1,wt});
	}
	Bellman(edges,n);
	return 0;	
} 
