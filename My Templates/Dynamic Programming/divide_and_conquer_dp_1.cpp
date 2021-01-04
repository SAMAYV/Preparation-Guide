// Refer to: https://codeforces.com/contest/834/problem/D

ll const maxn = 35005;
ll const maxk = 55;

ll dp[maxk][maxn];

// online calculation of calc...that's why cache is maintained
ll calc(ll l,ll r){
	if(l > r) return 0;
}

unordered_map<ll,ll> queries[maxn];
unordered_map<ll,ll>::iterator it;
ll to, diff;

void divide(ll u,ll l,ll r,ll L,ll R)
{
	if(l > r) return;
	ll m = (l + r) / 2, opt = L;
	auto &layer = dp[u - 1];
	auto &curr = dp[u][m];
	auto &cache = queries[m];

	for(ll i = L; i <= min(m - 1, R); i++)
	{
		to = layer[i];
		it = cache.find(i + 1);
		if(it != cache.end()){
			diff = it->second;
		}
		else {
			diff = calc(i + 1, m);
		}
		if(to + diff > curr){
			curr = to + diff, opt = i;
		}
		if(it == cache.end()){
			cache[i + 1] = diff;
		}
	}
	divide(u, l, m - 1, L, opt);
	divide(u, m + 1, r, opt, R);
}

void solve(ll n,ll k)
{
	// calc for state 1
    set<ll> s;
    REP(i,1,n+1){
    	s.insert(arr[i]);
    	dp[1][i] = s.size();
    }
    REP(i,2,k+1){
        divide(i,1,n,0,n);
    }
    cout<<dp[k][n]<<endl;
}