// https://codeforces.com/contest/165/problem/E

ll const maxn = 22;

int main()
{
	i_os;
	ll n;
	cin>>n;
	ll arr[n];
	vector<ll> dp((1 << maxn),-1);
	REP(i,0,n){
		cin>>arr[i];
		dp[arr[i]] = arr[i];
	}
	REP(j,0,maxn){
		vector<ll> dp1;
		dp1 = dp;
		REP(mask,0,(1 << maxn)){
			if((mask >> j) & 1){
				dp[mask] = dp1[(mask^(1 << j))];
			}
			else {
				dp[mask] = max(dp1[mask],dp1[mask^(1 << j)]);
			}		
		}
	}
	REP(i,0,n){
		cout<<dp[arr[i]]<<" ";
	}
	cout<<endl;
	return 0;
}