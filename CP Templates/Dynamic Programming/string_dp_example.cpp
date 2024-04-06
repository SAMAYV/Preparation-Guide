// https://codeforces.com/contest/1303/problem/E

vector<vector<ll>> compute,dp;
bool calc(string& a,string& b){
    dp.clear();
	dp.resize(a.size()+1,vector<ll>(b.size()+1,1e9));
	dp[0][0] = 0;
	REP(i,0,a.size()+1){
		REP(j,0,b.size()+1){
			if(dp[i][j] == 1e9) continue;
			ll p = dp[i][j];
			if(i < a.size() && compute[p][a[i]-'a'] < 1e9){
				dp[i+1][j] = min(dp[i+1][j],compute[p][a[i]-'a'] + 1);
			}
			if(j < b.size() && compute[p][b[j]-'a'] < 1e9){
				dp[i][j+1] = min(dp[i][j+1],compute[p][b[j]-'a'] + 1);
			}
		}
	}
	return dp[a.size()][b.size()] < 1e9;
}

int main()
{
	i_os;
	ll t;
	cin>>t;
	while(t--){
		string s1,s2;
		cin>>s1>>s2;
		compute.clear();
		compute.resize(s1.size()+1,vector<ll>(26,1e9));
		REPI(i,0,s1.size()){
			compute[i] = compute[i+1];
			compute[i][s1[i]-'a'] = i;
		}
		bool f = 0;
		REP(i,0,s2.size()+1){
		    string a = s2.substr(0,i);
		    string b = s2.substr(i);
			if(calc(a,b)){
				f = 1;
				break;
			}
		}
		if(f) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
