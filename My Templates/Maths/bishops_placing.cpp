// 1 2 5 6 9 
// 2 5 6 9 8 
// 5 6 9 8 7 
// 6 9 8 7 4
// 9 8 7 4 3

ll squares(ll i){
    if(i & 1)
        return i / 4 * 2 + 1;
    else
        return (i - 1) / 4 * 2 + 2;
}
ll bishop_placements(ll N,ll K)
{
    if(K > 2*N - 1){
        return 0;
    }
    vector<vector<ll>> D(N*2,vector<ll>(K + 1));
    REP(i,0,2*N){
        D[i][0] = 1;
    }
    D[1][1] = 1;
    REP(i,2,2*N){
        REP(j,1,k+1){
            D[i][j] = D[i-2][j] + D[i-2][j-1]*(squares(i) - (j - 1));
        }
    }
    ll ans = 0;
    REP(i,0,K+1){
        ans += D[N*2-1][i] * D[N*2-2][K-i];
    }
    return ans;
}
// Find the number of ways to place K bishops on an N×N chessboard so that no two bishops attack each other
// Let D[i][j] denote the number of ways to place j bishops on diagonals with indices up to i which have the same color as diagonal i. 
// Then i = 1...2N-1 and j = 0...K.