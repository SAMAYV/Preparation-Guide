// z[i] is the length of the longest common prefix between s and the suffix of s starting at i.
vector<ll> z_function(string q){
	ll n = q.size();
	vector<ll> Z(n,0);
	Z[0] = 0;
	ll i = 1, r = 0, l = 0;
	while(i < n){
		if(i > r){
			l = i;
			r = i;
			while(r < n && q[r] == q[r-l]){
				r++;
			}
			Z[i] = r - l;
			r--;
		}
		else {
			if(Z[i-l] + i <= r){
				Z[i] = Z[i-l];
			}
			else {
				l = i;
				while(r < n && q[r] == q[r-l]){
					r++;
				}
				Z[i] = r - l;
				r--;
			}
		}
		i++;
	}
	return Z;
}

// find occurrences of s in t
vector<ll> occurrences_of_s_in_t(string s,string t){
	ll m = t.size(),n = s.size();
	string q = s + "$" + t;
	vector<ll> z = z_function(q);
	vector<ll> ans;
	REP(i,n+1,n+m+1){
		if(z[i] == n){
			ans.push_back(i-n-1);
		}
	}
	return ans;
}