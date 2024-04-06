vector<ll> prefix_function(string s) 
{
    ll n = s.length();
    vector<ll> pi(n,0);
    REP(i,1,n){
        ll j = pi[i-1];
        while(j > 0 && s[i] != s[j]){
            j = pi[j-1];
        }
        if(s[i] == s[j]){
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

// Given a string s of length n. We want to find the shortest "compressed" representation of the string, i.e. we want to find a string t 
// of smallest length such that s can be represented as a concatenation of one or more copies of t.
ll string_compression(string s){
	vector<ll> pi = prefix_function(s);
	ll n = s.size();
	ll k = n - pi[n-1];	
	if(n % k == 0) return s.substr(0, k);
	else return n;
}