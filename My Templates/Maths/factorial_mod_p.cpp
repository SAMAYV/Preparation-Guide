// calc n! % p without taking powers of p into account
// O(plogn) time.
ll factmod(ll n,ll p){
    vector<ll> f(p);
    f[0] = 1;
    REP(i,1,p){
        f[i] = (f[i-1] * i) % p;
    }
    ll res = 1;
    while(n > 1){
        if((n/p) % 2)
            res = p - res;
        res = (res * f[n % p]) % p;
        n /= p;
    }
    return res; 
}

// calc power of p in n!
// O(logn)
ll multiplicity_factorial(ll n,ll p){
    ll count = 0;
    do {
        n /= p;
        count += n;
    } while (n);
    return count;
}