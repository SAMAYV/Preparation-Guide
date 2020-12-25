void phi_1_to_n(ll n){
    vector<ll> phi(n + 1);
    REP(i,0,n+1){
        phi[i] = i - 1;
    }
    REP(i,2,n+1){
        for(ll j = 2*i; j <= n; j += i){
        	phi[j] -= phi[i];
        }
    }
}
// This interesting property was established by Gauss: (d divides n) ∑ ϕ(d) = n. Here the sum is over all positive divisors d of n.
// As immediate consequence we also get the equivalence: a^n ≡ a^(n*modϕ(m))(modm)
// This allows computing (x^n)modm for very big n, especially if n is the result of another computation, as it allows to compute n under a modulo.

// There is a less known version of the last equivalence, that allows computing (x^n)modm efficiently for not coprime x and m. 
// For arbitrary x,m and n ≥ log2m: x^n ≡ x^(ϕ(m)+[nmodϕ(m)])modm