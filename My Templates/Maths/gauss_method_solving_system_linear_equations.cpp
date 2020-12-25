// Solving Ax = b system of linear equations 
// So the final complexity of the algorithm is O(min(n,m).nm). In case n=m, the complexity is simply O(n3).

ll gauss(vector<vector<double>> a, vector<double>& ans)
{
    double EPS = 1e-9;
    ll n = a.size();
    // mth column is vector b
    ll m = a[0].size() - 1;

    // where[i] stores which row of ith column is nonzero atlast
    vector<ll> where(m, -1);

    for(ll col=0,row=0; col<m && row<n; ++col){
        ll sel = row;
        // selecting the pivot row to replace with current row (row having having value at that column)
        REP(i,row,n){
            if(abs(a[i][col]) > abs(a[sel][col])){
                sel = i;
            }
        }
        if(abs(a[sel][col]) < EPS){
            continue;
        }
        REP(i,col,m+1){
            swap(a[sel][i], a[row][i]);
        }
        where[col] = row;

        REP(i,0,n){
            if(i != row){
                double c = a[i][col] / a[row][col];
                REP(j,col,m+1){
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row;
    }

    ans.assign(m, 0);
    REP(i,0,m){
        if(where[i] != -1){
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }
    REP(i,0,n){
        double sum = 0;
        REP(j,0,m){
            sum += ans[j] * a[i][j];
        }
        if(abs(sum - a[i][m]) > EPS){
            return 0;
        }
    }
    REP(i,0,m){
        // means that independent variable is present hence infinite solutions
        if(where[i] == -1){
            return 1e18;
        }
    }
    return 1;
}

/*
The previous implementation can be speed up by two times, by dividing the algorithm into two phases: forward and reverse:

Forward phase: Similar to the previous implementation, but the current row is only added to the rows after it. As a result, we obtain a triangular matrix instead of diagonal.
Reverse phase: When the matrix is triangular, we first calculate the value of the last variable. Then plug this value to find the value of next variable. Then plug these two values to find the next variables...

Reverse phase only takes O(nm), which is much faster than forward phase. In forward phase, we reduce the number of operations by half, 
thus reducing the running time of the implementation.
*/

// When matrix consists of only zeros and ones
ll gauss(vector<bitset<N>> a,ll n,ll m,bitset<N>& ans){
    vector<ll> where(m,-1);
    for(ll col=0,row=0; col<m && row<n; ++col){
        REP(i,row,n){
            if(a[i][col]){
                swap(a[i],a[row]);
                break;
            }
        }
        if(!a[row][col])
            continue;
        where[col] = row;

        REP(i,0,n){
            if(i != row && a[i][col])
                a[i] ^= a[row];
        }
        ++row;
    }
    // The rest of implementation is the same as above
}

// However, in case the module is equal to two, we can perform Gauss-Jordan elimination much more effectively using bitwise operations and C++ bitset data types.
