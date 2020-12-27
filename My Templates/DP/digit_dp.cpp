// How many numbers x are there in the range a to b, where the digit d occurs exactly k times in x?
ll const n = 1e5 + 5;
ll m = 20;

ll dp[n][m][2];

// dp[p][c][f] = Number of valid numbers <= b from this state
// p = current position from left side (zero based)
// c = upper bound on max value of function g
// f = tight specifies whether we are free to choose any number as current digit

ll memo(ll pos,ll cnt,ll f,vector<ll>& num)
{
    if(cnt > k) return 0;
    if(pos == num.size()){
        if(cnt == k) return 1;
        else return 0;
    }
    if(dp[pos][cnt][f] != -1){
        return dp[pos][cnt][f];    
    } 
    ll res = 0;
    ll LMT = f ? num[pos] : 9;

    // Try to place all the valid digits such that the number doesn't exceed b
    REP(i,0,LMT+1){
        ll ncnt = cnt;
        if(i == d) ncnt++;
        if(ncnt <= k) res += memo(pos+1, ncnt, f & (i == LMT), num);
    }
    return DP[pos][cnt][f] = res;
}

ll solve(ll b)
{
    vector<ll> num;
    while(b > 0){
        num.push_back(b % 10);
        b /= 10;
    }
    reverse(num.begin(), num.end());
    // Stored all the digits of b in num for simplicity

    memset(dp,-1,sizeof(dp));
    return res = memo(0,0,1,num);
}

int main() 
{
    ll a,b,d,k;
    cin>>a>>b>>d>>k;
    int res = solve(b) - solve(a-1);
    return 0;
}