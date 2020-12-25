bool next_combination(vector<ll>& a,ll n){
    ll k = a.size();
    REPI(i,0,k){
        if(a[i] < n - k + i + 1){
            a[i]++;
            REP(j,i+1,k){
                a[j] = a[j - 1] + 1;
            }
            return true;
        }
    }
    return false;
}
// Given the natural numbers N and K, and considering a set of numbers from 1 to N, Generate next lexicographical K-combination.