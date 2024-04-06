// https://codeforces.com/contest/768/problem/E
map<pair<ll,ll>,ll> grundy;
 
ll memo(ll n,ll mask,ll prev = 62){
	REP(i,n,prev){
		if((mask >> i) & 1LL) 
			mask = (mask ^ (1LL << i));
	}
	if(grundy.count({n,mask})) 
		return grundy[{n,mask}];
	ll mark[62] = {0};
	REP(i,0,n){
		if(((mask >> i) & 1LL) == 1LL){
			mark[memo(n-i-1,(mask ^ (1LL << i)),n)] = 1;
		}
	}
	ll curr = 0;
	while(mark[curr]) curr++;
	grundy[{n,mask}] = curr;
	return curr;
}
int main()
{
	ll n;
	cin>>n;
	ll arr[n];
	REP(i,0,n){
		cin>>arr[i];
	}
	ll ans[61] = {0};
	grundy[{0,0}] = 0;
	REP(i,1,61){
		ans[i] = memo(i,(1LL << i) - 1LL);
	}
	ll val = 0;
	REP(i,0,n) val ^= ans[arr[i]];
	if(val) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
    return 0;
}