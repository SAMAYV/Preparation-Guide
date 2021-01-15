vector<vector<ll>> dp,C,state;

// This can be done by the following pseudocode which for fixed i applies divide and conquer on j  
// and keeps range (jleft,jright) of values of j for which we are seeking the answer and the 
// corresponding range (kleft,kright) of the possible values for optimal k when j is in the range (jleft,jright)
void compute(ll i,ll jleft,ll jright,ll kleft,ll kright)
{
    if(jleft > jright){
        return;    
    } 
    ll jmid = (jleft + jright) / 2;
    ll best = 1e18;
    ll bestk = 0; 

    // calculating the answer for jmid and state[i][jmid] <= state[i][j] for all j >= jmid due to monotonicity
    REP(k,kleft,(ll)min(jmid,kright+1)){
        if(dp[i - 1][k] + C[k + 1][jmid] < best){
            best = dp[i - 1][k] + C[k + 1][jmid]; 
            bestk = k;
            state[i][jmid] = k;
        } 
    } 
    dp[i][jmid] = best;

    // Divide and conquer 
    if(jleft <= jmid - 1){
        compute(i, jleft, jmid - 1, kleft, bestk);
    } 
    if(jmid + 1 <= jright){
        compute(i, jmid + 1, jright, bestk, kright);
    } 
}

void solve(ll n,ll m){
    dp.clear();
    dp.resize(m+1,vector<ll>(n+1,0));
    state.clear();
    state.resize(m+1,vector<ll>(n+1,0));
    C.clear();
    C.resize(n+1,vector<ll>(n+1,0));
    
    // calculate for i = 0
    dp[0][0] = 0;
    REP(i,1,n+1){
        dp[0][i] = 1e18;
    }
    REP(i,1,m+1){
        dp[i][0] = 1e18;
    }
    // compute C

    REP(i,1,m+1){
        compute(i,1,n,0,n);
    }
}

/*
Some dynamic programming problems have a recurrence of this form: dp(i,j) = (k ≤ j)min{dp(i − 1,k) + C(k+1,j)} where C(k+1,j) is some cost function.
Say 1 ≤ i ≤ n and 1 ≤ j ≤ m, and evaluating C takes O(1) time. Straightforward evaluation of the above recurrence is O(n*m*m).
Let opt(i,j) be the value of k that minimizes the above expression. If opt(i,j) ≤ opt(i,j+1) for all i,j, then we can apply divide-and-conquer DP. 
This known as the monotonicity condition. The optimal "splitting point" for a fixed i increases as j increases.
*/
