ll g(ll n){
    return n ^ (n >> 1);
}

ll rev_g(ll g){
	ll n = 0;
  	for(; g; g >>= 1)
    	n ^= g;
  	return n;
}