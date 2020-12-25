ll solve(ll n,ll r)
{
    vector<ll> p;
    for(ll i=2; i*i<=n; ++i){
        if(n % i == 0){
            p.push_back(i);
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1){
        p.push_back(n);
    }

    ll sum = 0;
    REP(msk,1LL,(1LL << p.size())){
        ll mult = 1, bits = 0;
        REP(i,0,p.size()){
            if((msk >> i) & 1){
                ++bits;
                mult *= p[i];
            }
        }
        ll cur = r / mult;
        if(bits % 2) sum += cur;
        else sum -= cur;
    }
    return r - sum;
}
// Task: given two numbers n and r, count the number of integers in the interval [1;r] that are relatively prime to n.
// Asymptotics of the solution is O(sqrt(n)).