string min_cyclic_string(string s){
    s += s;
    ll n = s.size();
    ll i = 0, ans = 0;
    while(i < n / 2){
        ans = i;
        ll j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[k] < s[j]){
                k = i;
            }
            else {
                k++;
            }
            j++;
        }
        while(i <= k){
            i += j - k;
        }
    }
    return s.substr(ans, n / 2);
}