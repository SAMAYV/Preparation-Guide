ll binpow(ll a,ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

ll binpow(ll a,ll b){
    if(b == 0)
        return 1;
    ll res = binpow(a, b/2);
    if(b % 2){
        return res * res * a;
    }
    else {
        return res * res;
    }
} 
    