// Given a grid of size N×M. Find number of ways to fill the grid with figures of size 2×1 (no cell should be left unfilled and figures should not overlap each other)

vector<vector<ll>> board, dp;

// Check if ith block is occupied in profile q
bool occupied(ll i,ll q){ 
    return q & (1 << (i-1));
}

// i represents the current column of jth row 
// jth row is having the profile q
// p represents the profile of the (j+1)th row while filling jth row completely

void search(ll i,ll j,ll p,ll q,ll m,ll n){
    if(i == n+1){
        dp[j+1][p] += dp[j][q];
        return;
    }
    if(occupied(i, q)){
        search(i+1, j, p, q, m, n);
        return;
    }
    if(i+1 <= n && !occupied(i+1, q)){
        search(i+2, j, p, q, m, n);
    }
    if(j+1 <= m){
        search(i+1, j, p^(1 << (i-1)), q, m, n);
    }
}

void solve(ll m,ll n)
{
    board.clear();
    board.resize(m+1,vector<ll>(n+1));
    dp.clear();
    dp.resize(m+1,vector<ll>((1 << n),0));
    dp[0][0] = 1; 

    // all the rows till (j-1) are filled completely and state of jth row is given by q
    // we are trying to fill the jth row completely when it is in profile q and then finding which profiles it can achieve for (j+1)th row  
    REP(j,0,m){
        REP(q,0,(1 << n)){
            search(1, j, 0, q, m, n);
        }
    }
    cout<<dp[m][0]<<endl;
}

/* Let the DP state be: dp[i,mask], where i = 1,…N and mask = 0,…2^M−1.
i represents number of rows in the current grid, and mask is the state of last row of current grid. If j-th bit of mask is 0
then the corresponding cell is filled, otherwise it is unfilled.

Clearly, the answer to the problem will be dp[N,0].

We will be building the DP state by iterating over each i=1,⋯N and each mask = 0,…2M−1, and for each mask we will be only 
transitioning forward, that is, we will be adding figures to the current grid. */
