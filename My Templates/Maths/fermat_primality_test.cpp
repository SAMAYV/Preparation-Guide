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
bool probablyPrimeFermat(ll n,ll iter = 10){
    if(n < 4){
        return n == 2 || n == 3;
    }
    REP(i,0,iter){
        ll a = 2 + rand() % (n - 3);
        if(binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
// There is one bad news though: there exist some composite numbers where a^(n−1) ≡ 1 modn holds for all a coprime to n, for instance for the number 
// 561=3⋅11⋅17. Such numbers are called Carmichael numbers. The Fermat primality test can identify these numbers only, if we have immense luck 
// and choose a base a with gcd(a,n) != 1.