void dfs(vector<ll>& parent,vector<ll>* edges,ll curr,ll prev){
	for(auto it : edges[curr]){
		if(it == prev)
			continue;
		parent[it] = curr;
		dfs(parent,edges,it,curr);
	}
}

void precompute(vector<vector<ll>>& arr,vector<ll>* edges,vector<ll>& parent,ll n){
	arr.resize(20,vector<ll>(n+1));
	REP(j,1,n+1){
		arr[0][j] = parent[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = arr[i - 1][j];
			arr[i][j] = arr[i - 1][p];
		}
	}
}
ll Kth_ancestor(vector<vector<ll>>& arr,ll x,ll k){
	ll ans = x;
	REP(i,0,60){
		if((k >> i) & 1){
			ans = arr[i][ans];
		}
	}
	return ans;
}

int main() 
{ 
	ll n;
	cin>>n;
	vector<ll> edges[n+1];
	REP(i,0,n-1){
		ll x,y;
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	vector<ll> parent(n+1,0);
	dfs(parent,edges,1,0);
	vector<vector<ll>> arr;
	precompute(arr,edges,parent,n);
	
	ll q;
	cin>>q;
	while(q--){
		ll x,k;
		cin>>x>>k;
		cout<<Kth_ancestor(arr,x,k)<<endl;
	}
	return 0;	
} 