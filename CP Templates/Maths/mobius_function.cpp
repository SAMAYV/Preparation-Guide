vector<ll> mobius_function(ll n)
{
    vector<ll> lps(n+1,0), mobius(n+1,0);
    REP(i,2,n+1){
        if(!lps[i]){
            for(ll j = i; j <= n; j += i){
                if(!lps[j]){
                    lps[j] = i;
                }
            }
        }
    }
    mobius[1] = 1;
    REP(i,2,n+1){
        if(lps[i] == lps[i/lps[i]]){
            mobius[i] = 0;
        } 
        else {
            mu[i] = -mu[i/lps[i]];
        }
    }
    return mobius;
}
