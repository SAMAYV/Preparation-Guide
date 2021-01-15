ll const maxn = 1e6 + 5;
ll const lg = 21;

ll tempSA[maxn], SA[maxn], RA[maxn], LCP[maxn], c[maxn], tempRA[maxn];
ll C[lg][maxn];
ll n, stp = 1;

void countingSort(ll k) 
{                     
    ll maxi = max(300LL,n);                     // up to 255 ASCII chars
    memset(c,0,sizeof(c));
    REP(i,0,n){                                 // count the frequency
        ++c[i+k < n ? RA[i+k] : 0];             // of each integer rank
    }
    for(ll i = 0, sum = 0; i < maxi; ++i){
        ll t = c[i]; 
        c[i] = sum; 
        sum += t;
    }
    REP(i,0,n){                                 // sort SA
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    }
    REP(i,0,n){
        SA[i] = tempSA[i];
    }
}

void constructSA(string& s) 
{
    n = s.size();                             
    REP(i,0,n){
        SA[i] = i;
        RA[i] = s[i];                               // initial rankings  
        C[0][i] = RA[i];
    }
    for(ll k = 1; k < n; k *= 2){                  
        countingSort(k);                          // sort by 2nd item
        countingSort(0);                          // stable-sort by 1st item
        ll r = 0;
        tempRA[SA[0]] = r;                          // re-ranking process
        REP(i,1,n){                                 // compare adj suffixes
            tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i-1]]) && (RA[SA[i]+k] == RA[SA[i-1]+k])) ? r : ++r;                                                    
        }                                           // same pair => same rank r; otherwise, increase r
        REP(i,0,n){
            RA[i] = tempRA[i];
            C[stp][i] = RA[i];
        }
        stp++;
        if(RA[SA[n-1]] == n-1){
            break;                                  // nice optimization
        }              
    }
}

void computeLCP(string& s){
    n = s.size();
    ll h = 0;
    REP(i,0,n){
        if(RA[i]){
            ll k = SA[RA[i]-1];
            while(s[i+h] == s[k+h]) h++;
            LCP[RA[i]] = h;
            if(h > 0) h--;
        }
    }
}

ll lcp(ll x,ll y){
    ll k, ret = 0;
    if(x == y){
        return n - x;   
    } 
    for(k = stp - 1; k >= 0 && x < n && y < n; k--){
        if(C[k][x] == C[k][y]){
            x += (1 << k); 
            y += (1 << k); 
            ret += (1 << k);
        }
    }
    return ret;
}