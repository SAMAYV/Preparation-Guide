ll const maxn = 1e5 + 5;
ll const lg = 20;
ll P[lg][maxn], stp, cnt, SA[maxn], LCP[maxn];

struct entry {
	ll nr[2], p;
};

entry L[maxn];

bool compare(struct entry a, struct entry b){
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}

// The suffix array will be found on the last row of matrix P.
void constructSA(string& s){
	ll n = s.size();
	REP(i,0,n){
		P[0][i] = s[i] - 'a';
	}
	for(stp = 1, cnt = 1; (cnt >> 1) < n; stp++, cnt <<= 1){
		REP(i,0,n){
			L[i].nr[0] = P[stp-1][i];
			L[i].nr[1] = (i + cnt < n) ? P[stp-1][i + cnt] : -1;
			L[i].p = i;
		}
		sort(L,L+n,compare);
		REP(i,0,n){
			P[stp][L[i].p] = (i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1]) ? P[stp][L[i-1].p] : i;
		}
	}
	REP(i,0,n){
		SA[P[stp][i]] = i;
	}
}

ll lcp(ll x,ll y,string& s)
{
	ll k, ret = 0, n = s.size();
	if(x == y){
		return n - x;	
	} 
	for(k = stp - 1; k >= 0 && x < n && y < n; k--){
		if(P[k][x] == P[k][y]){
			x += (1 << k); 
			y += (1 << k); 
			ret += (1 << k);
		}
	}
	return ret;
}