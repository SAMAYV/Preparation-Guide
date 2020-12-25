ll compute_rank(vector<vector<double>> A){
    double EPS = 1E-9;
    ll n = A.size();
    ll m = A[0].size();

    ll rank = 0;
    vector<bool> row_selected(n,0);
    REP(i,0,m){
        ll j;
        for(j = 0; j < n; ++j){
            if(!row_selected[j] && abs(A[j][i]) > EPS)
                break;
        }
        if(j != n){
            ++rank;
            row_selected[j] = true;
            REP(p,i+1,m){
                A[j][p] /= A[j][i];
            }
            REP(k,0,n){
                if(k != j && abs(A[k][i]) > EPS){
                    REP(p,i+1,m){
                        A[k][p] -= A[j][p] * A[k][i];
                    }
                }
            }
        }
    }
    return rank;
}