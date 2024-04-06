void knuth_optimisation(string s){
	ll n = s.size();
	REP(s,0,n+1){									// s - length(size) of substring
		REP(L,0,n-s+1){								// L - left point
			ll R = L + s - 1;                       // R - right point
	      	if(s < 2){                              
	        	res[L][R] = 0;                      // DP base - nothing to break
	        	mid[L][R] = L;                      // mid is equal to left border
	        	continue;
	      	}
	      	ll mleft = mid[L][R-1];                 // Knuth's trick: getting bounds on M
	      	ll mright = mid[L+1][R];
	      	res[L][R] = 1e18;
	      	REP(M,mleft,mright+1){     				// iterating for M in the bounds only
	        	ll tres = res[L][M] + res[M][R] + (x[R]-x[L]);
	        	if(res[L][R] > tres){               // relax current solution
	          		res[L][R] = tres;
	          		mid[L][R] = M;
	        	}	
			}
		}                    
    }
  	ll answer = res[0][k];
}

// This trick works only for optimization DP over substrings for which optimal middle point depends monotonously on the end points. 
// Let mid[L,R] be the first middle point for (L,R) substring which gives optimal result. 
// It can be proven that mid[L,R-1] <= mid[L,R] <= mid[L+1,R] - this means monotonicity of mid by L and R.
// Applying this optimization reduces time complexity from O(k^3) to O(k^2) 