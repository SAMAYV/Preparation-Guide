// For a base 2 ≤ a ≤ n−2, we check if either a^d ≡ 1modn holds or a^((2^r)*d) ≡ −1 modn holds for some 0 ≤ r ≤ s−1.
// If we found a base 'a' which doesn't satisfy any of the above equalities, than we found a witness for the compositeness of n. 
// In this case we have proven that n is not a prime number.

ll binpower(ll a,ll b,ll c){
    if(b == 0)
        return 1 % c;
    ll res = binpow(a, b/2, c);
    if(b % 2){
        return (res * ((res * a) % c)) % c;
    }
    else {
        return (res * res) % c;
    }
} 
bool check_composite(ll n,ll a,ll d,ll s){
    ll x = binpower(a, d, n);
    if(x == 1 || x == n - 1){
        return false;
    }
    REP(r,1,s+1){
        x = (x * x) % n;
        if(x == n - 1){
            return false;
        }
    }
    return true;
}
// returns true if n is probably prime, else returns false.
bool MillerRabin(ll n,ll iter=10){ 
    if(n < 4){
        return n == 2 || n == 3;
    }
    ll s = 0;
    ll d = n - 1;
    while((d & 1) == 0){
        d >>= 1;
        s++;
    }
    REP(i,0,iter){
        ll a = 2 + rand() % (n - 3);
        if(check_composite(n, a, d, s)){
            return false;
        }
    }
    return true;
}

// returns true if n is prime, else returns false.
bool MillerRabin(ll n){ 
    if(n < 2){
        return false;
    }
    ll r = 0;
    ll d = n - 1;
    while((d & 1) == 0){
        d >>= 1;
        r++;
    }
    for(ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a)
            return true;
        if(check_composite(n, a, d, r))
            return false;
    }
    return true;
}

// It turns out, for testing a 32 bit integer it is only necessary to check the first 4 prime bases: 2, 3, 5 and 7. 
// The smallest composite number that fails this test is 3,215,031,751 = 151⋅751⋅28351. 
// And for testing 64 bit integer it is enough to check the first 12 prime bases: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
// Miller showed that it is possible to make the algorithm deterministic by only checking all bases ≤ O((ln(n))^2). 
// Bach later gave a concrete bound, it is only necessary to test all bases a ≤ 2*(ln(n)^2).