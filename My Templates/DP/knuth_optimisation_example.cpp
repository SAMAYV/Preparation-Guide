// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

vector<vector<ll>> dp,mid;
ll knuth(ll l,ll r,vector<ll>& arr){
	if(l+1 == r){
        mid[l][r] = l;
        dp[l][r] = 0;
        return 0;
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    ll ans = LLONG_MAX;
    ll v1 = knuth(l,r-1,arr);
    ll v2 = knuth(l+1,r,arr);
    for(ll i = (ll)max(l+1,mid[l][r-1]); i <= (ll)min(r-1,mid[l+1][r]); i++){
        if(ans > dp[l][i] + dp[i][r] + arr[r]-arr[l]){
            ans = dp[l][i] + dp[i][r] + arr[r]-arr[l];
            mid[l][r] = i; 
        }
    }
    return dp[l][r] = ans;
}
// Time Complexity O(m*m)

ll minCost(ll n,vector<ll>& cuts){
    vector<ll> newcuts;
    newcuts.push_back(0);
    sort(cuts.begin(),cuts.end());
    for(auto it:cuts) newcuts.push_back(it);
    newcuts.push_back(n);
    ll m = newcuts.size();
    dp.clear();
    dp.resize(m,vector<ll>(m,-1));
    mid.clear();
    mid.resize(m,vector<ll>(m,-1));
    return knuth(0,m-1,newcuts);
}