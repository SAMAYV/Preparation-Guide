// Given a string s of length n and a set of strings D whose total length is m, consider
// the problem of counting the number of ways s can be formed as a concatenation of strings in D.

ll power(ll a,ll n,ll c){
    if(n == 0) return 1 % c;
    ll s = power(a,n/2,c);
    s = (s * s) % c;
    if(n % 2) s = (s * a) % c;
    return s;
}

ll string_construction(string s,vector<string>& arr){
	ll n = s.size();
	ll m = arr.size();
	ll sum = 0;
	
	// store all distinct lengths from arr
	set<ll> distinct_len;
	for(auto it:arr){
		sum += it.size();
		distinct_len.insert(it.size());	
	} 

	// calculate prefix hash for s
	ll p = 31;
	ll mod = 1e9 + 7;
	ll temp[n+sum+1];
	ll hash_s[n+1] = {0};
	ll modinv[n+1];
	temp[0] = 1;
	modinv[0] = 1;
	REP(i,1,n+sum+1){
		temp[i] = (temp[i-1]*p) % mod;
	}
	REP(i,1,n+1){
		hash_s[i] = (hash_s[i-1] + (temp[i]*(s[i-1]-'a'+1)) % mod) % mod;
	}
	REP(i,1,n+1){
		ll p1 = power(p,i,mod);
		modinv[i] = power(p1,mod-2,mod);
	}
	
	// storing the hash values for m strings
	// key is length of ith string and it will store all the hashes for this length of strings
	map<ll,set<ll>> hash_values;
	REP(i,0,m){
		ll val = 0;
		REP(j,0,arr[i].size()){
			val = (val + ((arr[i][j]-'a'+1)*temp[j]) % mod) % mod;
		}
		hash_values[arr[i].size()].insert(val);
	}

	ll dp[n + 1] = {0};
	dp[0] = 1;
	REP(i,0,n+1){
		for(auto it:distinct_len){
			if(it+i <= n){
				// calculating hash for substring from i+1...i+it
				ll p = (hash_s[it+i] - hash_s[i] + mod) % mod;
				// dividing by p^i
				p = (p*modinv[i]) % mod;
				if(hash_values[it].find(p) != hash_values[it].end()){
					dp[it+i] += dp[i];
				}
			}
		}
	}
	return dp[n];
}
int main() 
{ 
	string s;
	cin>>s;
	ll m;
	cin>>m;
	vector<string> arr(m);
	REP(i,0,m){
		cin>>arr[i];
	}	
	cout<<string_construction(s,arr)<<endl;
	return 0;	
} 