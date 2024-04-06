// number of primes from 1 to n using blocks
ll count_primes(ll n) 
{
    // S is each block size
    const ll S = 10000;

    vector<ll> primes;
    ll nsqrt = sqrtl(n);
    vector<char> is_prime(nsqrt + 1, true);
    REP(i,2,sqrtn+1){
        if(is_prime[i]){
            primes.push_back(i);
            for(int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    ll result = 0;
    vector<bool> block(S,true);
    for(ll k = 0; k * S <= n; k++){
        fill(block.begin(), block.end(), true);
        ll start = k * S;
        for(ll p : primes){
            ll start_idx = (start + p - 1) / p;
            ll j = max(start_idx*p, p*p) - start;
            for(; j < S; j += p)
                block[j] = false;
        }
        if(k == 0)
            block[0] = block[1] = false;
        for(ll i = 0; i < S && start + i <= n; i++){
            if(block[i]){
                result++;
            }
        }
    }
    return result;
}

// Find primes in range L to R
vector<bool> segmentedSieve(ll L,ll R)
{
    // generate all primes up to sqrt(R)
    ll lim = sqrtl(R);
    vector<bool> mark(lim + 1, false);
    vector<ll> primes;
    REP(i,2,lim+1){
        if(!mark[i]){
            primes.emplace_back(i);
            for(ll j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }
    vector<bool> isPrime(R - L + 1, true);
    for(ll i : primes){
        for(ll j = max(i * i, ((L + i - 1) / i) * i); j <= R; j += i){
            isPrime[j - L] = false;
        }
    }
    if(L == 1)
        isPrime[0] = false;
    return isPrime;
}
