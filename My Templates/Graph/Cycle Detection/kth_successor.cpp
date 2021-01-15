void pre_compute(ll n,vector<vector<ll>>& arr,ll succ[]){
	arr.resize(20,vector<ll>(n));
	REP(j,1,n+1){
		arr[0][j] = succ[j];
	}
	REP(i,1,20){
		REP(j,1,n+1){
			ll p = arr[i - 1][j];
			arr[i][j] = arr[i - 1][p];
		}
	}
}
ll kth_successor(ll x,ll k,vector<vector<ll>>& arr){
	ll p = x;
	REP(i,0,60){
		if((k >> i) & 1){
			p = arr[i][p];
		}
	}
	return p;
}
int main() 
{ 
	ll n;
	cin>>n;
	// each edge is from (x to succ(x))
	ll succ[n+1];
	REP(i,1,n+1){
		cin>>succ[i];
	}
	vector<vector<ll>> arr;
	pre_compute(n,arr,succ);
	
	ll q;
	cin>>q;
	while(q--){
		ll x,k;
		cin>>x>>k;
		cout<<kth_successor(x,k,arr)<<endl;
	}
	return 0;	
} 
