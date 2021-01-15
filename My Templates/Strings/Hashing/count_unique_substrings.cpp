ll count_unique_substrings(string const& s){
    ll n = s.size();
    ll p = 31;
    ll m = 1e9 + 9;
    vector<ll> p_pow(n);
    p_pow[0] = 1;
    REP(i,1,n){
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    vector<ll> h(n + 1, 0);
    REP(i,0,n){
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }

    ll cnt = 0;
    REP(l,1,n+1){
        set<ll> hs;
        REP(i,0,n-l+1){
            ll cur_h = (h[i + l] + m - h[i]) % m;
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}

// Remember, the probability that collision happens is only ≈ 1/m. For m = 10^9 + 9 the probability is ≈ 10^−9 which is quite low.
// And if we want to compare 106 different strings with each other (e.g. by counting how many unique strings exists), 
// then the probability of at least one collision happening is already ≈ 1.

// There is a really easy trick to get better probabilities. 
// We can just compute two different hashes for each string (by using two different p, and/or different m, and compare these pairs instead.
// If m is about 10^9 for each of the two hash functions than this is more or less equivalent as having one hash function with m ≈ 10^18