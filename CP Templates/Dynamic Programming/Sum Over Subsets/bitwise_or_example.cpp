// https://atcoder.jp/contests/arc100/tasks/arc100_c

int main()
{
	i_os;
	ll n;
	cin>>n;
	ll arr[(1 << n)];
	multiset<ll> dp[(1 << n)];
	REP(i,0,(1 << n)){
		cin>>arr[i];
		dp[i].insert(arr[i]);
	}
	REP(i,0,n){
		REP(mask,0,(1 << n)){
			if((mask >> i) & 1){
				for(auto it:dp[(mask^(1 << i))]){
					dp[mask].insert(it);
				} 
				while(dp[mask].size() > 2){
					dp[mask].erase(dp[mask].begin());
				}
			}
		}
	}
	ll pref = 0;
	REP(i,1,(1 << n)){
		cout<<max(pref,*dp[i].begin() + *dp[i].rbegin())<<endl;
		pref = max(pref,*dp[i].begin() + *dp[i].rbegin());
	}
	return 0;
}