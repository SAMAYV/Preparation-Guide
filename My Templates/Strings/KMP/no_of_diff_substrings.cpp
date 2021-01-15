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

ll no_of_diff_substrings(string s){
	string p;
	ll n = s.size(), ans = 0;
	REP(i,0,n){
		p.push_back(s[i]);
		string k = p;
		reverse(k.begin(),k.end());
		vector<ll> pi = prefix_function(k);
		ll maxi = 0;
		REP(j,0,pi.size()){
			maxi = max(maxi,pi[j]);
		}
		ans += p.size() - maxi;
	}
	return ans;
}
// So for each character appended we can compute the number of new substrings in O(n) times, which gives a time complexity of O(n2) in total
// It is worth noting, that we can also compute the number of different substrings by appending the characters at the beginning, 
// or by deleting characters from the beginning or the end.