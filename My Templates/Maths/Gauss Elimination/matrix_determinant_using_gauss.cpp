ll determinant(ll n,vector<vector<double>> a){
    double EPS = 1E-9;
    double det = 1;
    REP(i,0,n){
        ll k = i;
        REP(j,i+1,n){
            if(abs(a[j][i]) > abs(a[k][i]))
                k = j;
        }
        if(abs(a[k][i]) < EPS){
            return 0;
        }
        swap(a[i], a[k]);
        if(i != k){
            det = -det;
        }
        det *= a[i][i];
        REP(j,i+1,n){
            a[i][j] /= a[i][i];
        }
        REP(j,0,n){
            if(j != i && abs(a[j][i]) > EPS){
                REP(k,i+1,n){
                    a[j][k] -= a[i][k] * a[j][i];
                }
            }
        }
    }
    return det;
}
int main()
{   

    return 0;
}   
    