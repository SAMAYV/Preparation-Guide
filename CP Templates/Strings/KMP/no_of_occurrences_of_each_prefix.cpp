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
vector<ll> occurrences_of_each_prefix(string s){
	vector<ll> pi = prefix_function(s);	
	vector<ll> ans(n + 1,0);
	
	// method-1
	REP(i,0,n){
		ll curr = i;
		while(curr > 0){
			ans[pi[curr]]++;
			curr = pi[curr] - 1;
		} 
	}
	REP(i,0,n){
		ans[i]++;	
	} 

	// method-2
	REP(i,0,n){
	    ans[pi[i]]++;
	}
	REPI(i,1,n){
	    ans[pi[i-1]] += ans[i];
	}
	REP(i,0,n+1){
	    ans[i]++;
	}
	return ans;
}

vector<ll> no_of_occurrences_of_each_prefix_of_patt_in_t(string patt,string t){
	string q = patt + "#" + t;
	vector<ll> pi = prefix_function(q);
	ll n = t.size();
	ll m = patt.size();

	// denotes length
	vector<ll> ans(m + 1,0);

	REP(i,m+1,n){
		ll curr = i;
		while(curr > 0){
			ans[pi[curr]]++;
			curr = pi[curr] - 1;
		} 
	}
	return ans;
}