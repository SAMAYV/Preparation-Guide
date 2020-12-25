// In modular arithmetic, a number g is called a primitive root modulo n if every number coprime to n is congruent to a power of g modulo n. 
// Mathematically, g is a primitive root modulo n if and only if for any integer a such that gcd(a,n)=1, there exists an integer k such that:
// g^k ≡ a(modn). k is then called the index or discrete logarithm of a to the base g modulo n. g is also called the generator of the 
// multiplicative group of integers modulo n.
ll powmod(ll a,ll b,ll p){
    ll res = 1;
    while(b){
        if(b & 1){
            res = (res * a) % p;  
            --b;
        }
        else {
            a = (a * a) % p; 
            b >>= 1;
        }
    }
    return res;
}
// The following code assumes that the modulo p is a prime number. To make it works for any value of p, we must add calculation of ϕ(p).
ll generator(ll p){
    vector<ll> fact;
    ll phi = p-1, n = p-1;
    for(ll i=2; i*i<=n; ++i){
        if(n % i == 0){
            fact.push_back(i);
            while(n % i == 0)
                n /= i;
        }
    }
    if(n > 1){
        fact.push_back(n);
    }
    REP(res,2,p+1){
        bool ok = 1;
        for(ll i=0; i<fact.size() && ok; ++i){
            ok &= (powmod(res, phi / fact[i], p) != 1);
        }
        if(ok) return res;
    }
    return -1;
}
// Running time of this algorithm is O(Ans⋅logϕ(n)⋅logn) (assume that ϕ(n) has logϕ(n) divisors).
// Let g be a primitive root modulo n. Then we can show that the smallest number k for which gk≡1(modn) is equal ϕ(n).
// Moreover, the reverse is also true, and this fact will be used in this article to find a primitive root.
// Furthermore, the number of primitive roots modulo n, if there are any, is equal to ϕ(ϕ(n)).
