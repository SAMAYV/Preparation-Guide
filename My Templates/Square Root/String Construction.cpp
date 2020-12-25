int main() 
{ 
	ll m;
	cin>>m;
	unordered_map<string,ll> um;
	REP(i,0,m){
		string x;
		cin>>x;
		um[x] = 1;
	}	
	string s;
	cin>>s;

	ll dp[s.size() + 1] = {0};
	dp[0] = 1;
	REP(i,0,s.size()){
		string k = "";
		ll curr = i;
		ll j = 1;
		while(j <= sqrt(m) + 1 && curr >= 0){
			k = s.substr(curr,1) + k;
			if(um.count(k)){
				dp[i+1] += dp[curr];
			}
			curr--;
			j++;
		}
	}
	REP(i,1,s.size() + 1) cout<<dp[i]<<" ";
	cout<<endl;
	return 0;	
} 