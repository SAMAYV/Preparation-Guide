ll compute_hash(string const& s){
    ll p = 31;
    ll m = 1e9 + 9;
    ll hash_value = 0;
    ll p_pow = 1;
    for(char c : s){
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// We calculate the hash for each string, sort the hashes together with the indices, and then group the indices by identical hashes.
vector<vector<ll>> group_identical_strings(vector<string> const& s){
    ll n = s.size();
    vector<pair<ll,ll>> hashes(n);
    REP(i,0,n){
        hashes[i] = {compute_hash(s[i]), i};
    }
    sort(hashes.begin(), hashes.end());

    vector<vector<ll>> groups;
    REP(i,0,n){
        if(i == 0 || hashes[i].first != hashes[i-1].first)
            groups.emplace_back();
        groups.back().push_back(hashes[i].second);
    }
    return groups;
}