// https://www.spoj.com/problems/DISUBSTR/
ll distinct_substrings(string s){
	s.push_back('$');
	ll n = s.size();
	constructSA();
	computeLCP();
	ll ans = 0;
	REP(i,1,n){
		ans += n - SA[i] - 1;
		ans -= LCP[i];
	}
	return ans;	
}

// https://www.spoj.com/problems/LCS/
ll longest_common_substring(string s,string b){
    ll n1 = s.size();
    s.push_back('$');
    s += b;
    s.push_back('#');
	n = s.size();
	constructSA();
	computeLCP();

	ll ans = 0;
	REP(i,1,n){
		if((SA[i] > n1 && SA[i-1] < n1) || (SA[i] < n1 && SA[i-1] > n1)){
			ans = max(ans,LCP[i]);
		}
	}
	return ans;
}

// https://www.spoj.com/problems/SUBLEX/
string kth_lexicographical_distinct_substring(string s,ll k){
	s.push_back('$');
	n = s.size();
	constructSA();
	computeLCP();
	
	// stores number of distinct substrings till SA[i]
	vector<ll> distinct(n,0);
	REP(i,1,n){
		distinct[i] = distinct[i-1] + n - SA[i] - 1 - LCP[i];
	}
	ll a = upper_bound(distinct.begin(),distinct.end(),k) - distinct.begin() - 1;
	if(a-1 >= 0){
		k = k - distinct[a-1];
	}
	return s.substr(SA[a],k+LCP[a]);
}

