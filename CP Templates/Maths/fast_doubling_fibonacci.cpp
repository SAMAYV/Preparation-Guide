pair<ll,ll> fib(ll n){
    if(n == 0){
        return {0, 1};
    }
    auto p = fib(n >> 1LL);
    ll c = p.first*(2*p.second - p.first);
    ll d = p.first*p.first + p.second*p.second;
    if(n & 1){
        return {d, c + d};
    }
    else {
        return {c, d};
    }
}
/*
    Using above method we can find these equations:
    F(2k) = F(k)*(2*F(k+1) − F(k))
    F(2k+1) = F(k+1)*F(k+1) + F(k)*F(k).
    Thus using above two equations Fibonacci numbers can be calculated easily by the following code:
    The above code returns F(n) and F(n+1) as a pair.
*/
