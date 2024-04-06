// https://www.codechef.com/problems/RRTREGAM
void dfs(ll curr,ll par,ll* depth,vector<ll>* edges,ll d){
	depth[curr] = d;
	for(auto it:edges[curr]){
		if(it != par){
			dfs(it,curr,depth,edges,d+1);
		}
	}
}
int main()
{
	i_os;
    ll n;
    cin>>n;
    ll arr[n+1];
    REP(i,1,n+1) cin>>arr[i];
    vector<ll> edges[n+1];
    REP(i,0,n-1){
    	ll x,y;
    	cin>>x>>y;
    	edges[x].push_back(y);
    	edges[y].push_back(x);
    }
    ll depth[n+1];
    dfs(1,0,depth,edges,0);
    ll ans = 0;
    REP(i,1,n+1){
    	arr[i] /= 2;
    	if(arr[i] % 2){
    		ans ^= depth[i];
    	}
    }
    if(ans) cout<<"Rachel\n";
    else cout<<"Ross\n";
    return 0;
}