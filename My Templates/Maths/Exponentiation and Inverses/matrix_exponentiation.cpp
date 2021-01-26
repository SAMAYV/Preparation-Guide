struct matrix {
    vector<vector<ll>> m;
};

void matrix_resize(matrix &a,ll rows,ll cols){
    a.m.resize(rows);
    REP(i,0,rows){
       a.m[i].resize(cols);
    }
}

void matrix_init(matrix &a,ll x){
    REP(i,0,a.m.size()){
        REP(j,0,a.m[0].size()){
            a.m[i][j] = x;
        }
    }
}

matrix multiply(matrix m1,matrix m2){
    matrix m3;
    matrix_resize(m3,m1.m.size(),m2.m[0].size());
    REP(i,0,m3.m.size()){
        REP(j,0,m3.m[0].size()){
            m3.m[i][j] = 0;
            REP(k,0,m1.m[0].size()){
                m3.m[i][j] = (m3.m[i][j] + m1.m[i][k]*m2.m[k][j]) % mod;
            }
        }
    }
    return m3;
}

matrix power(matrix &a,ll n){
    matrix res;
    matrix_resize(res,a.m.size(),a.m[0].size());
    matrix_init(res,0);
    REP(i,0,a.m.size()){
        res.m[i][i] = 1;
    }    
    while(n > 0){
        if(n & 1){
            res = multiply(res,a);
        }
        a = multiply(a,a);
        n = n >> 1;
   }
   return res;
}