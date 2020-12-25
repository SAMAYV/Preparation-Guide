ll solve(ll n,vector<bool> good,vector<ll>& deg,vector<ll>& cnt) 
{
    good.resize(n+1,1);
    deg.resize(n+1,0);
    cnt.resize(n+1,0);

    ll ans_bad = 0;
    for(ll i=2; i<=n; ++i){
        // good[i] to mark either if i contains each factor at most twice (good[i]=1) or not (good[i]=0)
        if(good[i])
        {
            // deg[i] to store the number of primes in the factorization of i
            if(deg[i] == 0) deg[i] = 1;
            for(ll j=1; i*j<=n; ++j)
            {
                if(j > 1 && deg[i] == 1){
                    if(j % i == 0) good[i*j] = false;
                    else ++deg[i*j];
                }
                // cnt[i] — the number of integers not coprime with i
                cnt[i*j] += (n / i)*(deg[i] % 2 == 1 ? +1 : -1);
            }
        }
        ans_bad += (cnt[i] - 1) * (n - 1 - cnt[i]);
    }
    return (((n-1) * (n-2) * (n-3) / 6) - ans_bad) / 2;
}

// The asymptotics of our solution is O(nlogn), as for almost every number up to n we make n/i iterations on the nested loop.

// You are given a number n ≤ 10^6. You are required to count the number of triples 2 ≤ a < b < c ≤ n that satisfy one of the following conditions:
// gcd(a,b) = gcd(a,c) = gcd(b,c) = 1, or gcd(a,b) > 1,gcd(a,c) > 1,gcd(b,c) > 1.