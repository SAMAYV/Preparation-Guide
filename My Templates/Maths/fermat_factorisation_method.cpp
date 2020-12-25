ll fermat(ll n){
    ll a = ceil(sqrtl(n));
    ll b2 = a*a - n;
    ll b = round(sqrt(b2));
    while(b * b != b2){
        a = a + 1;
        b2 = a*a - n;
        b = round(sqrtl(b2));
    }
    return a - b;
}
// Notice, this factorization method can be very fast, if the difference between the two factors p and q is small. 
// The algorithm runs in O(|p − q|) time. However since it is very slow, once the factors are far apart, it is rarely used in practice.
// Fermat's factorization method tries to exploit the fact, by guessing the first square a2, and check if the remaining part b2 = a2 − n 
// is also a square number. If it is, then we have found the factors a−b and a+b of n.