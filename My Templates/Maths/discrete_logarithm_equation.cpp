// The discrete logarithm is an integer x satisfying the equation a^x ≡ b(modm) for given integers a, b and m.


// When a and m are relatively prime
// Complexity O(sqrt(m)logm) using using the meet-in-the-middle method as follows:
ll powmod(ll a,ll b,ll m){
    ll res = 1;
    while(b > 0){
        if(b & 1){
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
// Another thing to note is that, if there are multiple arguments p that map to the same value of f1, we only store one such argument. 
// This works in this case because we only want to return one possible solution. If we need to return all possible solutions, 
// we need to change map<int, int> to, say, map<int, vector<int>>. We also need to change the second step accordingly.
ll solve(ll a,ll b,ll m){
    if(a == 0){
        return b == 0 ? 1 : -1;
    }
    a %= m, b %= m;
    ll n = sqrt(m) + 1;
    map<ll,ll> vals;
    REP(p,1,n+1){
        vals[powmod(a, p*n, m)] = p;
    }
    REP(q,0,n+1){
        ll cur = (powmod(a, q, m) * b) % m;
        if(vals.count(cur)){
            ll ans = vals[cur] * n - q;
            return ans;
        }
    }
    return -1;
}

// Improved Implementation
// Returns minimum x for which a ^ x % m = b % m, a and m are coprime.
// The complexity is O(sqrt(m)) using unordered_map.
ll solve(ll a,ll b,ll m){
    a %= m, b %= m;
    ll n = sqrt(m) + 1;

    ll an = 1;
    REP(i,0,n+1){
        an = (an * a) % m;
    }
    unordered_map<ll,ll> vals;
    for(ll q = 0, cur = b; q <= n; ++q){
        vals[cur] = q;
        cur = (cur * a) % m;
    }
    for(ll p = 1, cur = 1; p <= n; ++p){
        cur = (cur * an) % m;
        if(vals.count(cur)){
            ll ans = n*p - vals[cur];
            return ans;
        }
    }
    return -1;
}

// When a and m are not coprime
// The baby-step giant-step algorithm can be easily extended to solve k*(a^x) ≡ b(modm) for x.
// Returns minimum x for which a ^ x % m = b % m.
ll solve(ll a,ll b,ll m){
    a %= m, b %= m;
    ll k = 1, add = 0, g;
    while((g = gcd(a, m)) > 1){
        if(b == k)
            return add;
        if(b % g)
            return -1;
        b /= g, m /= g, ++add;
        k = (k * a / g) % m;
    }

    ll n = sqrtl(m) + 1;
    ll an = 1;
    REP(i,0,n){
        an = (an * a) % m;
    }
    unordered_map<ll,ll> vals;
    for(ll q = 0, cur = b; q <= n; ++q){
        vals[cur] = q;
        cur = (cur * a) % m;
    }
    for(ll p = 1, cur = k; p <= n; ++p){
        cur = (cur * an) % m;
        if(vals.count(cur)){
            ll ans = n*p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}
// The time complexity remains O(sqrt(m)) as before since the initial reduction to coprime a and m is done in O((logm)^2).