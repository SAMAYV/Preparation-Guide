//  Given a fixed array A of 2N integers, we need to calculate ∀ x function F(x) = Sum of all A[i] such that x&i = i, i.e., i is a subset of x.

// Time: O(3^N)
// iterate over all the masks

REP(mask,0,(1 << n))
{
	F[mask] = A[0];    
    // iterate over all the subsets of the mask
    for(ll i = mask; i > 0; i = (i-1) & mask){
    	F[mask] += A[i];
    }
}

// Time: O(N*2^N)
// iterative version

REP(i,0,n){	
	REP(mask,0,(1 << n)){
		dp[mask][-1] = A[mask];	
		if(mask & (1 << i)){
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1 << i)][i-1];
		}
		else {
			dp[mask][i] = dp[mask][i-1];
		}
	}
}
F[mask] = dp[mask][n-1];

// memory optimized, super easy to code.

REP(i,0,(1 << n)){
	F[i] = A[i];
}
REP(i,0,n){
	vector<ll> trans;
	trans = F;
	REP(mask,0,(1 << n)){
		if(mask & (1 << i)){
			F[mask] += trans[mask^(1 << i)];
		}
	}
} 
