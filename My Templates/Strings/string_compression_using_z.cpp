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

// Given a string s of length n. We want to find the shortest "compressed" representation of the string, i.e. we want to find a string t 
// of smallest length such that s can be represented as a concatenation of one or more copies of t.
ll string_compression(string s){
	vector<ll> z = z_function(s);
	ll n = s.size();
	REP(i,1,n){
		if(n % i == 0 && z[i] + i == n){
			return i;
		}
	}
	return n;
}