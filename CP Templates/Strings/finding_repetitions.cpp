vector<ll> z_function(string const& s){
    ll n = s.size();
    vector<ll> z(n);
    for(ll i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while(i + z[i] < n && s[z[i]] == s[i+z[i]])
            z[i]++;
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
ll get_z(vector<ll> const& z,ll i){
    if(i >= 0 && i < z.size())
        return z[i];
    else
        return 0;
}
vector<pair<ll,ll>> repetitions;

void convert_to_repetitions(ll shift,bool left,ll cntr,ll l,ll k1,ll k2){
    for(ll l1 = max(1LL, l - k2); l1 <= min(l, k1); l1++){
        if(left && l1 == l) break;
        ll l2 = l - l1;
        ll pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
        repetitions.emplace_back(pos, pos + 2*l - 1);
    }
}
void find_repetitions(string s,ll shift = 0){
    ll n = s.size();
    if(n == 1)
        return;

    ll nu = n / 2;
    ll nv = n - nu;
    string u = s.substr(0, nu);
    string v = s.substr(nu);
    string ru(u.rbegin(), u.rend());
    string rv(v.rbegin(), v.rend());

    find_repetitions(u, shift);
    find_repetitions(v, shift + nu);

    vector<ll> z1 = z_function(ru);
    vector<ll> z2 = z_function(v + '#' + u);
    vector<ll> z3 = z_function(ru + '#' + rv);
    vector<ll> z4 = z_function(v);

    for(ll cntr = 0; cntr < n; cntr++){
        ll l, k1, k2;
        if(cntr < nu){
            l = nu - cntr;
            k1 = get_z(z1, nu - cntr);
            k2 = get_z(z2, nv + 1 + cntr);
        } 
        else {
            l = cntr - nu + 1;
            k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
            k2 = get_z(z4, (cntr - nu) + 1);
        }
        if(k1 + k2 >= l){
            convert_to_repetitions(shift, cntr < nu, cntr, l, k1, k2);
        }
    }
}

// The implementation of the Main-Lorentz algorithm finds all repetitions in form of peculiar tuples of size four: (cntr, l, k1, k2) 
// in O(nlogn) time. If you only want to find the number of repetitions in a string, or only want to find the longest repetition in 
// a string, this information is enough and the runtime will still be O(nlogn).

// Notice that if you want to expand these tuples to get the starting and end position of each repetition, then the runtime will be the 
// runtime will be O(n2) (remember that there can be O(n2) repetitions). In this implementation we will do so, and store all found 
// repetition in a vector of pairs of start and end indices.