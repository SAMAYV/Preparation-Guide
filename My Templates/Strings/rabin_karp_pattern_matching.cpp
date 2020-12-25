vector<ll> rabin_karp(string const& s, string const& t){
    ll p = 31; 
    ll m = 1e9 + 9;
    ll S = s.size(), T = t.size();

    vector<ll> p_pow(max(S,T) + 1); 
    p_pow[0] = 1; 
    REP(i,1,p_pow.size()){
        p_pow[i] = (p_pow[i-1] * p) % m;
    } 

    vector<ll> h(T + 1, 0); 
    REP(i,0,T){
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    }
    ll h_s = 0; 
    REP(i,0,S){
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }  

    vector<ll> occurences;
    for(ll i = 0; i + S - 1 < T; i++){ 
        ll cur_h = (h[i+S] + m - h[i]) % m; 
        if(cur_h == (h_s * p_pow[i]) % m){
            occurences.push_back(i);
        }
    }
    return occurences;
}
 
    