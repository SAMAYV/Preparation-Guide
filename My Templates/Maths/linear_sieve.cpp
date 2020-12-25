void linear_sieve(vector<ll>& lp,ll N){
	lp.resize(N+1,0);
	vector<ll> pr;
	// minimum prime factor lp[i] for every number i
	REP(i,2,n+1){
	    if(lp[i] == 0){
	        lp[i] = i;
	        pr.push_back(i);
	    }
	    for(ll j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j){
	        lp[i * pr[j]] = pr[j];
	    }
	}
}
