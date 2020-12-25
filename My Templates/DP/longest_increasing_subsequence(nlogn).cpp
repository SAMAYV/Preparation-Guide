int main()
{
	ll n;
	cin>>n;
	ll arr[n];
	REP(i,0,n) cin>>arr[i];

	// L stores at ith index the minimum ending index of increasing subsequence of length i+1 
	// Lv stores at ith index the minimum ending index value of increasing subsequence of length i+1
	// Lv will be increasing 

	ll L[n],R[n],Lv[n];

	REP(i,0,n){
		L[i] = 1e18;
		Lv[i] = 1e18;
		R[i] = -1;
	}

	L[0] = 0;
	Lv[0] = arr[0];

	REP(i,1,n){
		ll p = upper_bound(Lv,Lv+n,arr[i]) - Lv;
		Lv[p] = arr[i];
		L[p] = i;
		if(p > 0)
			R[i] = L[p-1];
		else 
			R[i] = -1;
	}

	ll length = 1;
	REP(i,0,n){
		if(L[i] != 1e18) length = i+1;
	}
	cout<<length<<endl;

	vector<ll> v;
	ll curr = L[length-1];
	while(curr > -1){
		v.push_back(curr);
		curr = R[curr];
	}
	
	reverse(v.begin(),v.end());
	for(auto it:v) cout<<it<<" ";
	cout<<endl;
	return 0;
}