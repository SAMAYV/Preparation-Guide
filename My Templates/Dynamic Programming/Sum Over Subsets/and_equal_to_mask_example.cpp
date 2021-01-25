// https://codeforces.com/problemset/problem/449/D

ll const maxn = 20;
int mod = 1e9 + 7;

int main()
{
	i_os;
	ll n;
	cin>>n;
	ll arr[n];
	vector<ll> dp((1 << maxn),0);
	REP(i,0,n){
		cin>>arr[i];
		dp[arr[i]]++;
	}	
	REP(i,0,maxn){
		vector<ll> dp1;
		dp1 = dp;
		REP(mask,0,(1 << maxn)){
			if((mask >> i) & 1){
				dp[mask] = dp1[mask];
			}
			else {
				dp[mask] = dp1[mask] + dp1[mask^(1 << i)];
			}
		}
	}
	ll ans = 0;
	REP(mask,0,(1 << maxn)){
		ll set = 0;
		REP(i,0,maxn){
			if((mask >> i) & 1){
				set++;
			}
		}
		if(set % 2){
			ans -= power(2,dp[mask],mod);
			ans += mod;
			ans++;
		}
		else {
			ans += power(2,dp[mask],mod);
			ans--;
		}
		ans += mod;
		ans %= mod;
	}
	cout<<ans<<endl;
	return 0;
}