ll gray_code(ll n){
    return n ^ (n >> 1LL);
}
ll count_bits(ll n){
    ll res = 0;
    for(; n; n >>= 1)
        res += n & 1;
    return res;
}
void all_combinations(ll n,ll k){
    REP(i,0,(1LL << n)){
        ll cur = gray_code(i);
        if(count_bits(cur) == k){
            REP(j,0,n){
                if(cur & (1LL << j)){
                    cout << j + 1;
                }
            }
            cout << "\n";
        }
    }
}
// Generate all K-combinations such that adjacent combinations differ by one element
// The following is a naive implementation working by generating all 2n possible subsets, and finding subsets of size K.


vector<ll> ans;
void gen(ll n,ll k,ll idx,bool rev){
    if(k > n || k < 0)
        return;
    if(!n){
        REP(i,0,idx){
            if(ans[i]) cout << i + 1;
        }
        cout << "\n";
        return;
    }
    ans[idx] = rev;
    gen(n - 1, k - rev, idx + 1, false);
    ans[idx] = !rev;
    gen(n - 1, k - !rev, idx + 1, true);
}
void all_combinations(ll n,ll k){
    ans.resize(n);
    gen(n, k, 0, false);
}
// It's worth mentioning that a more efficient implementation exists that only resorts to building valid combinations and thus works 
// in O(N⋅(N/K)) however it is recursive in nature and for smaller values of N it probably has a larger constant than the previous solution.
// The implementation is derived from the formula: 
// G(N,K) = 0G(N−1,K) ∪ 1G(N−1,K−1)R
